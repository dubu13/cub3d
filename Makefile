# Name of the binary
NAME     = cub3D

# Compiler and flags
CC       = cc
CFLAGS   = -Wall -Werror -Wextra -g -I./inc

# MLX42 Flags
MLXFLAGS = -lm -lglfw -lpthread

LIBFT = ./libft/libft.a

# Binary Folder
BINDIR = bin

# Source files
SRCS     = src/main.c src/msg_free.c \
					 src/parsing/map_utils.c \
					 src/parsing/parser.c \
						src/parsing/parser_utils.c \
						src/parsing/checker.c \
						src/parsing/map_checker.c \
  					src/execution/movement.c \
 						src/execution/raycasting.c \
	 					src/execution/raycasting_utils.c \
 						src/execution/rendering.c \
 						src/execution/rendering_utils.c \

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
	@mkdir -p $(BINDIR) $(BINDIR)src/parsing $(BINDIR)src/execution

# MLX42 library
$(MLX):
	@if [ ! -d "MLX42" ]; then \
      git clone https://github.com/codam-coding-college/MLX42.git && \
      cd MLX42 && git checkout tags/v2.3.4 && cmake -B build && cmake --build build -j4; \
	fi

# Compile .c files into .o files
$(BINDIR)/%.o: %.c | $(BINDIR)
	@mkdir -p $(dir $@)  # Ensure any needed subdirectories are created
	@$(CC) $(CFLAGS) -c $< -o $@

# Linking libft
$(LIBFT):
	@if [ ! -d "libft" ]; then \
		echo "Cloning libft..."; \
		git clone git@github.com:ygalsk/libft.git libft && \
		git submodule update --init --recursive && \
		make -C libft; \
	else \
		make -C libft; \
	fi

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

