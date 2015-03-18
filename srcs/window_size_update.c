/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_size_update.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgauvrit <tgauvrit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/18 20:20:24 by tgauvrit          #+#    #+#             */
/*   Updated: 2015/03/18 20:22:56 by tgauvrit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void	window_size_update(int signum)
{
	t_env			*env;
	struct winsize	win;

	env = get_env(NULL);
	ioctl(0, TIOCGWINSZ, &win);
	env->width = (int)win.ws_col;
	env->height = (int)win.ws_row;
	handle_term(env);
	(void)signum;
}
