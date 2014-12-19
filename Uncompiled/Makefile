#OBJS specifies which files to compile as part of the project 

OBJS = Play.o Menu.o Window.o Entity.o Map.o Timer.o Texture.o Button.o Game.o Submit.o
OBJS-ME = MapEditEntity.o MapEditMap.o MapEditTimer.o Edit.o MapEditCameraController.o MapEditMenu.o MapEditButton.o

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
LINKER_FLAGS = -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf

STATIC = -static-libgcc -static-libstdc++


#This is the target that compiles our executable
all : main.cc $(OBJS) $(OBJS-ME) Makefile
	$(CCC) Main.cc $(OBJS) $(OBJS-ME)  $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(CCFLAGS) $(LINKER_FLAGS) -o ZombeeSwarm
	
all-w : main.cc $(OBJS) $(OBJS-ME) Makefile
	$(CCC) Main.cc $(OBJS) $(OBJS-ME)  $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(CCFLAGS) $(NOWINDOW) $(LINKER_FLAGS) -o ZombeeSwarm

all-s : main.cc $(OBJS) $(OBJS-ME) Makefile
	$(CCC) Main.cc $(OBJS) $(OBJS-ME) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(CCFLAGS) $(LINKER_FLAGS) $(STATIC) -o ZombeeSwarm
	
all-sw : main.cc $(OBJS) $(OBJS-ME) Makefile
	$(CCC) Main.cc $(OBJS) $(OBJS-ME) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(CCFLAGS) $(NOWINDOW) $(LINKER_FLAGS) $(STATIC) -o ZombeeSwarm

Window.o: Window.h Window.cc
	$(CCC) Window.cc $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(CCFLAGS) $(LINKER_FLAGS) -c 

Map.o: Map.h Map.cc
	$(CCC) Map.cc $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(CCFLAGS) $(LINKER_FLAGS) -c

Entity.o: Entity.h Entity.cc
	$(CCC) Entity.cc $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(CCFLAGS) $(LINKER_FLAGS) -c
	
Timer.o: Timer.h Timer.cc
	$(CCC) Timer.cc $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(CCFLAGS) $(LINKER_FLAGS) -c
	
Play.o: Play.h Play.cc
	$(CCC) Play.cc $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(CCFLAGS) $(LINKER_FLAGS) -c
	
Menu.o: Menu.h Menu.cc
	$(CCC) Menu.cc $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(CCFLAGS) $(LINKER_FLAGS) -c

Texture.o: Texture.h Texture.cc
	$(CCC) Texture.cc $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(CCFLAGS) $(LINKER_FLAGS) -c
	
Button.o: Button.h Button.cc
	$(CCC) Button.cc $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(CCFLAGS) $(LINKER_FLAGS) -c
	
Game.o: Game.h Game.cc
	$(CCC) Game.cc $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(CCFLAGS) $(LINKER_FLAGS) -c
	
Submit.o: Submit.h Submit.cc
	$(CCC) Submit.cc $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(CCFLAGS) $(LINKER_FLAGS) -c

MapEditMap.o: MapEditMap.h MapEditMap.cc
	$(CCC) MapEditMap.cc $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(CCFLAGS) $(LINKER_FLAGS) -c
	
Edit.o: Edit.h Edit.cc
	$(CCC) Edit.cc $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(CCFLAGS) $(LINKER_FLAGS) -c

MapEditEntity.o: MapEditEntity.h MapEditEntity.cc
	$(CCC) MapEditEntity.cc $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(CCFLAGS) $(LINKER_FLAGS) -c
	
MapEditTimer.o: MapEditTimer.h MapEditTimer.cc
	$(CCC) MapEditTimer.cc $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(CCFLAGS) $(LINKER_FLAGS) -c
	
MapEditCameraController.o: MapEditCameraController.h MapEditCameraController.cc
	$(CCC) MapEditCameraController.cc $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(CCFLAGS) $(LINKER_FLAGS) -c
		
MapEditMenu.o: MapEditMenu.h MapEditMenu.cc
	$(CCC) MapEditMenu.cc $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(CCFLAGS) $(LINKER_FLAGS) -c

MapEditButton.o: MapEditButton.h MapEditButton.cc
	$(CCC) MapEditButton.cc $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(CCFLAGS) $(LINKER_FLAGS) -c
