/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_terminal.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgauvrit <tgauvrit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/18 20:20:24 by tgauvrit          #+#    #+#             */
/*   Updated: 2015/03/18 20:25:15 by tgauvrit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void	clear_terminal(t_env *env, char **str)
{
	int	i;

	i = 0;
	while (i < env->height)
	{
		ft_strjoinfree(str, tgoto(tgetstr("cm", NULL), 0, i));
		ft_strjoinfree(str, tgetstr("ce", NULL));
		i++;
	}
}
