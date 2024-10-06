# Name of the binary
NAME     = cub3d

# Compiler and flags
CC       = cc
CFLAGS   = -Wall -Werror -Wextra -g -I. -fsanitize=address

# MLX42 Flags
MLXFLAGS = -lm -lglfw -lpthread

LIBFT = ./libft/libft.a

# Binary Folder
BINDIR = bin

# Source files
SRCS     = $(wildcard *.c parser/*.c)

# Object files (automatically place objects in the same subdirectory structure under BINDIR)
OBJS     = $(SRCS:%.c=$(BINDIR)/%.o)

# MLX42 library
MLX      = ./MLX42/build/libmlx42.a 

# Default target
all: $(NAME)

$(NAME): $(LIBFT) $(MLX) $(OBJS)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT) $(MLX) $(MLXFLAGS)
	@echo $(GREEN)"Building $(NAME)"$(DEFAULT);

# Create bin directories if they don't exist
$(BINDIR):
	@mkdir -p $(BINDIR) $(BINDIR)/parser

# MLX42 library
$(MLX):
	@if [ ! -d "MLX42" ]; then \
      git clone https://github.com/codam-coding-college/MLX42.git && \
      cd MLX42 && cmake -B build && cmake --build build -j4; \
	fi

# Compile .c files into .o files
$(BINDIR)/%.o: %.c | $(BINDIR)
	@mkdir -p $(dir $@)  # Ensure any needed subdirectories are created
	@$(CC) $(CFLAGS) -c $< -o $@

# Linking libft
$(LIBFT):
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
	@echo $(RED)"Removing $(NAME) and MLX42"$(DEFAULT);

# Rebuild everything
re: fclean all
	@echo $(GREEN)"Rebuilding everything"$(DEFAULT);

.PHONY: all clean fclean re

# Colours
DEFAULT = "\033[39m"
GREEN   = "\033[32m"
RED     = "\033[31m"

