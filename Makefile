# Name of the executable
NAME     = webserv

# Compiler and compiler flags
GCC      = g++
CFLAGS   = -Wall -Wextra -Werror -std=c++98  #-g -fsanitize=address
RM       = rm -rf

# Directories
SRC      = srcs
OBJ      = objects
SUBDIRS  = server main parsing

# Directory paths
SRC_DIR  = $(addprefix $(SRC)/,$(SUBDIRS))
OBJ_DIR  = $(addprefix $(OBJ)/,$(SUBDIRS))

# Source and object files
SRCS     = $(foreach dir,$(SRC_DIR),$(wildcard $(dir)/*.cpp))
OBJS     = $(patsubst $(SRC)/%.cpp,$(OBJ)/%.o,$(SRCS))

# Include directories
LIBS     = -I./includes/

# Make targets
all: $(NAME)

$(NAME): Makefile $(OBJS)
	$(GCC) -o $(NAME) $(OBJS) $(CFLAGS) $(LIBS)

$(OBJ)/%.o: $(SRC)/%.cpp
	mkdir -p $(@D)
	$(GCC) $(CFLAGS) $(LIBS) -c $< -o $@

clean:
	$(RM) $(OBJ_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re

