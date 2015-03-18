/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_abort.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgauvrit <tgauvrit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/18 20:20:24 by tgauvrit          #+#    #+#             */
/*   Updated: 2015/03/18 20:26:45 by tgauvrit         ###   ########.fr       */
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
	reset_term(get_env(NULL));
	(void)signum;
}
