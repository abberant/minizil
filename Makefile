# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lsadiq <lsadiq@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/24 08:21:48 by aanouari          #+#    #+#              #
#    Updated: 2023/06/09 02:02:44 by lsadiq           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	minishell

NO_COLOR	=	\033[0m
GREEN		=	\033[0;1;92m
RED			=	\033[0;1;91m
BLUE		=	\33[0;1;94m
GRAY		=	'\033[2;37m'
ITALIC		=	'\033[3m'


CC 	=		cc
CFLAGS =	-Wall -Wextra -Werror -fsanitize=address -g3
RM =		rm -rf

_SRCS =		minishell.c lexical_analysis.c structure.c aesthetic.c \
			joiners.c utils.c parsing.c redir.c errors.c expand.c \
			expand_2.c debug.c exec_cmd.c builtins.c ft_cd.c ft_pwd.c \
			ft_export.c ft_env.c ft_echo.c ft_unset.c ft_exit.c here_doc.c \
			get_next_line.c get_next_line_utils.c clean.c  
SRCS =		$(addprefix parsing/, $(_SRCS))
OBJS =		$(SRCS:.c=.o)


READLINE =	${HOME}/Desktop/brew/opt/readline/lib

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@
	@printf "$(RED)\r LOADING...⏳$(NO_COLOR)"
	
all:		$(NAME)

$(NAME):$(OBJS)
		@make -C libft/
		@$(CC) $(CFLAGS) -L libft/ -lft -lreadline -L $(READLINE) $(OBJS) -o $(NAME)
		@printf "$(GREEN)\r YOUR MINISHELL IS READY!!\n$(NO_COLOR)"
		
clean:
				@$(RM) $(OBJS)
				@printf "$(BLUE)\r Done Cleaning!!\n$(NO_COLOR)"
				@make clean -C libft/


fclean:			clean
				@$(RM) $(NAME)
				@make fclean -C libft/


re:				fclean all

.PHONY	:		all get_brew get_readline install clean fclean re bonus
