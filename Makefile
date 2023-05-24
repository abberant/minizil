<<<<<<< HEAD
# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aanouari <aanouari@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/24 08:21:48 by aanouari          #+#    #+#              #
#    Updated: 2023/05/24 01:56:49 by aanouari         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

=======
>>>>>>> a269eab136ae1422ddfd9d18cf8b26e2e1d5a49f
NAME		=	minishell


NO_COLOR	=	\033[0m
GREEN		=	\033[0;1;92m
RED			=	\033[0;1;91m
BLUE		=	\33[0;1;94m
GRAY		=	'\033[2;37m'
ITALIC		=	'\033[3m'


CC 	=		cc
CFLAGS =	-Wall -Wextra -Werror 
#-fsanitize=address -g3
RM =		rm -rf

_SRCS =		minishell.c parsing_utils.c structure.c aesthetic.c \
			joiners.c utils.c parsing.c redir.c errors.c expand.c \
			expand_2.c debug.c
SRCS =		$(addprefix parsing/, $(_SRCS))
OBJS =		$(SRCS:.c=.o)


READLINE =	/goinfre/aanouari/homebrew/opt/readline/lib

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@
	@printf "$(RED)\r LOADING...⏳$(NO_COLOR)"
	
all:		$(NAME)


get_brew	:
				@printf "$(ITALIC)$(GRAY) Installing Homebrew...$(NO_COLOR)"
				@cd ~/goinfre/ && \
				if [ -d homebrew ]; then \
					printf "$(GREEN)- Homebrew already installed -$(NO_COLOR)"; \
					exit 0; \
				fi
				@cd ~/goinfre/ && mkdir homebrew && curl -L https://github.com/Homebrew/brew/tarball/master | tar xz --strip 1 -C homebrew
				@cd ~/goinfre/ && eval "$$(homebrew/bin/brew shellenv)"
				@brew update --force --quiet
				@chmod -R go-w "$$(brew --prefix)/share/zsh"

get_readline:
				@printf "$(ITALIC)$(GRAY) Installing readline...$(NO_COLOR)"
				@brew install -q readline

install		:	get_brew get_readline


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
