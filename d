SRC =  minishell.c \
$(NAME): $(SRC) $(LIBFT_LIB)
	$(CC) $(CFLAGS) $(SRC) -lreadline  $(LIBFT_LIB) -o $(NAME)
