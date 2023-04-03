# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mabimich <mabimich@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/24 11:54:49 by flplace           #+#    #+#              #
#    Updated: 2023/04/03 16:23:27 by mabimich         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
# COLORS

GREEN		:= \033[0;92m
YELLOW		:= \033[0;93m
BLUE		:= \033[0;94m
END_COLOR	:= \033[0;39m

# **************************************************************************** #
# VARIABLES

SRCS	=	builtin/echo.c \
			builtin/cd.c \
			builtin/pwd.c \
			builtin/export.c \
			builtin/unset.c \
			builtin/env.c \
			builtin/exit.c \
			builtin/bltin_utils.c \
			lib/ft_calloc.c \
			lib/ft_lstlast.c \
			lib/ft_memset.c \
			lib/ft_strcmp.c\
			lib/ft_strdup.c \
			lib/ft_strlen.c\
			lib/ft_strcpy.c \
			lib/ft_strlcpy.c \
			lib/ft_strchr.c \
			lib/ft_itoa.c \
			lib/ft_strjoin.c \
			lib/ft_strjoin_tab.c \
			lib/ft_memmove.c \
			lib/ft_is_in_charset.c \
			lib/ft_free_tab_str.c \
			lib/ft_strtrim.c \
			lib/ft_substr.c \
			lib/ft_putendl_fd.c \
			lib/ft_putstr_fd.c \
			lib/ft_strjoin_with_free.c \
			lib/ft_pick.c \
			lib/ft_split.c \
			lib/free_tab_with_1blank.c\
			lib/ft_strcat.c \
			env_cpy.c \
			quote.c \
			expand.c \
			rl_gets.c \
			parser.c \
			fill_cmd.c \
			wip.c \
			ft_print_test.c \
			get_path.c \
			exec.c \
			exit.c \
			main.c
OBJ		=	${SRCS:.c=.o}
HEADER	=   minishell.h
NAME	=	minishell
CC		=	cc
CFLAGS	=	-Wall -Wextra -Werror

# **************************************************************************** #
# RULES

%.o:	%.c
	@${CC} ${CFLAGS} -c -g $< -o $@
	@echo "$(BLUE)Compiling $<...$(END_COLOR)"

$(NAME):	${OBJ} Makefile
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME) -l readline
	@echo "$(GREEN)Compiled $(NAME) :)$(END_COLOR)"

all:	${NAME}

clean:
	@rm -f ${OBJ}
	@echo "$(YELLOW)Removed object files.$(END_COLOR)"

fclean: clean
	@rm -f ${NAME}
	@echo "$(YELLOW)Cleaned libraries and $(NAME) executable.$(END_COLOR)"

re:		fclean all
	@echo "$(GREEN)Cleaned all and rebuilt $(NAME) and $(LIB)!$(END_COLOR)"

.PHONY:	all clean fclean re