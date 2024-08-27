# Name of the binary
NAME     = cub3d

# Compiler and flags
CC       = cc
CFLAGS   = -Wall -Werror -Wextra -g

# MLX42 Flags
MLXFLAGS = -lXext -lX11 -lm -lbsd -lglfw -lpthread

LIBFT = ./libft/libft.a

# Binary Folder
BINDIR = bin

# Source files
SRCS     = $(wildcard *.c)

# Object files
OBJS     = $(SRCS:%.c=$(BINDIR)/%.o)

# MLX42 library
MLX      = ./MLX42/build/libmlx42.a 

# Default target
all: $(NAME)

$(NAME): $(HEADER) $(MLX) $(OBJS)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT) $(MLX) $(MLXFLAGS) $(HEADER)
	@echo $(GREEN)"Building $(NAME)"$(DEFAULT);

# Create bin directory if it doesn't exist
$(BINDIR):
	@mkdir -p $(BINDIR)

# MLX42 library
$(MLX):
	@if [ ! -d "MLX42" ]; then \
      git clone https://github.com/codam-coding-college/MLX42.git && \
      cd MLX42 && cmake -B build && cmake --build build -j4; \
	fi

# Compile .c files into .o files
$(BINDIR)/%.o: %.c | $(BINDIR)
	@$(CC) $(CFLAGS) -c $< -o $@

# Linking libft
$(HEADER):
	@make -C libft

submodule:
	git submodule update --init --recursive

# Remove all object files
clean:
	@rm -rf $(BINDIR)
	@make -C libft clean
	@echo $(RED)"Removing $(NAME) object files"$(DEFAULT);

# Remove all files
fclean: clean
	@rm -f $(NAME)
	@rm -rf MLX42
	@make -C libft fclean
	@echo $(RED)"Removing $(NAME) and MLX42 "$(DEFAULT);

# Rebuild everything
re: fclean all
	@echo $(GREEN)"Rebuilding everything"$(DEFAULT);

.PHONY: all clean fclean re

# Colours
DEFAULT = "\033[39m"
GREEN   = "\033[32m"
RED     = "\033[31m"
