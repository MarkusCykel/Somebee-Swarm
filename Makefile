#OBJS specifies which files to compile as part of the project 

OBJS = MapEditWindow.o MapEditEntity.o MapEditMap.o MapEditTimer.o MapEditGameState.o MapEditCameraController.o MapEditMenu.o MapEditButton.o

# Kompilator (gcc) och diagnostikfilter (gccfilter)
CCC = g++

#INCLUDE_PATHS specifies the additional include paths we'll need 
INCLUDE_PATHS = -ID:\mingw_dev_lib\include\SDL2

#LIBRARY_PATHS specifies the additional library paths we'll need 
LIBRARY_PATHS = -LD:\mingw_dev_lib\lib

#COMPILER_FLAGS specifies the additional compilation options we're using 
# -w suppresses all warnings
# -Wl,-subsystem,windows gets rid of the console window 
CCFLAGS = -w -std=c++11 -Wpedantic -Wall -Wextra

NOWINDOW = -Wl,-subsystem,windows

#LINKER_FLAGS specifies the libraries we're linking against 
LINKER_FLAGS = -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf

STATIC = -static-libgcc -static-libstdc++


#This is the target that compiles our executable
all : MapEditmain.cc $(OBJS) Makefile
	$(CCC) MapEditMain.cc $(OBJS) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(CCFLAGS) $(LINKER_FLAGS) -o Main
	
all-w : MapEditmain.cc $(OBJS) Makefile
	$(CCC) MapEditMain.cc $(OBJS) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(CCFLAGS) $(NOWINDOW) $(LINKER_FLAGS) -o Main

all-s : MapEditmain.cc $(OBJS) Makefile
	$(CCC) MapEditMain.cc $(OBJS) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(CCFLAGS) $(LINKER_FLAGS) $(STATIC) -o Main
	
all-sw : MapEditmain.cc $(OBJS) Makefile
	$(CCC) MapEditMain.cc $(OBJS) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(CCFLAGS) $(NOWINDOW) $(LINKER_FLAGS) $(STATIC) -o Main

MapEditWindow.o: MapEditWindow.h MapEditWindow.cc
	$(CCC) MapEditWindow.cc $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(CCFLAGS) $(LINKER_FLAGS) -c 

MapEditMap.o: MapEditMap.h MapEditMap.cc
	$(CCC) MapEditMap.cc $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(CCFLAGS) $(LINKER_FLAGS) -c

MapEditEntity.o: MapEditEntity.h MapEditEntity.cc
	$(CCC) MapEditEntity.cc $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(CCFLAGS) $(LINKER_FLAGS) -c
	
MapEditTimer.o: MapEditTimer.h MapEditTimer.cc
	$(CCC) MapEditTimer.cc $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(CCFLAGS) $(LINKER_FLAGS) -c
	
MapEditGameState.o: MapEditGameState.h MapEditGameState.cc
	$(CCC) MapEditGamestate.cc $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(CCFLAGS) $(LINKER_FLAGS) -c
	
MapEditCameraController.o: MapEditCameraController.h MapEditCameraController.cc
	$(CCC) MapEditCameraController.cc $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(CCFLAGS) $(LINKER_FLAGS) -c
		
MapEditMenu.o: MapEditMenu.h MapEditMenu.cc
	$(CCC) MapEditMenu.cc $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(CCFLAGS) $(LINKER_FLAGS) -c

MapEditButton.o: MapEditButton.h MapEditButton.cc
	$(CCC) MapEditButton.cc $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(CCFLAGS) $(LINKER_FLAGS) -c
	