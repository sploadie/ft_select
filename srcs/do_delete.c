/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_delete.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgauvrit <tgauvrit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/18 20:20:24 by tgauvrit          #+#    #+#             */
/*   Updated: 2015/03/18 20:24:58 by tgauvrit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void	do_delete(t_env *env)
{
	int		i;

	if (env->argc == 1)
		do_abort(0);
	env->argc--;
	i = env->curr_arg;
	while (i < env->argc)
	{
		env->argv[i] = env->argv[i + 1];
		env->selected[i] = env->selected[i + 1];
		i++;
	}
	if (env->curr_arg == env->argc)
		env->curr_arg--;
}
