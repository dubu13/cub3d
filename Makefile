# Name of the binary
NAME     = so_long

NAME_BONUS = so_long_bonus

# Compiler and flags
CC       = cc
CFLAGS   = -Wall -Werror -Wextra -g

# MLX42 Flags
MLXFLAGS = -ldl -lglfw -pthread -lm

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
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(MLX) $(MLXFLAGS) $(HEADER)
	@echo $(GREEN)"Building $(NAME)"$(DEFAULT);

# MLX42 library
$(MLX):
	@if [ ! -d "MLX42" ]; then \
      git clone https://github.com/codam-coding-college/MLX42.git && \
      cd MLX42 && cmake -B build && cmake --build build -j4; \
	fi

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

#Linking libft
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

re_bonus: fclean bonus
.PHONY: all clean fclean re re_bonus

# Colours
DEFAULT = "\033[39m"
GREEN   = "\033[32m"
RED     = "\033[31m"