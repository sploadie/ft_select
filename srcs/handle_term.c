/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_term.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgauvrit <tgauvrit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/18 20:20:24 by tgauvrit          #+#    #+#             */
/*   Updated: 2015/03/19 17:45:57 by tgauvrit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

static void	arg_text(t_env *env, char **output, int i)
{
	if (i == env->curr_arg)
		ft_strjoinfree(output, tgetstr("us", NULL));
	if (env->selected[i] == 1)
		ft_strjoinfree(output, tgetstr("mr", NULL));
	ft_strjoinfree(output, env->argv[i]);
	ft_strjoinfree(output, tgetstr("me", NULL));
}

void		handle_term(t_env *env)
{
	char	*output;
	int		i;
	int		x;

	if ((((env->argc - 1) / (env->height - 1)) * (env->col_width + 1))
		+ env->col_width > env->width)
	{
		ft_putstr_fd(tgoto(tgetstr("cm", NULL), 0, 0), tty_fd());
		ft_putstr_fd(tgetstr("cd", NULL), tty_fd());
		write(tty_fd(), "Increase window size...", 23);
		return ;
	}
	output = ft_strdup(tgoto(tgetstr("cm", NULL), 0, 0));
	clear_terminal(env, &output);
	i = 0;
	while (i < env->argc)
	{
		x = (i / (env->height - 1)) * (env->col_width + 1);
		ft_strjoinfree(&output, tgoto(tgetstr("cm", NULL), x
			, i % (env->height - 1)));
		arg_text(env, &output, i);
		i++;
	}
	write(tty_fd(), output, ft_strlen(output));
	free(output);
}
