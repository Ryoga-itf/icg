// The structure used in spatial subdivision to accelerate raytracing by
// reducing the number of intersection tests that need to be performed.
// Algorithm adapted from Graphics Gems III, "Ray Tracing with the BSP Tree",
// Kelvin Sung and Peter Shirley

#ifndef __BSPTREE_H__
#define __BSPTREE_H__

#include "../vecmath/vec.h"
#include "../vecmath/mat.h"
#include "scene.h"

#include <list>
#include <algorithm>
#include <assert.h>

class BSPNode
{
public:
	BoundingBox bounds;			// extent of the node
	std::vector<Geometry*> members;	// objects in this node
	BSPNode *pChild[2];			// pointers to any children nodes
	unsigned short subdiv_axis;			// which axis does the subdivision plane lie on?
	
public:
	BSPNode(const BoundingBox& bounds, const std::vector<Geometry*> &parentMembers, short subdiv_axis)
	{
		this->bounds = bounds;
		members.clear();
		
		// of the parent's children, take only the ones that intersect this node
		std::vector<Geometry*>::const_iterator i;
		for( i = parentMembers.begin(); i != parentMembers.end(); ++i ) {
			if( (*i)->hasBoundingBoxCapability() && (*i)->getBoundingBox().intersects(bounds) ) {
				members.push_back(*i);
			}
		}

		this->subdiv_axis = subdiv_axis;
		pChild[0] = NULL;
		pChild[1] = NULL;
	}

	
	~BSPNode()
	{
		members.clear();
		

		if (pChild[0])
			delete pChild[0];
		if (pChild[1])
			delete pChild[1];
	}

public:
	// recursively construct the tree, using maxDepth and maxListLength as heuristics/controls.
	void Subdivide(unsigned short depth, unsigned short maxDepth, unsigned long maxListLength)
	{
		unsigned short newAxis = (subdiv_axis + 1) % 3;
		unsigned short newDepth = depth + 1;
		double subdiv_width = (bounds.max[subdiv_axis] - bounds.min[subdiv_axis]);
		BoundingBox childBounds;

		if ((depth < maxDepth) && (members.size() > maxListLength)) {
			childBounds = bounds;
			childBounds.max[subdiv_axis] = bounds.min[subdiv_axis] + 0.5 * subdiv_width;

			pChild[0] = new BSPNode(childBounds, members, newAxis);
			pChild[0]->Subdivide(newDepth, maxDepth, maxListLength);
			
			childBounds = bounds;
			childBounds.min[subdiv_axis] += 0.5 * subdiv_width;
			childBounds.max[subdiv_axis] = bounds.min[subdiv_axis] + subdiv_width;
			pChild[1] = new BSPNode(childBounds, members, newAxis);
			pChild[1]->Subdivide(newDepth, maxDepth, maxListLength);
		}
	}

	bool intersect(const ray& r, isect& i, double tMin, double tMax) const
	{
		// if we're a leaf, check the member objects for intersection
		if (pChild[0] == NULL) {
			bool have_one = false;
			isect cur;
			
			for( std::vector<Geometry*>::const_iterator j = members.begin(); j != members.end(); ++j ) {
				if( (*j)->intersect( r, cur ) ) {
					if( !have_one || (cur.t < i.t) ) {
						i = cur;
						have_one = true;
					}
				}
			}

			// if the found intersection point doesn't lie inside the current node, we're not done yet.
			//if (have_one && bounds.intersects(r.at(i.t)))
			if (have_one && (i.t <= tMax + RAY_EPSILON))
				return true;
			else
				return false;
		}
		else { // if we're not a leaf, check the children for intersections.
			BSPNode* pNearNode;
			BSPNode* pFarNode;

			// if the ray is parallel to the cutting plane, we can just assign
			// it an arbitrary negative t-value; this causes only the near child to
			// be checked, and this is what we want since the ray only hits the near
			// child.
			double tValueToCuttingPlane = tValueToSubdivisionPlane(pChild[0]->bounds.max, r);
			

			// put the near child in pNearNode and the far child in pFarNode
			
			//if (pChild[0]->bounds.intersects(r.getPosition()))
			double subdiv_plane_coord = pChild[0]->bounds.max[subdiv_axis];
			double raypos_coord = r.getPosition()[subdiv_axis];

			if ( raypos_coord < subdiv_plane_coord )
			{
				pNearNode = pChild[0];
				pFarNode = pChild[1];
			}
			else if ( raypos_coord == subdiv_plane_coord )
			{
				//There is no far side, try checking the ray direction
				double dir = r.getDirection()[subdiv_axis];
				if(dir > 0) {
					return pChild[1]->intersect(r, i, tMin, tMax);
				} else { //if(dir < 0) {
					return pChild[0]->intersect(r, i, tMin, tMax);
				} /*else {
					//dir == 0
					//If this happens, it'll only intersect objects that are in both sides, so this can be folded into the above cases

					//No culling possible, just check both
					if (pChild[0]->intersect(r, i, tMin, tMax))
						return true;
					else
						return pChild[1]->intersect(r, i, tMin, tMax);
				}*/
			}
			else
			{
				pNearNode = pChild[1];
				pFarNode = pChild[0];
			}
						
			if ((tValueToCuttingPlane > tMax) || (tValueToCuttingPlane < 0.0))			// whole interval is on near side
				return pNearNode->intersect(r, i, tMin, tMax);

			else if (tValueToCuttingPlane < tMin)					// whole interval is on far side
				return pFarNode->intersect(r, i, tMin, tMax);
			
			else {													// interval intersects the plane
				if (pNearNode->intersect(r, i, tMin, tValueToCuttingPlane))
					return true; // i was filled in for us since we passed it in to pNearNode->intersect()
				else
					return pFarNode->intersect(r, i, tValueToCuttingPlane, tMax);
			}
		}
	}
	
private:

	double tValueToSubdivisionPlane(const Vec3d& ptInPlane, const ray& r) const // ray's "t" value at intersection with the subdivision plane
	{
		Vec3d p = ptInPlane - r.getPosition();
		Vec3d d = r.getDirection();

		// if the ray is parallel to the cutting plane, we can just assign
		// it an arbitrary negative t-value; this causes only the near child to
		// be checked, and this is what we want since the ray only hits the near
		// child.
		if( d[subdiv_axis] == 0.0 )
			return -1.0;

		return p[subdiv_axis]/d[subdiv_axis];
	}	
};

class BSPTree
{
private:
	BoundingBox bounds;				// bounds of the entire BSP tree
    std::vector<Geometry*> *pObjects;		// pointer to the list of all primitives
	unsigned short MaxTreeDepth;	// Max allowed tree depth					(heuristic)
	unsigned long MaxListLength;	// Max number of children per node			(heuristic)
	BSPNode *pRoot;					// Pointer to root node

public:
	BSPTree()
	{
		pRoot = NULL;
	}

	~BSPTree()
	{
		if (pRoot)
			delete pRoot;
	}

	void initialize(std::vector<Geometry*> *pObjectList, unsigned short maxTreeDepth, unsigned long maxChildrenPerNode, const BoundingBox& sceneBounds)
	{
		if (pRoot)
			delete pRoot;

		pObjects = pObjectList;
		MaxTreeDepth = maxTreeDepth;
		MaxListLength = maxChildrenPerNode;
		bounds = sceneBounds;
		pRoot = NULL;
	
		// start subdividing along the X axis
		pRoot = new BSPNode(bounds, *pObjects, 0);
		pRoot->Subdivide(0, maxTreeDepth, MaxListLength);
	}

	bool intersect(const ray& r, isect& i) const
	{
		double tMin, tMax;
		// test if the whole BSP tree is missed by the ray, and fill in maximum and minimum "t" boundaries
		if (!bounds.intersect(r, tMin, tMax))
			return false;

		// start at the root, and recursively check for intersections
		return pRoot->intersect(r, i, tMin, tMax);
	}
};


#endif //__BSPTREE_H__
