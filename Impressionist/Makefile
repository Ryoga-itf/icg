WORKDIR = `pwd`

FLTK=/home/ryoga/workspace/univ/icg/fltk-1.3.0

CC = gcc
CXX = g++
AR = ar
LD = g++
WINDRES = windres

INC = -I$(FLTK) -I/usr/include -I/home/ryoga/workspace/repos/github.com/Ryoga-itf/icg/Impressionist/include
CFLAGS = `$(FLTK)/fltk-config --cxxflags`
RESINC = 
LIBDIR = -L$(FLTK)/lib -L/usr/lib/x86_64-linux-gnu
LIB = $(FLTK)/lib/libfltk_images.a \
			$(FLTK)/lib/libfltk_gl.a \
			$(FLTK)/lib/libfltk_forms.a \
			$(FLTK)/lib/libfltk.a \
			$(FLTK)/lib/libfltk_z.a \
			$(FLTK)/lib/libfltk_jpeg.a \
			$(FLTK)/lib/libfltk_png.a \
			/usr/lib/x86_64-linux-gnu/libpng16.so.16 \
			/usr/lib/x86_64-linux-gnu/libz.so \
			/usr/lib/x86_64-linux-gnu/libGL.so \
			/usr/lib/x86_64-linux-gnu/libGLU.so.1
LDFLAGS = `$(FLTK)/fltk-config --ldstaticflags`

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

OBJ_DEBUG = $(OBJDIR_DEBUG)/pointBrush.o \
						$(OBJDIR_DEBUG)/triangleBrush.o \
						$(OBJDIR_DEBUG)/circleBrush.o \
						$(OBJDIR_DEBUG)/lineBrush.o \
						$(OBJDIR_DEBUG)/paintView.o \
						$(OBJDIR_DEBUG)/originalView.o \
						$(OBJDIR_DEBUG)/impressionistUI.o \
						$(OBJDIR_DEBUG)/FltDesignUI.o \
						$(OBJDIR_DEBUG)/impressionistDoc.o \
						$(OBJDIR_DEBUG)/impressionist.o \
						$(OBJDIR_DEBUG)/impBrush.o \
						$(OBJDIR_DEBUG)/bitmap.o

OBJ_RELEASE = $(OBJDIR_RELEASE)/pointBrush.o \
							$(OBJDIR_RELEASE)/triangleBrush.o \
							$(OBJDIR_RELEASE)/circleBrush.o \
							$(OBJDIR_RELEASE)/lineBrush.o \
							$(OBJDIR_RELEASE)/paintView.o \
							$(OBJDIR_RELEASE)/originalView.o \
							$(OBJDIR_RELEASE)/impressionistUI.o \
							$(OBJDIR_RELEASE)/FltDesignUI.o \
							$(OBJDIR_RELEASE)/impressionistDoc.o \
							$(OBJDIR_RELEASE)/impressionist.o \
							$(OBJDIR_RELEASE)/impBrush.o \
							$(OBJDIR_RELEASE)/bitmap.o

all: debug release

clean: clean_debug clean_release

before_debug: 
	test -d bin/Debug || mkdir -p bin/Debug
	test -d $(OBJDIR_DEBUG) || mkdir -p $(OBJDIR_DEBUG)

after_debug: 

debug: before_debug out_debug after_debug

out_debug: before_debug $(OBJ_DEBUG) $(DEP_DEBUG)
	# $(LD) $(LIBDIR_DEBUG) -o $(OUT_DEBUG) $(OBJ_DEBUG)  $(LDFLAGS_DEBUG) $(LIB_DEBUG)

$(OBJDIR_DEBUG)/pointBrush.o: src/pointBrush.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c src/pointBrush.cpp -o $(OBJDIR_DEBUG)/pointBrush.o

$(OBJDIR_DEBUG)/triangleBrush.o: src/triangleBrush.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c src/triangleBrush.cpp -o $(OBJDIR_DEBUG)/triangleBrush.o

$(OBJDIR_DEBUG)/circleBrush.o: src/circleBrush.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c src/circleBrush.cpp -o $(OBJDIR_DEBUG)/circleBrush.o

$(OBJDIR_DEBUG)/lineBrush.o: src/lineBrush.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c src/lineBrush.cpp -o $(OBJDIR_DEBUG)/lineBrush.o

$(OBJDIR_DEBUG)/paintView.o: src/paintView.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c src/paintView.cpp -o $(OBJDIR_DEBUG)/paintView.o

$(OBJDIR_DEBUG)/originalView.o: src/originalView.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c src/originalView.cpp -o $(OBJDIR_DEBUG)/originalView.o

$(OBJDIR_DEBUG)/impressionistUI.o: src/impressionistUI.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c src/impressionistUI.cpp -o $(OBJDIR_DEBUG)/impressionistUI.o

$(OBJDIR_DEBUG)/FltDesignUI.o: src/FltDesignUI.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c src/FltDesignUI.cpp -o $(OBJDIR_DEBUG)/FltDesignUI.o

$(OBJDIR_DEBUG)/impressionistDoc.o: src/impressionistDoc.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c src/impressionistDoc.cpp -o $(OBJDIR_DEBUG)/impressionistDoc.o

$(OBJDIR_DEBUG)/impressionist.o: src/impressionist.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c src/impressionist.cpp -o $(OBJDIR_DEBUG)/impressionist.o

$(OBJDIR_DEBUG)/impBrush.o: src/impBrush.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c src/impBrush.cpp -o $(OBJDIR_DEBUG)/impBrush.o

$(OBJDIR_DEBUG)/bitmap.o: src/bitmap.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c src/bitmap.cpp -o $(OBJDIR_DEBUG)/bitmap.o

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

$(OBJDIR_RELEASE)/pointBrush.o: src/pointBrush.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c src/pointBrush.cpp -o $(OBJDIR_RELEASE)/pointBrush.o

$(OBJDIR_RELEASE)/triangleBrush.o: src/triangleBrush.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c src/triangleBrush.cpp -o $(OBJDIR_RELEASE)/triangleBrush.o

$(OBJDIR_RELEASE)/circleBrush.o: src/circleBrush.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c src/circleBrush.cpp -o $(OBJDIR_RELEASE)/circleBrush.o

$(OBJDIR_RELEASE)/lineBrush.o: src/lineBrush.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c src/lineBrush.cpp -o $(OBJDIR_RELEASE)/lineBrush.o

$(OBJDIR_RELEASE)/paintView.o: src/paintView.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c src/paintView.cpp -o $(OBJDIR_RELEASE)/paintView.o

$(OBJDIR_RELEASE)/originalView.o: src/originalView.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c src/originalView.cpp -o $(OBJDIR_RELEASE)/originalView.o

$(OBJDIR_RELEASE)/impressionistUI.o: src/impressionistUI.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c src/impressionistUI.cpp -o $(OBJDIR_RELEASE)/impressionistUI.o

$(OBJDIR_RELEASE)/FltDesignUI.o: src/FltDesignUI.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c src/FltDesignUI.cpp -o $(OBJDIR_RELEASE)/FltDesignUI.o

$(OBJDIR_RELEASE)/impressionistDoc.o: src/impressionistDoc.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c src/impressionistDoc.cpp -o $(OBJDIR_RELEASE)/impressionistDoc.o

$(OBJDIR_RELEASE)/impressionist.o: src/impressionist.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c src/impressionist.cpp -o $(OBJDIR_RELEASE)/impressionist.o

$(OBJDIR_RELEASE)/impBrush.o: src/impBrush.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c src/impBrush.cpp -o $(OBJDIR_RELEASE)/impBrush.o

$(OBJDIR_RELEASE)/bitmap.o: src/bitmap.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c src/bitmap.cpp -o $(OBJDIR_RELEASE)/bitmap.o

clean_release: 
	rm -f $(OBJ_RELEASE) $(OUT_RELEASE)
	rm -rf bin/Release
	rm -rf $(OBJDIR_RELEASE)

.PHONY: before_debug after_debug clean_debug before_release after_release clean_release

