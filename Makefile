MAIN_FILE = Main
STAGE_FILE = Stage
BC_FILE = BlockCharacter
OTHER_FILE = Other

EXE_NAME = Game

$(EXE_NAME) : $(MAIN_FILE).o $(STAGE_FILE).o $(BC_FILE).o $(OTHER_FILE).o
	g++ $(MAIN_FILE).o $(STAGE_FILE).o $(BC_FILE).o $(OTHER_FILE).o -lsfml-graphics -lsfml-window -lsfml-system -o$(EXE_NAME)

$(MAIN_FILE).o :
	g++ -c $(MAIN_FILE).cpp -o $(MAIN_FILE).o

$(STAGE_FILE).o :
	g++ -c $(STAGE_FILE).cpp -o $(STAGE_FILE).o

$(BC_FILE).o :
	g++ -c $(BC_FILE).cpp -o $(BC_FILE).o

$(OTHER_FILE).o :
	g++ -c $(OTHER_FILE).cpp -o $(OTHER_FILE).o
