#source file search paths
VPATH = ./src 

	# compiler include search paths
INCS = -I./include \
	-I../ravencode/pub/src \
	-I../raven-set \
	-I../boost/boost1_78 

LIBS = \
	-lgdiplus -lgdi32 -lcomdlg32 -lstdc++fs \
	#-mwindows

static_link_flags = -static-libstdc++ -static-libgcc -static

# folders
ODIR = ./.vscode/obj
RDIR = ../ravencode/pub/src

OPT = -O2
CCflags = -std=c++17 $(OPT) -D_mingw_

# sources
OBJ = \
	$(ODIR)/test.o  \
	$(ODIR)/quadtree.o \
	$(ODIR)/octree.o \
	$(ODIR)/cRunWatch.o
OBJ_oct = \
	$(ODIR)/testoctree.o  \
	$(ODIR)/octree.o \
	$(ODIR)/cRunWatch.o

OBJ_unit = \
	$(ODIR)/testunit.o  \
	$(ODIR)/quadtree.o \
	$(ODIR)/octree.o \
	$(ODIR)/cutest.o

### COMPILE
$(ODIR)/cRunWatch.o : $(RDIR)/cRunWatch.cpp
	g++  $(CCflags) \
	-c -o $@ $< $(INCS)
$(ODIR)/cutest.o : $(RDIR)/cutest.cpp
	g++  $(CCflags) \
	-c -o $@ $< $(INCS)
$(ODIR)/%.o: %.cpp  
	g++  $(CCflags) \
	-c -o $@ $< $(INCS)

### LINK

qtest: $(OBJ)
	g++ $(OPT) \
	-o bin/quadtreetest.exe $^  \
	$(static_link_flags) $(LIBS)

otest: $(OBJ_oct)
	g++ $(OPT) \
	-o bin/octreetest.exe $^  \
	$(static_link_flags) $(LIBS)

utest: $(OBJ_unit)
	g++ $(OPT) \
	-o bin/unitest.exe $^  \
	$(static_link_flags) $(LIBS)

.PHONY: clean
clean:
	del /q .vscode\\obj\\*.o

