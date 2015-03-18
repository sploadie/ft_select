/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_startup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgauvrit <tgauvrit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/18 20:20:24 by tgauvrit          #+#    #+#             */
/*   Updated: 2015/03/18 20:31:48 by tgauvrit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

static void	set_signals(void)
{
	signal(SIGWINCH, &window_size_update);
	signal(SIGCONT, &do_startup);
	signal(SIGINT, &do_abort);
	signal(SIGINT, &do_abort);
	signal(SIGHUP, &do_abort);
	signal(SIGTERM, &do_abort);
	signal(SIGSEGV, &do_abort);
	signal(SIGQUIT, &do_abort);
	signal(SIGFPE, &do_abort);
	signal(SIGALRM, &do_abort);
	signal(SIGKILL, &do_abort);
	signal(SIGABRT, &do_abort);
	signal(SIGUSR1, &do_abort);
	signal(SIGUSR2, &do_abort);
}

void		do_startup(int signum)
{
	t_env	*env;

	set_signals();
	env = get_env(NULL);
	tcgetattr(0, &env->term);
	env->term.c_lflag &= ~(ICANON);
	env->term.c_lflag &= ~(ECHO);
	env->term.c_cc[VMIN] = 1;
	env->term.c_cc[VTIME] = 0;
	tcgetattr(0, env->old_term);
	if (tcsetattr(0, TCSADRAIN, &env->term) == -1)
		throw_error(NULL);
	if (env->ti == 0)
	{
		ft_putstr_fd(tgetstr("ti", NULL), tty_fd());
		env->ti = 1;
	}
	(void)signum;
}
