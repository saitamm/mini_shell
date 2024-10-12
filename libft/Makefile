# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sait-amm <sait-amm@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/30 13:15:44 by lai-elho          #+#    #+#              #
#    Updated: 2024/10/12 17:35:02 by sait-amm         ###   ########.fr        #
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
		ft_isalpha.c \
		ft_isalnum.c \
		ft_itoa.c


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
