/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reset_term.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgauvrit <tgauvrit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/18 20:20:24 by tgauvrit          #+#    #+#             */
/*   Updated: 2015/04/27 18:22:28 by tgauvrit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void	reset_term(t_env *env)
{
	ft_putstr_fd(tgetstr("ve", NULL), tty_fd());
	ft_putstr_fd(tgetstr("te", NULL), tty_fd());
	tcsetattr(0, 0, env->old_term);
	close(tty_fd());
	tty_fd_get_set(-1);
}
