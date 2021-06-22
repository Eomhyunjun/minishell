/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heom <heom@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 15:54:30 by heom              #+#    #+#             */
/*   Updated: 2021/06/22 19:57:49 by heom             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "src/egginshell.h"

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
  while ((buf = readline("🐣  ")) != 0) {
    if (strlen(buf) > 0) {
      add_history(buf);
    }

    printf("[%s]\n", buf);

    // // readline malloc's a new buffer every time.
    free(buf);
  }
}

int main(int argc, char **argv)
{
	// test_add_cmds();
	// test_add_cmd();
	// test_read();
	test_readline(argc, argv);
	return (0);
}
