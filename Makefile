NAME = ircserv

CC = c++
CFLAGS = -std=c++98 -Wall -Wextra -Werror

SRC_DIR = ./srcs
INC_DIR = ./inc

SRC_FILES = $(SRC_DIR)/main.cpp  $(SRC_DIR)/run.cpp $(SRC_DIR)/server/Server.cpp $(SRC_DIR)/client/Client.cpp $(SRC_DIR)/commands/Join.cpp $(SRC_DIR)/channel/Channel.cpp

OBJ_FILES = $(SRC_FILES:%.cpp=%.o)

INC_FILES = $(INC_DIR)/Server.hpp
INC_FLAGS = -I$(INC_DIR)

all: $(NAME)

$(NAME): $(OBJ_FILES)
	$(CC) $(CFLAGS) $(OBJ_FILES) -o $(NAME)

.PHONY: clean

clean:
	rm -rf ./srcs/server/*.o
	rm -rf ./srcs/*.o
	rm -rf ./srcs/client/*.o

fclean: clean
	rm -f $(NAME)

re: fclean all