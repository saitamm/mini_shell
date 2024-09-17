# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sait-amm <sait-amm@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/02 12:49:12 by sait-amm          #+#    #+#              #
#    Updated: 2024/09/17 17:25:08 by sait-amm         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC =  minishell.c \
		parsing/src/parce_error.c \
		parsing/src/print_error.c \
		parsing/src/redirection_in.c \
		parsing/src/redirection_out.c \
		parsing/src/ft_split_pipe.c \
		parsing/src/init_struct.c \
		parsing/src/add_fun.c \
		parsing/src/fun_file.c \
		parsing/src/help_quote.c \
		parsing/src/expand.c \
		parsing/src/ft_split_whitespace.c \
		parsing/src/help_expand.c \
		parsing/src/to_final_struct.c \
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
		execution/export2.c \
		execution/exit.c \
		parsing/src/her_doc.c

OBJF = $(SRC:.c=.o)
LIBFT_DIR=libft
LIBFT_LIB=$(LIBFT_DIR)/libft.a
NAME = minishell
INCLUDES = -I . -I include -I $(LIBFT_DIR)  

C = cc

CFLAGS =  -Wall -Werror -Wextra -g3 -fsanitize=address 

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
