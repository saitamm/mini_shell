/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lai-elho <lai-elho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 14:30:09 by lai-elho          #+#    #+#             */
/*   Updated: 2024/10/07 12:14:58 by lai-elho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <unistd.h>

# define ERROR "syntax error near unexpected token"

typedef struct s_env
{
	char					*key;
	char					*value;
	struct s_env			*next;
}							t_env;

typedef struct s_minishell	t_minishell;
typedef struct s_global
{
	t_env					*env;
	int						flag;
	int						exit_status;
	int						separator;
	int						save_fd_out;
	int						save_fd_int;
	int						fd_pipe[2];
	char					*pwd;
	pid_t					*pid;
	char					*oldpwd;
	char					*underscore;
	t_minishell				*strct;
	int						flag_env;
	int						sig_herdoc;
	// for the norm
	int						shelvl;
	int						i;
	int						j;
}							t_global;
extern t_global				*g_global;

//***********************************PARSING***********************************

enum						e_type
{
	IN,
	OUT,
	HER_DOC,
	APPEND,
};

enum						e_token
{
	NOT,
	AMB,
	Q_HER,
};

typedef struct s_file
{
	char					*file;
	enum e_type				file_type;
	enum e_token			flag;
	struct s_file			*next;
}							t_file;

typedef struct s_flag
{
	bool					s_quote;
	bool					d_quote;
}							t_flag;

typedef struct s_cmd
{
	char					*cmd;
	struct s_cmd			*next;
}							t_cmd;

typedef struct s_data
{
	t_cmd					*command;
	t_file					*files;
	struct s_data			*next;
}							t_data;

typedef struct s_minishell
{
	char					**cmd;
	t_file					*files;
	struct s_minishell		*next;
}							t_minishell;
// libft function
int							ft_whitespace(char c);
int							ft_atoi(const char *c);
size_t						ft_strlen(const char *str);
char						**ft_split(const char *s, char c);
char						*ft_strtrim(char const *s1, char const *set);
size_t						ft_strlcpy(char *str, const char *src, size_t size);
char						*ft_strdup(const char *s1);
char						*ft_strchr(const char *s, int c);
int							ft_strncmp(const char *str1, const char *str2,
								size_t n);
char						*ft_strjoin(char *s1, char *s2);
char						*ft_substr(char const *s, unsigned int start,
								size_t len);
void						*ft_memcpy(void *dest, const void *src, size_t n);
char						*ft_itoa(int n);
int							ft_isalnum(unsigned char c);
int							ft_isalpha(int c);
// function parce Error
int							parce_error(char *line);
int							check_quote(char *line);
int							check_bracket(char *str);
char						check_logical(char *str);
int							check_red_out(char *str);
int							check_red_in(char *str);
// help redirection
int							ft_three_in(char *str);
int							ft_space_in(char *str);
int							ft_pipe_out(char *str);
int							ft_three_out(char *str);
int							ft_space_out(char *str);
// pipe
char						**ft_split_with_pipe(char *line);
char						*help_pipe_quote(char *str);
char						*help_pipe_quote_2(char *str);
size_t						len_double_str(char **str);
// fill data
void						init_data(t_data **data, char **line);
// store redirection file

char						*help_file(char *str, t_file **s, char *src);
char						*ft_file(char *str);
void						update_quotes(bool *s, bool *d, char c);
// linked list function
t_file						*ft_lstlast_file(t_file *lst);
void						ft_lstadd_file(t_file **lst, char *str,
								t_file *new);
t_cmd						*ft_lstlast_cmd(t_cmd *lst);
void						ft_lstadd_cmd(t_cmd **head, char *str);
t_data						*ft_lstlast_data(t_data *lst);
void						add_cmd(int *i, t_data **s, char *str);
char						**help_cmd(char *str);
void						full_command(t_data **data, char *str);
t_minishell					*lstlast_minishell(t_minishell *lst);
t_data						**add_data(t_data **data, t_data *new);
void						add_her_append(int *i, t_data **s, char *str);
int							append_her_doc(char a, char b);
void						add_infile(int *i, t_data **s, char *str);
void						add_outfile(int *i, t_data **s, char *str);
void						add_file(int *i, char *str, t_data **s);
t_cmd						*new_node_cmd(char *str);
// expand
int							need_expand(char *str, int *pos);
char						*help_expand(char *str);
// free function
void						ft_free(char **str, int i);
void						free_minishell(t_minishell **m_shell);
void						ft_free_cmd(t_cmd **lst);
void						ft_free_data(t_data **data);
void						ft_free_file(t_file **lst);
// print function
int							synt_error(char *str, char c);
// expand function
char						**ft_split_whitesp(const char *s);
char						*ft_cpy_dolar(char *str);
char						*expand_str(char *string, int pos);
char						**split_str(char *str, int *f);
char						*help_quote_exp(char *str);
char						*remove_quote(char *str);
t_minishell					*parce(char *line);
// her doc function
char						*generate_filename(void);
char						*create_file_herdoc(char *lim,
								enum e_token flag_quote);
char						*help_herdoc(char *line, enum e_token flag_quote,
								int *flag, char *d);

// help function

int							no_red_af(char *str);
char						*skip_red(char *str);
int							ft_skip(char *str);
int							ft_lstsize_3(t_env *lst);
int							have_to_split(char *str);
char						*help_space(char *str);

void						sig_her_doc(int signum);
int							her_doc_sig(char *line);
void						norm_main(char *line);
//***********************************EXECUTION**********************************

typedef struct s_execution
{
	int						ac;
	char					**av;
	char					**env;
}							t_execution;

int							ft_echo(char **str);
void						parse_env_var(char **env_var);

int							ft_pwd(void);
int							ft_cd(char **Path);
int							print_env(t_env *head, char **cmd);
char						*ft_strchr(const char *str, int c);
int							ft_strcmp(const char *s1, const char *s2);
void						ft_free_3_in_exit(char **cmd);
int							ft_strncmp(const char *s1, const char *s2,
								size_t n);
size_t						ft_strlen(const char *c);
char						*ft_strcpy(char *dest, const char *src);
char						*find_home_path(void);
int							unset(char **av);
int							ft_exit(char **cmd);
void						ft_free_1_in_exit(void);
void						ft_free_2_in_exit(void);
void						add_to_list(t_env **head, char *key, char *value);
char						*get_key(char *s);
char						*ft_putkey(char *env_var);
int							ft_find_key_len(char *env_var);
void						add_to_list(t_env **head, char *key, char *value);
t_env						*create_node(char *key, char *value);
void						ft_export(t_minishell *strct);
int							ft_check_export_unset_args(char *str);
void						ft_check_key(char *str);
char						*ft_strcat(char *dest, const char *src);
int							find_key(t_env *env, const char *key);
void						ft_change_key_value(char *key, char *value);
void						ft_lstremove(char *key);
void						ft_execution(t_minishell *strct);
// void	ft_export(t_minishell *strct);
int							ft_check_export_unset_args(char *str);
void						ft_check_key(char *str);
char						*ft_strcat(char *dest, const char *src);
void						ft_change_curr_and_old_path(char *new_path);
int							ft_lstsize2(t_minishell *lst);

void						ft_write_in_pipe(t_file *files_head);
char						*get_path(char *envp, char *cmd);
char						**env_to_array(t_env *env);
int							need_expand_her_doc(char *str, int *pos, int flag);
void						print(t_minishell *strct);
int							is_built(char *str);
int							ft_builtins(t_minishell *strct);
int							ft_infile(t_file *strct);
int							ft_outfile(t_file *strct);
int							ft_append(t_file *strct);
int							redirection(t_minishell *strct);
void						ft_bashlvl(t_minishell *strct);
void						ft_underscore(t_minishell *strct);
void						ft_free_global(void);
void						free_list(t_env **m_shell);
int							ft_lstsize_minishell(t_minishell *lst);
int							ft_lstsize2(t_minishell *lst);
int							ft_lstsize_3(t_env *lst);
void						ft_swaped(t_env *a, t_env *b);
void						ft_list_sort(t_env **env);
void						print_export(void);
void						error_export(char *str, char *error);
int							check_error_export(char *str);
int							ft_infile(t_file *strct);
int							ft_outfile(t_file *strct);
void						hepl_2_ft_infile(t_file *strct);
void						hepl_3_ft_infile(t_file *strct, int infile_fd);
void						hepl_5_ft_infile(int infile_fd);
void						hepl_4_ft_infile(void);
void						hepl_1_ft_infile(t_file *strct);
int							ft_outfile_built(t_file *strct);
int							ft_append_built(t_file *strct);
int							help1_append(t_file *strct, int fd);
void						ft_change_curr_and_old_path(char *new_path);
char						*find_home_path(void);
void						ft_find_current_pwd(void);
void						help_1_ft_change_curr_and_old_path(char *new_path);
void						help_2_ft_change_curr_and_old_path(char *new_path);
void						ft_change_curr_and_old_path(char *new_path);
void						error_fun(char *str, int h);
char						**env_to_array(t_env *env);
void						ft_double_free(char **str, char *cmd_1,
								char *w_path);
char						*cmd_is_path(char **str, char *cmd_1, int flag);
void						env_manuel(void);
int							is_directory(const char *path);
char						**ft_execve_arg(char **str);
void						ft_exec_child(t_minishell *strct);
int							ft_infile_built(t_file *strct);
int							redirection_buils(t_minishell *strct);
int							execute_child(t_minishell *strct);
void						free_0(void);
void						free_1(void);
void						free_2(t_minishell *strct, char **spl);
void						free_3(t_minishell *strct, char **spl);
void						free_4(t_minishell *strct, char **spl, int l);
void						free_5(t_minishell *strct, char **spl);
void						free_6(t_minishell *strct, char *path, char *h_ex);
void						free_7(t_minishell *strct, char *path,
								char **env_exc);
void						handle_builtins(t_minishell *strct);
int							help_2_ft_outfile(t_file *strct, int outfile_fd);
int							ft_execution_built(t_minishell *strct);
void						ft_child(t_minishell *strct, int i);
void						ft_wait(int size);
void						help_wait(int status);
void						handle_special(t_minishell *strct);
// signals fcts
void						ft_sig_handling(void);
void						handle_signals(void);

#endif
