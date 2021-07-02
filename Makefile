# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: heom <heom@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/06/10 12:51:40 by heom              #+#    #+#              #
#    Updated: 2021/07/02 18:12:39 by heom             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CFLAGS = -Wall -Wextra -Werror -g
RM = rm -f

MAIN = main

SRCS = \
			all \
			add \
			safe_exit \
			egg_strndup \
			init \
			charbox \
			try_open \
			utils/ft_bzero \
			utils/ft_strncmp \
			utils/ft_strlen \
			utils/ft_split \
			utils/ft_strlcpy \
			utils/ft_strjoin \
			utils/ft_malloc \
			pipe/fork_loop \
			pipe/make_pipe \

PARSING = \
			parse \
			make_cmd \
			is_quote \
			try_push \
			get_none_pos \
			interpret_quote_env \
			dollar \


OBJS = $(FIL:.c=.o)
INCS = -I./inc
LIBS =  -lreadline -ltermcap

# $(addsuffix .c, $(addprefix src/, $(MAIN)))
FIL = \
		$(addsuffix .c, $(addprefix src/, $(SRCS))) \
		$(addsuffix .c, $(addprefix src/parsing/, $(PARSING)))


all : $(NAME)

$(OBJS): %.o : %.c
	gcc $(CFLAGS) $(INCS) -c -o $@ $<

src/main.o : src/main.c
	gcc $(CFLAGS) $(INCS) -c -o $@ $<

$(NAME) : $(OBJS) src/main.o
	gcc $(CFLAGS) $^ -o $@ $(LIBS)

clean :
	$(RM) $(OBJS) src/main.o

fclean : clean
	$(RM) $(NAME) test

test : $(OBJS) test.c
	gcc $(CFLAGS) $(INCS) $^ -o test $(LIBS)

re: fclean all

.PHONY: all clean fclean re
