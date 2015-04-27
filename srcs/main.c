/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgauvrit <tgauvrit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/11 16:16:41 by tgauvrit          #+#    #+#             */
/*   Updated: 2015/04/27 19:22:31 by tgauvrit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

int		main(int argc, char **argv)
{
	t_env	env;
	int		ret;
	int		selected[argc];

	if (argc < 2)
		print_error("./ft_select input [input...]\n");
	ft_bzero(&env, sizeof(env));
	env.argc = argc - 1;
	env.argv = argv + 1;
	env.col_width = get_col_width(env.argv, env.argc);
	ft_bzero(selected, argc * sizeof(int));
	env.selected = selected;
	if ((env.termtype = getenv("TERM")) == NULL)
		print_error("Specify a terminal with 'setenv TERM'\n");
	if ((ret = tgetent(env.term_buffer, env.termtype)) <= 0)
		throw_error(NULL);
	env.width = tgetnum("co");
	env.height = tgetnum("li");
	get_env(&env);
	env.ti = 0;
	do_startup(0);
	input_loop(&env);
	return (0);
}
