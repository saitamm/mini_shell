# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lai-elho <lai-elho@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/02 12:49:12 by sait-amm          #+#    #+#              #
#    Updated: 2024/08/29 21:30:41 by lai-elho         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# SRC =  minishell.c \
# 		parting/src/parce_error.c \
# 		parting/src/print_error.c \
# 		parting/src/redirection_in.c \
# 		parting/src/redirection_out.c \
# 		parting/src/ft_split_pipe.c \
# 		parting/src/init_struct.c \
# 		parting/src/add_fun.c \
# 		parting/src/fun_file.c \
# 		parting/src/help_quote.c \
# 		parting/src/expand.c \
# 		parting/src/ft_split_whitespace.c \
# 		parting/src/help_expand.c \
# 		execution/echo.c \
# 		execution/env.c \
# 		execution/builtins.c \
#  		execution/env_struct.c \
# 		execution/pwd.c \
# 		execution/cd.c \
# 		execution/ft_libft.c \
# 		parting/src/to_final_struct.c\
# 		parting/libft/ft_atoi.c \
#         parting/libft/ft_strlen.c \
# 		parting/libft/ft_split.c \
# 		parting/libft/ft_strtrim.c \
# 		parting/libft/ft_strchr.c \
# 		parting/libft/ft_strlcpy.c \
# 		parting/libft/ft_strdup.c \
# 		parting/libft/ft_strncmp.c \
# 		parting/libft/ft_strjoin.c \
# 		parting/libft/ft_substr.c \
# 		parting/libft/ft_memcpy.c \
# 		parting/libft/ft_isalpha.c

# OBJF = $(SRC:.c=.o)
# # LIBFT_DIR=/parting/libft
# # LIBFT_LIB=$(LIBFT_DIR)/libft.a
# NAME = minishell
# INCLUDES = -I . -I include -I $(LIBFT_DIR)  

# C = cc

# CFLAGS =  -Wall -Werror -Wextra #-fsanitize=address -g3

# all: $(NAME)

# $(NAME): $(OBJF) $(LIBFT_LIB)
# 	$(CC) $(CFLAGS) -lreadline $(OBJF) $(LIBFT_LIB) -o $(NAME)


# $(LIBFT_LIB):
# 	@$(MAKE) -C $(LIBFT_DIR)
# %.o: %.c
# 	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
# clean:
# 	rm -rf $(OBJF)
# 	$(MAKE) -C $(LIBFT_DIR) clean
# fclean: clean
# 	rm -rf $(NAME)
# 	$(MAKE) -C $(LIBFT_DIR) fclean


# re: fclean all

# .PHONY: all clean fclean re


NAME= minishell
CFLAG= -Wall -Wextra -Werror # -fsanitize=address -g3
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
		execution/echo.c \
		execution/env.c \
		execution/builtins.c \
 		execution/env_struct.c \
		execution/pwd.c \
		execution/cd.c \
		execution/ft_libft.c \
		parting/src/to_final_struct.c\
		parting/libft/ft_atoi.c \
        parting/libft/ft_strlen.c \
		parting/libft/ft_split.c \
		parting/libft/ft_strtrim.c \
		parting/libft/ft_strchr.c \
		parting/libft/ft_strlcpy.c \
		parting/libft/ft_strdup.c \
		parting/libft/ft_strncmp.c \
		parting/libft/ft_strjoin.c \
		parting/libft/ft_substr.c \
		parting/libft/ft_memcpy.c \
		parting/libft/ft_isalpha.c
		
OBJ= $(SRC:.c=.o)

all : $(NAME)



$(NAME) : $(OBJ)
	cc $(CFLAG) $^ -o $@

clean :
	rm -rf $(OBJ)

fclean : clean
	rm -rf $(NAME)

re : fclean all

.PHONY: all clean fclean re 
.SECONDARY : $(OBJ) $(OBJB)
