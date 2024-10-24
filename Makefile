# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sait-amm <sait-amm@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/02 12:49:12 by sait-amm          #+#    #+#              #
#    Updated: 2024/10/24 11:45:46 by sait-amm         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC =  minishell.c \
		parsing/src/parce_error.c \
		parsing/src/print_error.c \
		parsing/src/redirection_in.c \
		parsing/src/redirection_out.c \
		parsing/src/ft_split_pipe.c \
		parsing/src/add_cmd.c \
		parsing/src/add_file.c \
		parsing/src/add_file_2.c \
		parsing/src/add_data.c \
		parsing/src/free_function.c \
		parsing/src/fun_file.c \
		parsing/src/help_quote.c \
		parsing/src/expand.c \
		parsing/src/ft_split_whitespace.c \
		parsing/src/help_expand.c \
		parsing/src/to_final_struct.c \
		parsing/src/her_doc.c\
		parsing/src/help_herdoc.c \
		parsing/src/helper_func.c \
		execution/echo.c \
		execution/env.c \
		execution/builtins.c \
 		execution/env_struct.c \
		execution/env_struct2.c \
		execution/pwd.c \
		execution/cd.c \
		execution/cd2.c \
		execution/ft_libft.c \
		execution/execution.c \
		execution/execution2.c \
		execution/unset.c \
		execution/export.c \
		execution/redirection.c \
		execution/exit.c \
		execution/export2.c \
		execution/get_path.c \
		execution/free.c \
		execution/function_size.c \
		execution/signals.c \
		execution/signals_herdoc.c \
		execution/exit_function_built.c \
		execution/export3.c \
		execution/intfile.c \
		execution/intfile2.c \
		execution/outfile.c \
		execution/outfile2.c \
		execution/get_path2.c \
		execution/execute_child.c \
		execution/execute_child2.c \
		execution/built_redirection.c \
		execution/exec_child.c \
		execution/close.c \
		execution/close2.c \
		
LIBFT_DIR=libft
LIBFT_LIB=$(LIBFT_DIR)/libft.a
NAME = minishell
INCLUDES = -I . -I include -I $(LIBFT_DIR)  

C = cc

CFLAGS =  -Wall -Werror -Wextra -g3 #-fsanitize=address 

all: $(NAME)

$(NAME): $(SRC) $(LIBFT_LIB)
	$(CC) $(CFLAGS) $(SRC) -lreadline  $(LIBFT_LIB) -o $(NAME)

$(LIBFT_LIB):
	@$(MAKE) -C $(LIBFT_DIR)
clean:
	$(MAKE) -C $(LIBFT_DIR) clean
fclean: clean
	rm -rf $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean


re: fclean all

.PHONY: all clean fclean re
