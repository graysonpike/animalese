.DEFAULT_GOAL := main.out

CC = g++
FLAGS = -std=c++11 -g
LIBS  = -lsdlgl -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -lpthread -lm -ldl


OBJ_FILES = main.o \
			entities/dialogue.o \
			entities/conversation.o \
			components/voice.o \
			components/typewriter.o \
			utilities/text_utils.o


clean:
	rm -f *.out *.o
	rm -f entities/*.out entities/*.o
	rm -f components/*.out components/*.o
	rm -f utilities/*.out utilities/*.o

main.out: $(OBJ_FILES)
	$(CC) $(FLAGS) -o main.out $(OBJ_FILES) $(LIBS)

%.o: %.cpp
	$(CC) $(FLAGS) -c $< -o $@

all: main.out