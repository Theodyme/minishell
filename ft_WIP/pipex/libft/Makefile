# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mabimich <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/07 18:43:48 by mabimich          #+#    #+#              #
#    Updated: 2022/05/31 18:49:46 by mabimich         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRCS = ${shell find . -name "*.c"}

INCS = includes

OBJS = $(SRCS:%.c=%.o)

CFLAGS = -Wall -Wextra -Werror

CC = gcc

all: $(NAME)

.c.o :
	@${CC} ${CFLAGS} -c $< -o ${<:.c=.o} -I ${INCS}

$(NAME): $(OBJS)
	ar rc $(NAME) $(OBJS)

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
