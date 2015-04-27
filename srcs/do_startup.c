/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_startup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgauvrit <tgauvrit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/18 20:20:24 by tgauvrit          #+#    #+#             */
/*   Updated: 2015/04/27 19:22:19 by tgauvrit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

static void	set_signals(void)
{
	signal(SIGWINCH, &window_size_update);
	signal(SIGCONT, &do_restart);
	signal(SIGTSTP, &do_stop);
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

void		do_restart(int signum)
{
	t_env	*env;

	(void)signum;
	signal(SIGTSTP, &do_stop);
	signal(SIGCONT, &do_restart);
	env = get_env(NULL);
	window_size_update(0);
	if (tcsetattr(0, TCSADRAIN, &env->term) == -1)
		throw_error(NULL);
	input_loop(env);
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
