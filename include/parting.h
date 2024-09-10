/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parting.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sait-amm <sait-amm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 12:50:17 by sait-amm          #+#    #+#             */
/*   Updated: 2024/09/10 22:08:38 by sait-amm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARTING_H
# define PARTING_H

# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define ERROR "syntax error near unexpected token"
# define RED "\033[0;31m"
# define RESET "\033[0m"
# define GOLD "\033[0;33m"
# define RESET "\033[0m"




// structs

enum				type
{
	IN,
	OUT,
	HER_DOC,
	APPEND,
};

enum	token
{
	NOT,
	AMB,
	Q_HER,	
};


typedef struct s_file
{
	char			*file;
	enum type		file_type;
	enum token		flag;
	struct s_file	*next;
}					t_file;

typedef struct s_flag
{
	bool			s_quote;
	bool			d_quote;
}					t_flag;

typedef struct s_cmd
{
	char			*cmd;
	struct s_cmd	*next;
}					t_cmd;

typedef struct s_data
{
	t_cmd *command; 
	t_file *files;
	struct s_data	*next;
}					t_data;

typedef struct s_minishell
{
	char			**cmd;
	t_file			*files;
	struct s_minishell	*next;
}					t_minishell;

// libft function

int					ft_whitespace(char c);
int					ft_atoi(const char *c);
size_t				ft_strlen(const char *str);
char				**ft_split(const char *s, char c);
char				*ft_strtrim(char const *s1, char const *set);
size_t				ft_strlcpy(char *str, const char *src, size_t size);
char				*ft_strdup(const char *s1);
char				*ft_strchr(const char *s, int c);
int					ft_strncmp(const char	*str1, const char	*str2, size_t n);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_substr(char const	*s, unsigned int start, size_t	len);
void	*ft_memcpy(void *dest, const void *src, size_t n);
int	ft_isalnum(unsigned char c);
int	ft_isalpha(int c);


// function parce Error

int					parce_error(char *line);
int					check_quote(char *line);
int					check_bracket(char *str);
int					check_logical(char *str);
int					check_red_out(char *str);
int					check_red_in(char *str);

// help redirection

int					ft_three_in(char *str);
int					ft_space_in(char *str);
int					ft_pipe_out(char *str);
int					ft_three_out(char *str);
int					ft_space_out(char *str);

// pipe

char				**ft_split_with_pipe(char *line);
char				*help_pipe_quote(char *str);
char				*help_pipe_quote_2(char *str);
size_t				len_double_str(char **str);

// fill data

void				init_data(t_data **data, char **line);


// store redirection file

char				*help_file(char *str,t_file **s,  char *src);
char				*ft_file(char *str);
void				update_quotes(bool *s, bool *d, char c);

// linked list function

t_file				*ft_lstlast_file(t_file *lst);
void				ft_lstadd_file(t_file **lst, char *str, t_file *new);
t_cmd				*ft_lstlast_cmd(t_cmd *lst);
void				ft_lstadd_cmd(t_cmd **head, char *str);
t_data				*ft_lstlast_data(t_data *lst);



//expand	

int	need_expand(char *str, int *pos);
char	*help_expand(char *str);

//free function 

void	ft_free(char	**str, int i);


// print function

int					synt_error(char *str);

// expand function

char	**ft_split_whitesp(const char *s);
char	*ft_cpy_dolar(char *str);
char	*expand_str(char *string, int pos);
char	*expand(char *str);
char	**split_str(char *str, int *f);
char	*help_quote_exp(char *str);
char	*remove_quote(char *str);
t_minishell *parce(char *line);

#endif
