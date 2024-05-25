

WORKDIR = `pwd`

CC = gcc
CXX = g++
AR = ar
LD = g++
WINDRES = windres

INC = -I/home/sxxxxxxx/Desktop/icg_linux/fltk-1.3.0 -I/usr/include 
CFLAGS = `/home/sxxxxxxx/Desktop/icg_linux/fltk-1.3.0/fltk-config --cxxflags` 
RESINC = 
LIBDIR = -L//home/sxxxxxxx/Desktop/icg_linux/fltk-1.3.0/lib -L/usr/lib/x86_64-linux-gnu
LIB = /home/sxxxxxxx/Desktop/icg_linux/fltk-1.3.0/lib/libfltk_images.a /home/sxxxxxxx/Desktop/icg_linux/fltk-1.3.0/lib/libfltk_gl.a /home/sxxxxxxx/Desktop/icg_linux/fltk-1.3.0/lib/libfltk_forms.a /home/sxxxxxxx/Desktop/icg_linux/fltk-1.3.0/lib/libfltk.a /home/sxxxxxxx/Desktop/icg_linux/fltk-1.3.0/lib/libfltk_z.a /home/sxxxxxxx/Desktop/icg_linux/fltk-1.3.0/lib/libfltk_jpeg.a /home/sxxxxxxx/Desktop/icg_linux/fltk-1.3.0/lib/libfltk_png.a /usr/lib/x86_64-linux-gnu/libpng12.so.0 /usr/lib/x86_64-linux-gnu/libz.so /usr/lib/x86_64-linux-gnu/libGL.so /usr/lib/x86_64-linux-gnu/libGLU.so.1
LDFLAGS = `/home/sxxxxxxx/Desktop/icg_linux/fltk-1.3.0/fltk-config --ldstaticflags`

INC_DEBUG = $(INC)
CFLAGS_DEBUG = $(CFLAGS) -g
RESINC_DEBUG = $(RESINC)
RCFLAGS_DEBUG = $(RCFLAGS)
LIBDIR_DEBUG = $(LIBDIR)
LIB_DEBUG = $(LIB)
LDFLAGS_DEBUG = $(LDFLAGS)
OBJDIR_DEBUG = obj/Debug
DEP_DEBUG = 
OUT_DEBUG = bin/Debug/Impressionist

INC_RELEASE = $(INC)
CFLAGS_RELEASE = $(CFLAGS) -O2 -s
RESINC_RELEASE = $(RESINC)
RCFLAGS_RELEASE = $(RCFLAGS)
LIBDIR_RELEASE = $(LIBDIR)
LIB_RELEASE = $(LIB)
LDFLAGS_RELEASE = $(LDFLAGS)
OBJDIR_RELEASE = obj/Release
DEP_RELEASE = 
OUT_RELEASE = bin/Release/Impressionist

OBJ_DEBUG = $(OBJDIR_DEBUG)/pointBrush.o $(OBJDIR_DEBUG)/paintView.o $(OBJDIR_DEBUG)/originalView.o $(OBJDIR_DEBUG)/impressionistUI.o $(OBJDIR_DEBUG)/FltDesignUI.o $(OBJDIR_DEBUG)/impressionistDoc.o $(OBJDIR_DEBUG)/impressionist.o $(OBJDIR_DEBUG)/impBrush.o $(OBJDIR_DEBUG)/bitmap.o

OBJ_RELEASE = $(OBJDIR_RELEASE)/pointBrush.o $(OBJDIR_RELEASE)/paintView.o $(OBJDIR_RELEASE)/originalView.o $(OBJDIR_RELEASE)/impressionistUI.o $(OBJDIR_RELEASE)/FltDesignUI.o $(OBJDIR_RELEASE)/impressionistDoc.o $(OBJDIR_RELEASE)/impressionist.o $(OBJDIR_RELEASE)/impBrush.o $(OBJDIR_RELEASE)/bitmap.o

all: debug release

clean: clean_debug clean_release

before_debug: 
	test -d bin/Debug || mkdir -p bin/Debug
	test -d $(OBJDIR_DEBUG) || mkdir -p $(OBJDIR_DEBUG)

after_debug: 

debug: before_debug out_debug after_debug

out_debug: before_debug $(OBJ_DEBUG) $(DEP_DEBUG)
	$(LD) $(LIBDIR_DEBUG) -o $(OUT_DEBUG) $(OBJ_DEBUG)  $(LDFLAGS_DEBUG) $(LIB_DEBUG)

$(OBJDIR_DEBUG)/pointBrush.o: pointBrush.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c pointBrush.cpp -o $(OBJDIR_DEBUG)/pointBrush.o

$(OBJDIR_DEBUG)/paintView.o: paintView.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c paintView.cpp -o $(OBJDIR_DEBUG)/paintView.o

$(OBJDIR_DEBUG)/originalView.o: originalView.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c originalView.cpp -o $(OBJDIR_DEBUG)/originalView.o

$(OBJDIR_DEBUG)/impressionistUI.o: impressionistUI.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c impressionistUI.cpp -o $(OBJDIR_DEBUG)/impressionistUI.o

$(OBJDIR_DEBUG)/FltDesignUI.o: FltDesignUI.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c FltDesignUI.cpp -o $(OBJDIR_DEBUG)/FltDesignUI.o

$(OBJDIR_DEBUG)/impressionistDoc.o: impressionistDoc.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c impressionistDoc.cpp -o $(OBJDIR_DEBUG)/impressionistDoc.o

$(OBJDIR_DEBUG)/impressionist.o: impressionist.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c impressionist.cpp -o $(OBJDIR_DEBUG)/impressionist.o

$(OBJDIR_DEBUG)/impBrush.o: impBrush.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c impBrush.cpp -o $(OBJDIR_DEBUG)/impBrush.o

$(OBJDIR_DEBUG)/bitmap.o: bitmap.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c bitmap.cpp -o $(OBJDIR_DEBUG)/bitmap.o

clean_debug: 
	rm -f $(OBJ_DEBUG) $(OUT_DEBUG)
	rm -rf bin/Debug
	rm -rf $(OBJDIR_DEBUG)

before_release: 
	test -d bin/Release || mkdir -p bin/Release
	test -d $(OBJDIR_RELEASE) || mkdir -p $(OBJDIR_RELEASE)

after_release: 

release: before_release out_release after_release

out_release: before_release $(OBJ_RELEASE) $(DEP_RELEASE)
	$(LD) $(LIBDIR_RELEASE) -o $(OUT_RELEASE) $(OBJ_RELEASE)  $(LDFLAGS_RELEASE) $(LIB_RELEASE)

$(OBJDIR_RELEASE)/pointBrush.o: pointBrush.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c pointBrush.cpp -o $(OBJDIR_RELEASE)/pointBrush.o

$(OBJDIR_RELEASE)/paintView.o: paintView.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c paintView.cpp -o $(OBJDIR_RELEASE)/paintView.o

$(OBJDIR_RELEASE)/originalView.o: originalView.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c originalView.cpp -o $(OBJDIR_RELEASE)/originalView.o

$(OBJDIR_RELEASE)/impressionistUI.o: impressionistUI.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c impressionistUI.cpp -o $(OBJDIR_RELEASE)/impressionistUI.o

$(OBJDIR_RELEASE)/FltDesignUI.o: FltDesignUI.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c FltDesignUI.cpp -o $(OBJDIR_RELEASE)/FltDesignUI.o

$(OBJDIR_RELEASE)/impressionistDoc.o: impressionistDoc.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c impressionistDoc.cpp -o $(OBJDIR_RELEASE)/impressionistDoc.o

$(OBJDIR_RELEASE)/impressionist.o: impressionist.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c impressionist.cpp -o $(OBJDIR_RELEASE)/impressionist.o

$(OBJDIR_RELEASE)/impBrush.o: impBrush.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c impBrush.cpp -o $(OBJDIR_RELEASE)/impBrush.o

$(OBJDIR_RELEASE)/bitmap.o: bitmap.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c bitmap.cpp -o $(OBJDIR_RELEASE)/bitmap.o

clean_release: 
	rm -f $(OBJ_RELEASE) $(OUT_RELEASE)
	rm -rf bin/Release
	rm -rf $(OBJDIR_RELEASE)

.PHONY: before_debug after_debug clean_debug before_release after_release clean_release

