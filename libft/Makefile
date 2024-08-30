# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sait-amm <sait-amm@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/11 11:56:15 by sait-amm          #+#    #+#              #
#    Updated: 2024/08/27 17:17:36 by sait-amm         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
SRCF =  ft_atoi.c \
        ft_strlen.c \
		ft_split.c \
		ft_strtrim.c \
		ft_strchr.c \
		ft_strlcpy.c \
		ft_strdup.c \
		ft_strncmp.c \
		ft_strjoin.c \
		ft_substr.c \
		ft_memcpy.c \
		ft_isalpha.c


CC = cc

CFLAGS = -Wall -Werror -Wextra

AR = ar rc

OBJF = $(SRCF:.c=.o)


all : $(NAME)

$(OBJF) : $(SRC)
	$(CC) $(CFLAGS) -c $(SRCF)

$(NAME): $(OBJF) 
	$(AR) $(NAME) $(OBJF)


clean :
	rm -f $(OBJF) 

fclean : clean
	rm -f $(NAME)

re: fclean all

.PHONY: fclean all re clean 
