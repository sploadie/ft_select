/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgauvrit <tgauvrit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/11 16:16:41 by tgauvrit          #+#    #+#             */
/*   Updated: 2015/03/11 17:53:18 by tgauvrit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void	throw_error(char *str)
{
	perror(str);
	exit(1);
}

void	print_error(char *str)
{
	ft_putstr_fd(str, 2);
	exit(1);
}

int		main(int argc, char **argv)
{
	t_env	env;
	int		ret;

	if (argc < 2)
		print_error("./ft_select input [input...]\n");
	ft_bzero(&env, sizeof(env));
	env.argc = argc - 1;
	env.argv = argv + 1;
	if ((env.termtype = getenv("TERM")) == NULL)
		print_error("Specify a terminal with 'setenv TERM'\n");
	if ((ret = tgetent(env.term_buffer, env.termtype)) <= 0)
		throw_error(NULL);
	env.width = tgetnum("co");
	env.height = tgetnum("li");
	return (0);
}

/*
int		main(int argc, char **argv)
{
	char	str[2048];
	char	*termtype = getenv("TERM");
	char	term_buffer[2048];
	int		success;

	(void)argc;
	(void)argv;
	bzero(term_buffer, 2048);
	write(1, str, sprintf(str, "= Begin =\n"));
	// ------------------------------------------------------------ //
	//Check termtype global:
	if (termtype == NULL)
		printf("Specify a terminal type in your environment.\n");
	success = tgetent(term_buffer, termtype);
	// - Handle errors:
	if (success < 0)
	{
		printf("Could not access the termcap data base.\n");
		return (0);
	}
	if (success == 0)
	{
		printf("Terminal type '%s' is not defined.\n", termtype);
		return (0);
	}
	printf("Terminal type '%s' is defined!\n", termtype);
	printf("Terminal buffer: '%s'\n", term_buffer);
	printf("Success: '%d'\n", success);
	//Get info about terminal:
	printf("Terminal Size: (% 3d, % 3d)\n", tgetnum("co"), tgetnum("li"));
	printf("vi: '%s'\n", tgetstr("vi", NULL));
	printf("vi: '%s'\n", tgetstr("vi", NULL));
	// ------------------------------------------------------------ //
	write(1, str, sprintf(str, "=  End  =\n"));
	return (0);
}
*/
