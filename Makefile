#OBJS specifies which files to compile as part of the project 
OBJS = SDLWindow.o Entity.o Map.o Timer.o Controller.o

# Kompilator (gcc) och diagnostikfilter (gccfilter)
CCC = g++

#INCLUDE_PATHS specifies the additional include paths we'll need 
INCLUDE_PATHS = -IC:\mingw_dev_lib\include\SDL2

#LIBRARY_PATHS specifies the additional library paths we'll need 
LIBRARY_PATHS = -LC:\mingw_dev_lib\lib

#COMPILER_FLAGS specifies the additional compilation options we're using 
# -w suppresses all warnings
# -Wl,-subsystem,windows gets rid of the console window 
CCFLAGS = -w -std=c++11 -Wpedantic -Wall -Wextra

NOWINDOW = -Wl,-subsystem,windows

#LINKER_FLAGS specifies the libraries we're linking against 
LINKER_FLAGS = -lmingw32 -lSDL2main -lSDL2 -lSDL2_image

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

SDLWindow.o: SDLWindow.h SDLWindow.cc
	$(CCC) SDLWindow.cc $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(CCFLAGS) $(LINKER_FLAGS) -c 

Map.o: Map.h Entity.o Map.cc
	$(CCC) Map.cc $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(CCFLAGS) $(LINKER_FLAGS) -c
	
Controller.o: Controller.h Entity.o Controller.cc
	$(CCC) Controller.cc $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(CCFLAGS) $(LINKER_FLAGS) -c

Entity.o: Entity.h Entity.cc
	$(CCC) Entity.cc $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(CCFLAGS) $(LINKER_FLAGS) -c
	
Timer.o: Timer.h Timer.cc
	$(CCC) Timer.cc $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(CCFLAGS) $(LINKER_FLAGS) -c
	