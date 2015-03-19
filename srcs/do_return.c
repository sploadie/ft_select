/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_return.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgauvrit <tgauvrit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/18 20:20:24 by tgauvrit          #+#    #+#             */
/*   Updated: 2015/03/19 14:48:11 by tgauvrit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void	do_return(t_env *env)
{
	int		ret_len;
	char	str[(ret_len = (env->argc * env->col_width) + env->argc)];
	char	*temp;
	int		i;

	ft_bzero(str, ret_len);
	i = 0;
	temp = str;
	while (i < env->argc)
	{
		if (env->selected[i] == 1)
		{
			ft_strcpy(temp, env->argv[i]);
			temp += ft_strlen(env->argv[i]);
			*(temp++) = ' ';
		}
		i++;
	}
	if (temp == str)
		temp++;
	*(temp - 1) = '\0';
	reset_term(env);
	ft_putstr_fd(str, 1);
	exit(0);
}
