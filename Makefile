# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: heom <heom@student.42seoul.kr>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/06/10 12:51:40 by heom              #+#    #+#              #
#    Updated: 2021/07/23 12:44:58 by heom             ###   ########.fr        #
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
			signal \
			charbox \
			try_open \
			get_path \
			make_io \
			process_open \
			ii_write \
			wait_subprocess \
			close \
			envp \
			make_pipe \

UTILS = \
			ft_atoi \
			ft_itoa \
			ft_bzero \
			ft_strncmp \
			ft_strlen \
			ft_split \
			ft_strlcpy \
			ft_strjoin \
			ft_malloc \
			ft_putstr \

PARSING = \
			parse \
			make_cmd \
			is_quote \
			is_empty \
			try_push \
			get_none_pos \
			interpret_quote_env \
			dollar \
			create \
			can_be_name \

EXECVE = \
			fork_loop \
			do_child \
			try_execve \
			dir_cmd \
			builtin_cmd \
			else_cmd \

BUILTIN_CMD = \
			env \
			export \
			unset \
			exit \
			echo \
			cd \
			pwd \



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
		$(addsuffix .c, $(addprefix src/utils/, $(UTILS))) \
		$(addsuffix .c, $(addprefix src/parsing/, $(PARSING))) \
		$(addsuffix .c, $(addprefix src/execve/, $(EXECVE))) \
		$(addsuffix .c, $(addprefix src/builtin_cmd/, $(BUILTIN_CMD))) \


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
