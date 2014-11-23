#OBJS specifies which files to compile as part of the project 
OBJS = SDLWindow.o SDLSurface.o

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

#LINKER_FLAGS specifies the libraries we're linking against 
LINKER_FLAGS = -lmingw32 -lSDL2main -lSDL2

#This is the target that compiles our executable
all : main.cc $(OBJS) Makefile
	$(CCC) Main.cc $(OBJS) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(CCFLAGS) $(LINKER_FLAGS) -o Main

SDLWindow.o: SDLWindow.h SDLWindow.cc
	$(CCC) SDLWindow.cc $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(CCFLAGS) $(LINKER_FLAGS) -c 

SDLSurface.o: SDLSurface.h SDLSurface.cc
	$(CCC) SDLSurface.cc $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(CCFLAGS) $(LINKER_FLAGS) -c