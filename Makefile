NAME_SERVER = server
NAME_CLIENT = client
NAME_SERVER_BONUS = server_bonus
NAME_CLIENT_BONUS = client_bonus

CC = cc
CFLAGS	= -Wall -Wextra -Werror -I includes

SRC_DIR	= srcs
OBJ_DIR	= objs
INC_DIR	= includes
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

SRCS_FILES	= server.c \
			  client.c \
			  utils_minitalk.c

SRCS_BONUS_FILES = server_bonus.c \
				   client_bonus.c \
				   utils_minitalk_bonus.c

OBJS		= $(addprefix $(OBJ_DIR)/, $(SRCS_FILES:.c=.o))
OBJS_BONUS	= $(addprefix $(OBJ_DIR)/, $(SRCS_BONUS_FILES:.c=.o))

all: $(NAME_SERVER) $(NAME_CLIENT)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(NAME_SERVER): $(LIBFT) $(OBJ_DIR)/server.o $(OBJ_DIR)/utils_minitalk.o
	$(CC) $(CFLAGS) $(OBJ_DIR)/server.o $(OBJ_DIR)/utils_minitalk.o -L$(LIBFT_DIR) -lft -o $(NAME_SERVER)

$(NAME_CLIENT): $(LIBFT) $(OBJ_DIR)/client.o $(OBJ_DIR)/utils_minitalk.o
	$(CC) $(CFLAGS) $(OBJ_DIR)/client.o $(OBJ_DIR)/utils_minitalk.o -L$(LIBFT_DIR) -lft -o $(NAME_CLIENT)

bonus: $(NAME_SERVER_BONUS) $(NAME_CLIENT_BONUS)

$(NAME_SERVER_BONUS): $(LIBFT) $(OBJ_DIR)/server_bonus.o $(OBJ_DIR)/utils_minitalk_bonus.o
	$(CC) $(CFLAGS) $(OBJ_DIR)/server_bonus.o $(OBJ_DIR)/utils_minitalk_bonus.o -L$(LIBFT_DIR) -lft -o $(NAME_SERVER_BONUS)

$(NAME_CLIENT_BONUS): $(LIBFT) $(OBJ_DIR)/client_bonus.o $(OBJ_DIR)/utils_minitalk_bonus.o
	$(CC) $(CFLAGS) $(OBJ_DIR)/client_bonus.o $(OBJ_DIR)/utils_minitalk_bonus.o -L$(LIBFT_DIR) -lft -o $(NAME_CLIENT_BONUS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME_SERVER) $(NAME_CLIENT) $(NAME_SERVER_BONUS) $(NAME_CLIENT_BONUS)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re bonus