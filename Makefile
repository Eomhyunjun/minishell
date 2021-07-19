# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: taehokim <taehokim@student.42seoul.kr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/06/10 12:51:40 by heom              #+#    #+#              #
#    Updated: 2021/07/19 15:32:30 by taehokim         ###   ########.fr        #
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
			get_path \
			make_io \
			ii_write \
			wait_subprocess \
			close \
			envp \
			process_env_pipe \
			process_exit_pipe \
			process_other_pipe \
			builtin_cmd/env \
			builtin_cmd/export \
			builtin_cmd/unset \
			builtin_cmd/exit \
			builtin_cmd/echo \
			builtin_cmd/cd \
			builtin_cmd/pwd \
			builtin_cmd/builtin_request \
			utils/ft_atoi \
			utils/ft_itoa \
			utils/ft_bzero \
			utils/ft_strncmp \
			utils/ft_strlen \
			utils/ft_split \
			utils/ft_strlcpy \
			utils/ft_strjoin \
			utils/ft_malloc \
			utils/ft_putstr \
			pipe/fork_loop \
			pipe/make_pipe \
			delete/print \

PARSING = \
			parse \
			make_cmd \
			is_quote \
			try_push \
			get_none_pos \
			interpret_quote_env \
			dollar \
			create \


OBJS = $(FIL:.c=.o)
INCS = -I./inc
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
	LIBS =  -L./lib/linux -lreadline -ltermcap -lhistory
else
	LIBS =  -L./lib -lreadline -ltermcap -lhistory
endif

FIL = \
		$(addsuffix .c, $(addprefix src/, $(SRCS))) \
		$(addsuffix .c, $(addprefix src/parsing/, $(PARSING)))


all : $(NAME)

$(OBJS): %.o : %.c inc/egginshell.h inc/types.h
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
