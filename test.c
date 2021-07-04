/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heom <heom@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 15:54:30 by heom              #+#    #+#             */
/*   Updated: 2021/07/04 15:19:31 by heom             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "egginshell.h"

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

  char* buf;
  while ((buf = readline("egg > ")) != 0) {
    if (strlen(buf) > 0) {
      add_history(buf);
    }

    printf("[%s]\n", buf);

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
	(void)	argc;
	(void)	argv;
	char	*buf;


	init(envp);

	buf = "echo 123";
	parse(buf);
	make_io();
	make_pipe();
	fork_loop();
}

int main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;

	// test_add_cmds();
	// test_add_cmd();
	// test_read();
	// test_readline(argc, argv);
	// test_ft_malloc();
	// test_to_double_ptr();
	// test_interpret_quote_env_item();
	test_primitive(argc, argv, envp);
	return (0);
}
