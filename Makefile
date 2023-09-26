.DEFAULT_GOAL := main.out

CC = g++
FLAGS = -std=c++11 -g
LIBS  = -lsdlgl -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -lpthread -lm -ldl


OBJ_FILES = main.o \
			entities/dialogue.o \
			components/voice.o \


clean:
	rm -f *.out *.o
	rm -f entities/*.out entities/*.o
	rm -f components/*.out components/*.o

main.out: $(OBJ_FILES)
	$(CC) $(FLAGS) -o main.out $(OBJ_FILES) $(LIBS)

%.o: %.cpp
	$(CC) $(FLAGS) -c $< -o $@

all: main.out