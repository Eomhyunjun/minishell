# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: heom <heom@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/06/10 12:51:40 by heom              #+#    #+#              #
#    Updated: 2021/06/21 16:09:02 by heom             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CFLAGS = -Wall -Wextra -Werror -g
RM = rm -f

SRCS = \
			add \
			all \
			utils/ft_bzero


OBJS = $(FIL:.c=.o)

FIL = $(addsuffix .c, $(addprefix srcs/, $(SRCS)))


all : $(NAME)

$(OBJS): %.o : %.c
	gcc $(CFLAGS) -c -o $@ $<


$(NAME) : $(OBJS)
	gcc $(CFLAGS) $^ -o $@

clean :
	$(RM) $(OBJS)

fclean : clean
	$(RM) $(NAME) test

test : $(OBJS) test.c
	gcc $(CFLAGS) $^ -o test

re: fclean all

.PHONY: all clean fclean re
