/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgauvrit <tgauvrit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/11 16:16:41 by tgauvrit          #+#    #+#             */
/*   Updated: 2015/03/11 17:13:41 by tgauvrit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <strings.h>
#include <signal.h>
#include <term.h>
#include <curses.h>
#include <stdio.h>
#include <sys/ioctl.h>

// static char term_buffer[2048];

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
	/* ------------------------------------------------------------ */
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
	/* ------------------------------------------------------------ */
	write(1, str, sprintf(str, "=  End  =\n"));
	return (0);
}
