CC	= cc
CFLAGS = -Wall -Wextra -Iinc -g3

SRC_DIR		= srcs
OBJ_DIR 	= obj

SRC			= parser.c\
			  pipex.c\
			  gen_cmd.c\
			  free_memory.c\
			  init_memory.c\
			  init_pipe.c\
			  close_pipe.c\
			  dup.c\
			  dispatch.c\
			  exec_cmd.c\
			  error.c\

NAME		= pipex

OBJ			= $(SRC:%.c=$(OBJ_DIR)/%.o)

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

all: $(NAME)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ) -Llibft -lft -o $(NAME)

$(LIBFT):
	echo "Making libft"
	@make -C libft bonus

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)
	make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
