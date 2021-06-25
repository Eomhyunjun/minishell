# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: heom <heom@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/06/10 12:51:40 by heom              #+#    #+#              #
#    Updated: 2021/06/25 16:29:52 by heom             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CFLAGS = -Wall -Wextra -Werror -g
RM = rm -f

MAIN = main

SRCS = \
			add \
			all \
			safe_exit \
			egg_strndup \
			get_none_pos \
			init \
			make_argv \
			utils/ft_bzero \


OBJS = $(FIL:.c=.o)
INCS = -I./inc
LIBS = -L./lib -lhistory -lreadline -ltermcap

# $(addsuffix .c, $(addprefix src/, $(MAIN)))
FIL = $(addsuffix .c, $(addprefix src/, $(SRCS))) \


all : $(NAME)

$(OBJS): %.o : %.c
	gcc $(CFLAGS) $(INCS) -c -o $@ $<

src/main.o : src/main.c
	gcc $(CFLAGS) $(INCS) -c -o $@ $<

$(NAME) : $(OBJS) src/main.o
	gcc $(CFLAGS) $^ -o $@ $(LIBS)

clean :
	$(RM) $(OBJS)

fclean : clean
	$(RM) $(NAME) test

test : $(OBJS) test.c
	gcc $(CFLAGS)  $^ -o test $(LIBS)

re: fclean all

.PHONY: all clean fclean re
