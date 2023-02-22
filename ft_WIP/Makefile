# **************************************************************************** #
# COLORS

GREEN		:= \033[0;92m
YELLOW		:= \033[0;93m
BLUE		:= \033[0;94m
END_COLOR	:= \033[0;39m

# **************************************************************************** #
# VARIABLES

SRCS	=	lib/ft_calloc.c \
			lib/ft_memset.c \
			lib/ft_strcmp.c\
			lib/ft_strdup.c \
			lib/ft_strlen.c\
			lib/ft_strcpy.c \
			lib/ft_strlcpy.c \
			lib/ft_strchr.c \
			test_printer.c \
			env_cpy.c \
			quote.c \
			expand.c \
			rl_gets.c \
			wip.c \
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
