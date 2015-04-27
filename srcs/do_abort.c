/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_abort.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgauvrit <tgauvrit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/18 20:20:24 by tgauvrit          #+#    #+#             */
/*   Updated: 2015/04/27 18:02:52 by tgauvrit         ###   ########.fr       */
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
	ft_putstr_fd(tgetstr("ve", NULL), tty_fd());
	// ft_putstr_fd(tgetstr("te", NULL), tty_fd());
	tcsetattr(0, 0, env->old_term);
	// reset_term(get_env(NULL));
	// env->ti = 0;
	signal(SIGTSTP, SIG_DFL);
	cp[0] = env->term.c_cc[VSUSP];
	cp[1] = '\0';
	ioctl(0, TIOCSTI, cp);
	// signal(SIGTSTP, &do_stop);
	(void)signum;
}
