#OBJS specifies which files to compile as part of the project 

OBJS = Window.o Entity.o Map.o Timer.o GameState.o CameraController.o EditMenu.o

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
all : main.cc $(OBJS) Makefile
	$(CCC) Main.cc $(OBJS) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(CCFLAGS) $(LINKER_FLAGS) -o Main
	
all-w : main.cc $(OBJS) Makefile
	$(CCC) Main.cc $(OBJS) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(CCFLAGS) $(NOWINDOW) $(LINKER_FLAGS) -o Main

all-s : main.cc $(OBJS) Makefile
	$(CCC) Main.cc $(OBJS) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(CCFLAGS) $(LINKER_FLAGS) $(STATIC) -o Main
	
all-sw : main.cc $(OBJS) Makefile
	$(CCC) Main.cc $(OBJS) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(CCFLAGS) $(NOWINDOW) $(LINKER_FLAGS) $(STATIC) -o Main

Window.o: Window.h Window.cc
	$(CCC) Window.cc $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(CCFLAGS) $(LINKER_FLAGS) -c 

Map.o: Map.h Map.cc
	$(CCC) Map.cc $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(CCFLAGS) $(LINKER_FLAGS) -c

Entity.o: Entity.h Entity.cc
	$(CCC) Entity.cc $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(CCFLAGS) $(LINKER_FLAGS) -c
	
Timer.o: Timer.h Timer.cc
	$(CCC) Timer.cc $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(CCFLAGS) $(LINKER_FLAGS) -c
	
GameState.o: GameState.h GameState.cc
	$(CCC) Gamestate.cc $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(CCFLAGS) $(LINKER_FLAGS) -c
	
CameraController.o: CameraController.h CameraController.cc
	$(CCC) CameraController.cc $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(CCFLAGS) $(LINKER_FLAGS) -c
		
EditMenu.o: EditMenu.h EditMenu.cc
	$(CCC) EditMenu.cc $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(CCFLAGS) $(LINKER_FLAGS) -c
	