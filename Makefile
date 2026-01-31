NAME_SERVER = server
NAME_CLIENT = client

CC = cc
CFLAGS	= -Wall -Wextra -Werror -I includes

SRC_DIR	= srcs
OBJ_DIR	= objs
INC_DIR	= includes
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

SRCS_FILES	= server_bonus.c \
			  client_bonus.c \
			  utils_minitalk_bonus.c

OBJS		= $(addprefix $(OBJ_DIR)/, $(SRCS_FILES:.c=.o))

all: $(NAME_SERVER) $(NAME_CLIENT)

bonus: $(NAME_SERVER) $(NAME_SERVER)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(NAME_SERVER): $(LIBFT) $(OBJ_DIR)/server_bonus.o $(OBJ_DIR)/utils_minitalk_bonus.o
	$(CC) $(CFLAGS) $(OBJ_DIR)/server_bonus.o $(OBJ_DIR)/utils_minitalk_bonus.o -L$(LIBFT_DIR) -lft -o $(NAME_SERVER)

$(NAME_CLIENT): $(LIBFT) $(OBJ_DIR)/client_bonus.o $(OBJ_DIR)/utils_minitalk_bonus.o
	$(CC) $(CFLAGS) $(OBJ_DIR)/client_bonus.o $(OBJ_DIR)/utils_minitalk_bonus.o -L$(LIBFT_DIR) -lft -o $(NAME_CLIENT)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME_SERVER) $(NAME_CLIENT)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re bonus
