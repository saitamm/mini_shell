# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lai-elho <lai-elho@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/02 12:49:12 by sait-amm          #+#    #+#              #
#    Updated: 2024/09/11 11:14:56 by lai-elho         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC =  minishell.c \
		parting/src/parce_error.c \
		parting/src/print_error.c \
		parting/src/redirection_in.c \
		parting/src/redirection_out.c \
		parting/src/ft_split_pipe.c \
		parting/src/init_struct.c \
		parting/src/add_fun.c \
		parting/src/fun_file.c \
		parting/src/help_quote.c \
		parting/src/expand.c \
		parting/src/ft_split_whitespace.c \
		parting/src/help_expand.c \
		parting/src/to_final_struct.c \
		execution/echo.c \
		execution/env.c \
		execution/builtins.c \
 		execution/env_struct.c \
		execution/pwd.c \
		execution/cd.c \
		execution/ft_libft.c \
		execution/execution.c \
		execution/unset.c \
		execution/export.c \
		execution/exit.c \
		execution/export2.c


OBJF = $(SRC:.c=.o)
LIBFT_DIR=libft
LIBFT_LIB=$(LIBFT_DIR)/libft.a
NAME = minishell
INCLUDES = -I . -I include -I $(LIBFT_DIR)  

C = cc

CFLAGS =  -Wall -Werror -Wextra -g3 #-fsanitize=address 

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
