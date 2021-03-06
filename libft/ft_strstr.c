/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgauvrit <tgauvrit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/09/02 22:16:02 by tgauvrit          #+#    #+#             */
/*   Updated: 2015/03/05 18:45:52 by tgauvrit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(char *str, char *to_find)
{
	int	i;

	if (to_find[0] == '\0')
		return (str);
	if (str == NULL)
		return (NULL);
	i = 0;
	while (to_find[i] == str[i] && str[i] != '\0')
	{
		i++;
		if (to_find[i] == '\0')
			return (str);
	}
	if (str[i] == '\0')
		return (NULL);
	return (ft_strstr(str + 1, to_find));
}
