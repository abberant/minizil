 /* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanouari <aanouari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 08:21:35 by aanouari          #+#    #+#             */
/*   Updated: 2023/05/05 14:09:56 by aanouari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"

# define RED	"\x1B[31m"
# define RESET	"\x1B[0m"


# define ERR_PERMISSION "minishell: %s: Permission denied\n"
# define ERR_NO_SUCH_FILE "minishell: %s: No such file or directory\n"
# define ERR_CMD_NOT_FOUND "minishell: %s: command not found\n"
# define ERR_INVALID_IDENT "minishell: %s: `%s': not a valid identifier\n"
# define ERR_UNSET "minishell: cd: %s not set\n"
# define ERR_NUMERIC_ARG "minishell: exit: %s: numeric argument required\n"
# define ERR_TOO_MANY_ARGS "minishell: exit: too many arguments\n"
# define UNEXPECTED_TOKEN "minishell: syntax error near unexpected token `%s'\n"
# define UNEXPECTED_TOKEN_2 "minishell: syntax error near unexpected token `||'\n"
# define UNCLOSED_QUOTE "minishell: syntax error near unclosed quotation mark\n"

typedef struct s_redir
{
	int				type;
	int				fd;
	char			*file;
	struct s_redir	*next;
	struct s_redir	*previous;
}	t_redir;

typedef struct s_vdata
{
	char			**stack;
	char			*cmd;
	int				sep;
	int				error;
	struct s_redir *rd;
	struct s_vdata *previous;
	struct s_vdata *next;
}	t_vdata;

typedef struct s_posay
{
	char			**env;
	int				exit_s;
	struct s_vdata	*ms;
}	t_posay;

enum e_token
{
	GREAT= '>',
	LESS = '<',
	PIPE = '|',
	SINGLE_QUOTE = '\'',
	DOUBLE_QUOTE = '"',
	SPACE = ' ',
	TAB = '\t',
	QUESTION_MARK = '?',
};

enum e_redir
{
	HEREDOC,
	REDIR_IN,
	REDIR_OUT,	
	APPEND,
};


char	*s_concatinate(char *s, char c);
char	**a_concatinate(char **s, char *c);

void	banner(void);

void	skip_spaces(char *str, int *i);
int		metachar_check(char c);
int		arrow_check(char *str);
void	sig_handler(int sig);

int		token_error(t_posay *tsr, char **stack);
int		unspecial(char c);

char	**lexer(char *load);
void	init_tree(char **stack, t_posay *tsr);
void	init_redir(t_posay *tsr);
void	rl_replace_line(const char *s, int comp);

char	*expand(t_posay *tsr, char *str);
char	*cancel_quotes(char	*file);
void	quote_expansion(t_posay *tsr, t_vdata *ms);

t_vdata	*vdata_new(char **stack, int separator);
void	vdata_addback(t_vdata **vdata, t_vdata *_new);
t_redir	*redir_new(char *file, int type);
void	redir_addback(t_redir **redir, t_redir *_new);



#endif