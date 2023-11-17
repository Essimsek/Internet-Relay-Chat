NAME = ircserv

CC = g++
CFLAGS = -std=c++98 -Wall -Wextra -Werror

SRC_DIR = ./srcs
INC_DIR = ./inc

SRC_FILES = $(SRC_DIR)/main.cpp $(SRC_DIR)/server/Server.cpp

OBJ_FILES = $(SRC_FILES:%.cpp=%.o)

INC_FILES = ./inc/Server.hpp
INC_FLAGS = -I$(INC_DIR)

all: $(NAME)

$(NAME): $(OBJ_FILES)
	$(CC) $(CFLAGS) $(OBJ_FILES) -o $(NAME)

.PHONY: clean

clean:
	rm -rf ./srcs/server/*.o
	rm -rf ./srcs/*.o

fclean: clean
	rm -f $(NAME)

re: fclean all
