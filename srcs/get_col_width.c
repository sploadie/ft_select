/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_col_width.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgauvrit <tgauvrit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/18 20:20:24 by tgauvrit          #+#    #+#             */
/*   Updated: 2015/03/18 20:25:35 by tgauvrit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

int		get_col_width(char **list, int size)
{
	unsigned int	max_len;

	max_len = 0;
	while (size-- > 0)
	{
		if (ft_strlen(list[size]) > max_len)
			max_len = ft_strlen(list[size]);
	}
	return ((int)max_len);
}
