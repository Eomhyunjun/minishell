/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taehokim <taehokim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 15:54:30 by heom              #+#    #+#             */
/*   Updated: 2021/07/08 14:15:26 by taehokim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/egginshell.h"
#include <termios.h>
#include <curses.h>
#include <term.h>
#include <errno.h>

// void test_add_cmds()
// {
// 	add_cmds();
// 	add_cmds();
// 	add_cmds();
// 	add_cmds();
// }

// void test_add_cmd()
// {
// 	add_cmds();
// 	add_cmd();
// 	add_cmd();
// 	add_cmd();
// 	add_cmd();
// 	t_cmd *a;
// 	for (a = all()->cmds->cmd_info; a; a = a->next)
// 	{
// 		printf("hi hos\n");
// 	}
// }

void test_read()
{
	char c;
	while (1)
	{
		read(0, &c, 1);
		printf("%d \n", c);
	}
}

void test_interpret_quote_env_item()
{
	printf("%s\n", interpret_quote_env("1dd"));
	printf("%s\n", interpret_quote_env("2dd\"'\"abc"));
	printf("%s\n", interpret_quote_env("3dd'\"'abc"));
	printf("%s\n", interpret_quote_env("4dd"));
	printf("%s\n", interpret_quote_env("5dd\"d\""));
	printf("%s\n", interpret_quote_env("6dd$PAT"));
	printf("%s\n", interpret_quote_env("dd''$A''\"\"c"));
	printf("%s\n", interpret_quote_env("dd\"$A\""));
	printf("%s\n", interpret_quote_env("dd\"d$A\""));
}

void test_readline(int argc, char **argv)
{
	(void)argv;
	(void)argc;
	// 	  printf("Welcome! You can exit by pressing Ctrl+C at any time...\n");

	//   if (argc > 1 && strcmp(argv[1], "-d") == 0) {
	//     // By default readline does filename completion. With -d, we disable this
	//     // by asking readline to just insert the TAB character itself.
	//     rl_bind_key('\t', rl_insert);

	//   }

	char *buf;
	while ((buf = readline("egg > ")) != 0)
	{
		if (strlen(buf) > 0)
		{
			add_history(buf);
		}

		printf("[%s]\n", buf);

		// // readline malloc's a new buffer every time.
		free(buf);
	}
}

struct termios saved_attributes;

void reset_input_mode(void)
{
	tcsetattr(STDIN_FILENO, TCSANOW, &saved_attributes);
}

void set_input_mode(void)
{
	struct termios tattr;

	extern char *tgetstr(), *getenv();
	// char *loc = termbuf;
	char entry[1024];
	char *term;
	char buffer[1024];

	if ((term = getenv("TERM")) == NULL)
	{
		printf("$TERM not defined");
	}
	if (tgetent(entry, term) <= 0)
	{
		printf("Unknown terminal.");
	}
	if (tgetent(buffer, term) != 1)
	{
		printf("No termcap definition for $TERM");
	}
	printf("buffer: %s\n", buffer);
	printf("term: %s\n", term);
	printf("entry: %s\n", entry);

	/* Make sure stdin is a terminal. */
	if (!isatty(STDIN_FILENO))
	{
		fprintf(stderr, "Not a terminal.\n");
		exit(EXIT_FAILURE);
	}

	/* Save the terminal attributes so we can restore them later. */
	tcgetattr(STDIN_FILENO, &saved_attributes);
	atexit(reset_input_mode);

	/* Set the funny terminal modes. */
	tcgetattr(STDIN_FILENO, &tattr);
	tattr.c_lflag &= ~(ICANON | ECHO); /* Clear ICANON and ECHO. */
	tattr.c_cc[VMIN] = 1;
	tattr.c_cc[VTIME] = 0;
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &tattr);
}

void do_nothing(int signo)
{
	(void)signo;
}
void test_sig_handler(int signo)
{
	(void)signo;
	// printf("\nI Received (%d), %s(%lu), %d, %p\n", signo, rl_line_buffer, strlen(rl_line_buffer),  rl_point, rl_pre_input_hook);
	// rl_done = 1;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

int test_rl_getc_function(FILE *stream)
{
	int result;
	unsigned char c;
	(void)(stream);
	// printf("stream: %p\n", rl_instream);

	// int fd = fileno(rl_instream);
	while (1)
	{
		result = read(rl_instream->_file, &c, sizeof(unsigned char));
		// printf("(readed: %c, %d, %d)\n", c, c, rl_point);
		if (c == 4)
		{
			rl_on_new_line();
			write(1, "exit\n", 5);
			exit(0);
		}

		if (result == sizeof(unsigned char))
		{
			// rl_redisplay();
			// printf("(readed: %s)\n", rl_line_buffer);
			// if (c == 'a')
			// {
			// 	rl_done = 1;
			// 	// rl_replace_line("", 0);
			// 	// rl_on_new_line();
			// 	// rl_redisplay();
			// }

			return (c);
		}
		if (result == 0)
		{
			printf("result is 0\n");
			return (EOF);
		}
	}
}

int test_rl_signal_event_hook()
{
	// printf("signal! %d\n", rl_catch_signals);
	return 0;
}

void test_signal_while_readline(int argc, char **argv)
{
	(void)argv;
	(void)argc;

	// set_input_mode();
	char *buf;
	signal(SIGINT, test_sig_handler);
	signal(SIGQUIT, do_nothing);
	printf("%p\n", rl_getc_function);
	rl_getc_function = test_rl_getc_function;
	// rl_signal_event_hook = test_rl_signal_event_hook;
	// rl_redisplay();
	// pause();
	rl_catch_signals = 0;
	while ((buf = readline("egg > ")) != 0)
	{
		if (strlen(buf) > 0)
		{
			add_history(buf);
		}

		printf("[%s]\n", buf);
		if (strlen(buf) == 4 && buf[0] == 'e' && buf[1] == 'x' && buf[2] == 'i' && buf[3] == 't')
			exit(0);

		// // readline malloc's a new buffer every time.
		free(buf);
	}
}

void test_ft_malloc()
{
	char *p;
	int res = ft_malloc(&p, 10);
	p[0] = 'a';
	p[1] = 'b';
	p[2] = 'c';
	p[3] = 'h';
	p[4] = 'a';
	p[5] = 'o';
	p[6] = '\0';
	printf("%d %p %s\n", res, p, p);
}

void test_to_double_ptr()
{
	t_charbox *box;
	add_charbox(&box, egg_strdup("hi"), 0);
	add_charbox(&box, egg_strdup("ho"), 0);
	add_charbox(&box, egg_strdup("he"), 0);
	add_charbox(&box, egg_strdup("hu"), 0);

	char **box2 = to_double_ptr(box);
	int i = 0;
	while (box2[i])
	{
		printf("%d: %s\n", i, box2[i]);
		i++;
	}
}

void test_primitive(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	char *buf;

	init(envp);
	buf = "echo << a";
	if (ft_strlen(buf) > 0)
	{
		safe_free_cmd();
		add_history(buf);
		parse(buf);
		if (!make_io())
		{
			make_pipe();
			fork_loop();
		}
	}
	close_unused();
	wait_subprocess();
	safe_exit(0, NULL);
}

void test_execve(int argc, char **argv, char **envp)
{
	(void)argc;
	int res = execve("/Users/heom/test.sh", argv, envp);
	printf("res: %d, %s, %d\n", res, strerror(errno), errno);
}

int main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	(void)envp;

	// test_add_cmds();
	// test_add_cmd();
	// test_read();
	// test_readline(argc, argv);
	// test_ft_malloc();
	// test_to_double_ptr();
	// test_interpret_quote_env_item();
	// test_primitive(argc, argv, envp);
	// test_execve(argc, argv, envp);
	test_signal_while_readline(argc, argv);

	return (0);
}
