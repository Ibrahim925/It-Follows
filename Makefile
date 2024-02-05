CC       =clang++                  # Compiler
CCFLAGS  =-Wall                  # Compiler flags
STD      =c++17                    # Standard
SRC      =$(shell find src -name '*.cpp')  # Source files
INC      =inc                    # Include path for headers
BIN      =ItFollows              # Binary name
SDL_INC  =/opt/homebrew/include
SDL_LIB_PATH =/opt/homebrew/lib
SDL_LIB  =SDL2
SDL_IMAGE_LIB=SDL2_image
SDL_TTF_LIB=SDL2_ttf

default: build

build:
	$(CC) -std=$(STD) $(CCFLAGS) $(SRC) -I$(INC) -I$(SDL_INC) -L$(SDL_LIB_PATH) -l$(SDL_LIB) -l$(SDL_IMAGE_LIB) -l$(SDL_TTF_LIB) -o ./bin/$(BIN)

