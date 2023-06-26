# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lsadiq <lsadiq@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/24 08:21:48 by aanouari          #+#    #+#              #
#    Updated: 2023/06/26 21:38:43 by lsadiq           ###   ########.fr        #
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
CFLAGS =	-Wall -Wextra -Werror -g3 -fsanitize=address
RM =		rm -rf

PSRCS	=	lexical_analysis.c structure.c aesthetic.c \
			joiners.c utils.c parsing.c redir.c errors.c expand.c \
			expand_2.c clean.c
P_SRCS	=		$(addprefix parsing/, $(PSRCS))

BSRCS	=	ft_cd.c ft_pwd.c ft_export.c ft_env.c ft_echo.c \
			ft_unset.c ft_exit.c cd_helper.c export_helper1.c \
			export_helper2.c
B_SRCS	=		$(addprefix builtins/, $(BSRCS))

ESRCS	=	builtins.c exec_cmd.c exec_red.c exec_helper.c \
			here_doc.c exec_1.c  
E_SRCS	=		$(addprefix execution/, $(ESRCS))

MAIN	=	minishell.c

OBJS	=	$(P_SRCS:.c=.o) $(B_SRCS:.c=.o) $(E_SRCS:.c=.o) $(MAIN:.c=.o)


READLINE =	${HOME}/Desktop/brew/opt/readline/lib

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@
	@printf "$(RED)\r YOUR SHELL IS LOADING...⏳$(NO_COLOR)"
	@sleep 0.03
	@printf "$(RED)\r YOUR SHELL IS LOADING...⌛️$(NO_COLOR)"
	@sleep 0.03
	
all:		$(NAME)

$(NAME):$(OBJS)
		@make -C libft/
		@$(CC) $(CFLAGS) -L libft/ -lft -lreadline -L $(READLINE) $(OBJS) -o $(NAME)
		@printf "$(GREEN)\r YOUR SHELL IS READY!!\n$(NO_COLOR)"
		
clean:
				@$(RM) $(OBJS)
				@printf "$(BLUE)\r Done Cleaning!!\n$(NO_COLOR)"
				@make clean -C libft/


fclean:			clean
				@$(RM) $(NAME)
				@make fclean -C libft/


re:				fclean all


.PHONY	:		all clean fclean re bonus
