NAME = ircserv
CC = c++
CFLAGS = -std=c++98 -Wall -Wextra -Werror
SRC_DIR = ./srcs
INC_DIR = ./inc
SRC_FILES = $(SRC_DIR)/main.cpp  $(SRC_DIR)/run.cpp $(SRC_DIR)/server/Server.cpp \
			$(SRC_DIR)/client/Client.cpp  $(SRC_DIR)/channel/Channel.cpp \
			$(SRC_DIR)/commands/Join.cpp $(SRC_DIR)/commands/PrivMsg.cpp \
			$(SRC_DIR)/utils/utils.cpp $(SRC_DIR)/commands/Kick.cpp \
			$(SRC_DIR)/commands/Notice.cpp $(SRC_DIR)/commands/Quit.cpp \
			$(SRC_DIR)/commands/AssignAdmin.cpp

OBJ_FILES = $(SRC_FILES:%.cpp=%.o)
INC_FILES = $(INC_DIR)/Server.hpp
INC_FLAGS = -I$(INC_DIR)

all: $(NAME)

$(NAME): $(OBJ_FILES)
	$(CC) $(CFLAGS) $(OBJ_FILES) -o $(NAME)

dep:
	$(CC) -MM $(SRC_FILES) > dependencies

-include dependencies

.PHONY: clean dep all

clean:
	rm -rf ./srcs/server/*.o
	rm -rf ./srcs/*.o
	rm -rf ./srcs/client/*.o
	rm -rf ./srcs/commands/*.o
	rm -rf ./srcs/channel/*.o
	rm -rf ./srcs/utils/*.o
	rm -f dependencies

fclean: clean
	rm -f $(NAME)

re: fclean all
