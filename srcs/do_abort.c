/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_abort.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgauvrit <tgauvrit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/18 20:20:24 by tgauvrit          #+#    #+#             */
/*   Updated: 2015/04/27 18:33:41 by tgauvrit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void	do_abort(int signum)
{
	reset_term(get_env(NULL));
	exit(signum);
}

void	do_stop(int signum)
{
	t_env	*env;
	char    cp[2];

	env = get_env(NULL);
	// ft_putstr_fd(tgetstr("te", NULL), tty_fd());
	reset_term(env);
	signal(SIGTSTP, SIG_DFL);
	cp[0] = env->term.c_cc[VSUSP];
	cp[1] = '\0';
	ioctl(0, TIOCSTI, cp);
	(void)signum;
}
