MAIN_FILE = Main.cpp
STAGE_FILE = Stage.cpp
BC_FILE = BlockCharacter.cpp
OTHER_FILE = Other.cpp

EXE_NAME = Game

all : $(MAIN_FILE) $(STAGE_FILE) $(BC_FILE) $(OTHER_FILE)
	g++ $(MAIN_FILE) $(STAGE_FILE) $(BC_FILE) $(OTHER_FILE) -lsfml-graphics -lsfml-window -lsfml-system -o$(EXE_NAME)
