/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanouari <aanouari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 08:21:35 by aanouari          #+#    #+#             */
/*   Updated: 2023/06/26 20:54:15 by aanouari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define RED "\x1B[31m"
# define GREEN "\e[01;32m"
# define RESET "\x1B[0m"
# define YELLOW "\033[0;33m"
# define BUFFER_SIZE 1024

# define ERR_PERMISSION "minishell: %s: Permission denied\n"
# define ERR_NO_SUCH_FILE "minishell: %s: No such file or directory\n"
# define ERR_CMD_NOT_FOUND "minishell: %s: command not found\n"
# define ERR_INVALID_IDENT "minishell: %s: `%s': not a valid identifier\n"
# define ERR_UNSET "minishell: cd: %s not set\n"
# define ERR_NUMERIC_ARG "minishell: exit: %s: numeric argument required\n"
# define ERR_TOO_MANY_ARGS "minishell: exit: too many arguments\n"
# define UNEXPECTED_TOKEN "minishell: syntax error near unexpected token `%s'\n"
# define UNCLOSED_QUOTE "minishell: syntax error near unclosed quotation mark\n"
# define AMBIGUOUS_REDIR "minishell: %s: ambiguous redirect\n"
# define UNSET_UNVALID "minishell: unset: `%s' : not a valid identifier\n"
# define EXPORT_INVALID "minishell: export: `%s': not a valid identifier\n"

typedef struct s_redir
{
	int				type;
	int				fd;
	int				error;
	char			*error_file;
	char			*file;
	struct s_redir	*next;
	int				in_flag;
	int				out_flag;
	struct s_redir	*previous;
}					t_redir;

typedef struct s_vdata
{
	char			**stack;
	char			*cmd;
	int				sep;
	struct s_redir	*rd;
	struct s_vdata	*previous;
	struct s_vdata	*next;
}					t_vdata;

typedef struct s_env
{
	char			*name;
	char			*value;
	void			*next;
}					t_env;

typedef struct s_shell
{
	int				flag;
	char			**env;
	char			**exp;
	char			**new_env;
	int				exit_s;
	struct s_vdata	*ms;
}					t_shell;

t_shell				g_data;

enum				e_token
{
	GREAT = '>',
	LESS = '<',
	PIPE = '|',
	SINGLE_QUOTE = '\'',
	DOUBLE_QUOTE = '"',
	SPACE = ' ',
	TAB = '\t',
	QUESTION_MARK = '?',
};

enum				e_redir
{
	HEREDOC,
	REDIR_IN,
	REDIR_OUT,
	APPEND,
};

char				*s_concatinate(char *s, char c);
char				**a_concatinate(char **s, char *c);

void				banner(void);
char				*get_prompt(char **load);

void				skip_spaces(char *str, int *i);
int					metachar_check(char c);
int					arrow_check(char *str);
void				sig_handler(int sig);
int					get_separator(char **stack, int i);
int					token_error(char **stack);
int					unspecial(char c);

char				**lexer(char *load);
void				init_tree(char **stack);
void				init_redir(void);
int					ft_parse(char **full, char *load);
void				rl_replace_line(const char *s, int comp);

char				*expand(char *str, bool quote);
char				*cancel_quotes(char *file, bool free_file);
void				quote_expansion(t_vdata *ms);
char				*delete_spaces(char *forum);

t_vdata				*vdata_new(char **stack, int separator);
void				vdata_addback(t_vdata **vdata, t_vdata *_new);
t_redir				*redir_new(char *file, int type);
void				redir_addback(t_redir **redir, t_redir *_new);

void				debug_struct(void);
void				ft_cleanse(void);

void				exec_command(void);
char				*split_path(char *path, char *argv);
char				*get_path(char **envp);
int					execute(void);
int					ft_lentab(char *tab);
int					ft_alpha(char c);
int					ft_len_env(char **str);
int					ft_cd(void);
int					ft_pwd(void);
int					ft_export(void);
int					ft_env(void);
int					ft_echo(void);
int					ft_unset(int i, int k, t_shell *tmp);
int					ft_exit(void);
void				here_doc(void);
int					open_here_doc(char *file, int fd, int status, char *line);
void				ft_append(void);
int					exec_redir(int in_fd, int out_fd);
void				fork_exec(int fd_in, int fd_out);
int					check_built_in(void);
void				ft_pipes(void);
char				**clone_env(char **str);
void				dup_2(int fd_1, int fd_2);
int					get_c_index(char *str, char c);
char				*get_my_env(t_shell shell, char *str);
int					ft_go_home(void);
int					go_old_pwd(void);
void				sort_env(char **str);
char				**clone_env(char **str);
char				**ft_add_str_to_tab(char **tab, char *str);
void				ft_free_env(t_env *env);
t_env				*ft_set(char *str);
char				**print_export(char **str);
int					ft_alpha(char c);
int					ft_does_it_exist(char **str, char *new);
int					ft_check(char *str);
void				dup_2(int fd_1, int fd_2);
int					launch(int *fd, int in, int out);
void				ft_pipeline(int fd[2], int in, int out);
void				fork_exec(int fd_in, int fd_out);
int					ft_reverse_fd(int *end, int index);
void				ft_here_sig(void);

#endif