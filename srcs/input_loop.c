/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgauvrit <tgauvrit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/18 20:20:24 by tgauvrit          #+#    #+#             */
/*   Updated: 2015/03/18 20:23:20 by tgauvrit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void	input_loop(t_env *env)
{
	char			input_string[8];
	unsigned long	inputs;
	int				width;
	int				height;
	int				size;
	int				extra;

	write(tty_fd(), tgetstr("vi", NULL), 6);
	handle_term(env);
	ft_bzero(input_string, 8);
	while ((read(0, input_string, 6)) != 0)
	{
		inputs = *((unsigned long *)input_string);
		if (inputs == FT_SELECT_KEY_ESCAPE)
			do_abort(0);
		else if (inputs == FT_SELECT_KEY_SPACE && (inputs = FT_SELECT_KEY_DOWN))
			env->selected[env->curr_arg] = (env->selected[env->curr_arg] + 1) % 2;
		if (inputs == FT_SELECT_KEY_UP)
			env->curr_arg = (env->curr_arg == 0 ? env->argc - 1 : env->curr_arg - 1);
		else if (inputs == FT_SELECT_KEY_DOWN)
			env->curr_arg = (env->curr_arg == env->argc - 1 ? 0 : env->curr_arg + 1);
		else if (inputs == FT_SELECT_KEY_LEFT && (env->height - 1) < env->argc)
			env->curr_arg -= (env->height - 1);
		else if (inputs == FT_SELECT_KEY_RIGHT && (env->height - 1) < env->argc)
			env->curr_arg += (env->height - 1);
		else if (inputs == FT_SELECT_KEY_BACKSPACE || inputs == FT_SELECT_KEY_DELETE)
			do_delete(env);
		else if (inputs == FT_SELECT_KEY_ENTER)
			do_return(env);
		height = env->height - 1;
		width = ((env->argc - 1) / height) + 1;
		size = width * height;
		extra = env->argc % height;
		if (env->curr_arg < 0)
		{
			env->curr_arg += size;
			if (env->curr_arg > env->argc - 1)
				env->curr_arg -= height;
		}
		if (env->curr_arg > env->argc - 1)
		{
			env->curr_arg -= size;
			if (env->curr_arg < 0)
				env->curr_arg += height;
		}
		handle_term(env);
		ft_bzero(input_string, 8);
	}
}
