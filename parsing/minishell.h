/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanouari <aanouari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 08:21:35 by aanouari          #+#    #+#             */
/*   Updated: 2023/04/28 14:48:35 by aanouari         ###   ########.fr       */
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


# define UNEXPECTED_TOKEN "minishell: syntax error near unexpected token `%s'\n"


typedef struct s_token
{
	char			*content;
	int				type;
	int				status;
	struct s_token	*next;
}	t_token;

// typedef struct s_rop
// {
// 	char	**stack;
// 	t_token	*shaft;
// }	t_rop;

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

enum e_type
{
	KEYWORD,
	LITERAL,
	OPERATOR,
	HEREDOC,
	REDIR_IN,
	REDIR_OUT,
	
};

enum e_status
{
	DEFAULTED,
	BETWIXT_SQ,
	BETWIXT_DQ,
};


char	*s_concatinate(char *s, char c);
char	**a_concatinate(char **s, char *c);


void	banner(void);


void	skip_spaces(char *str, int *i);
int		metachar_check(char c);
void	reset_pivot(char *pivot);
int		d_quote_cast(char *stack);
int		set_type(int status, char *shaft);

char	**lexer(char *load);
void	init_tree(char **stack, t_token **shaft);
void	casting(t_token **shaft);
void	rl_replace_line(const char *s, int comp);

/*-----> TOKEN UTILS <-----*/

t_token	*token_new(char *content);
int		clear_tokens(t_token **token);
void	token_addback(t_token **token, t_token *_new);
void	token_addfront(t_token **token, t_token *_new);


#endif