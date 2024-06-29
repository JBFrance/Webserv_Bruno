NAME     = webserv
GCC      = c++
CFLAGS   = -Wall -Wextra -Werror -std=c++98  #-g -fsanitize=address
RM       = rm -rf
OUTPUT   = ./$(NAME)
LIBS     = -I./includes/

# Compiled directories
SRC = srcs
OBJ = objects
SUBDIRS = server main

# Folder directions
SRC_DIR = $(foreach dir, $(SUBDIRS), $(addprefix $(SRC)/, $(dir)))
OBJ_DIR = $(foreach dir, $(SUBDIRS), $(addprefix $(OBJ)/, $(dir)))

# File directions
SRCS = $(foreach dir, $(SRC_DIR), $(wildcard $(dir)/*.cpp))
OBJS = $(subst $(SRC), $(OBJ), $(SRCS:.cpp=.o))

all: $(NAME)

$(NAME): Makefile $(OBJS)
	$(GCC) -o $(NAME) $(OBJS) -g $(CFLAGS) $(LIBS)

$(OBJ)/%.o: $(SRC)/%.cpp
	mkdir -p $(OBJ) $(OBJ_DIR)
	$(GCC) $(CFLAGS) $(LIBS) -c $< -o $@

clean:
	$(RM) $(OBJ_DIR)
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all
