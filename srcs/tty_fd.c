/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tty_fd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgauvrit <tgauvrit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/18 20:20:24 by tgauvrit          #+#    #+#             */
/*   Updated: 2015/04/27 18:21:55 by tgauvrit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

int		tty_fd_get_set(int new)
{
	static int	fd = -1;

	if (new != 0)
		fd = new;
	return (fd);
}

int		tty_fd(void)
{
	if (tty_fd_get_set(0) == -1)
		tty_fd_get_set(open("/dev/tty", O_WRONLY));
	return (tty_fd_get_set(0));
}
