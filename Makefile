# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sait-amm <sait-amm@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/02 12:49:12 by sait-amm          #+#    #+#              #
#    Updated: 2024/08/30 11:30:04 by sait-amm         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = minishell.c \
		src/parce_error.c \
		src/print_error.c \
		src/redirection_in.c \
		src/redirection_out.c \
		src/ft_split_pipe.c \
		src/init_struct.c \
		src/add_fun.c \
		src/fun_file.c \
		src/help_quote.c \
		laila/env_struct.c \
		src/expand.c \
		src/ft_split_whitespace.c \
		src/help_expand.c \
		src/to_final_struct.c

OBJF = $(SRC:.c=.o)
LIBFT_DIR=libft
LIBFT_LIB=$(LIBFT_DIR)/libft.a
NAME = minishell
INCLUDES = -I . -I include -I $(LIBFT_DIR)  

C = cc

CFLAGS =  -Wall -Werror -Wextra #-fsanitize=address -g3

all: $(NAME)

$(NAME): $(OBJF) $(LIBFT_LIB)
	$(CC) $(CFLAGS) -lreadline $(OBJF) $(LIBFT_LIB) -o $(NAME)


$(LIBFT_LIB):
	@$(MAKE) -C $(LIBFT_DIR)
%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
clean:
	rm -rf $(OBJF)
	$(MAKE) -C $(LIBFT_DIR) clean
fclean: clean
	rm -rf $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean


re: fclean all

.PHONY: all clean fclean re