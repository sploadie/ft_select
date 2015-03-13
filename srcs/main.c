/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgauvrit <tgauvrit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/11 16:16:41 by tgauvrit          #+#    #+#             */
/*   Updated: 2015/03/13 20:27:49 by tgauvrit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void	throw_error(char *str)
{
	perror(str);
	exit(1);
}

void	print_error(char *str)
{
	ft_putstr_fd(str, 2);
	exit(1);
}

void	ft_strjoinfree(char **line, char *add)
{
	char	*to_free;

	to_free = *line;
	*line = ft_strjoin(*line, add);
	if (*line == NULL)
		throw_error(NULL);
	free(to_free);
}

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

t_env	*get_env(t_env *env)
{
	static t_env	*saved;

	if (env != NULL)
		saved = env;
	return (saved);
}

int		tty_fd(void)
{
	static int	fd = -1;

	if (fd == -1)
		fd = open("/dev/tty", O_WRONLY);
	return (fd);
}

void	handle_term(t_env *env)
{
	char	*output;
	int		i;

	if (env->argc > env->height || env->col_width > env->width)//((1 + (env->argc / env->height)) * env->col_width > env->width)
	{
		write(tty_fd(), "Increase window size...\n", 24);
		return ;
	}
	output = ft_strdup(tgoto(tgetstr("cm", NULL), 0, 0));
	ft_strjoinfree(&output, tgetstr("cd", NULL));
	i = 0;
	while (i < env->argc)
	{
		if (i == env->curr_arg)
			ft_strjoinfree(&output, tgetstr("us", NULL));
		if (env->selected[i] == 1)
			ft_strjoinfree(&output, tgetstr("mr", NULL));
		ft_strjoinfree(&output, env->argv[i]);
		ft_strjoinfree(&output, "\n");
		ft_strjoinfree(&output, tgetstr("me", NULL));
		i++;
	}
	ft_strjoinfree(&output, tgoto(tgetstr("cm", NULL), 0, env->curr_arg));//1 + ((env->curr_arg / env->width) * env->col_width), env->curr_arg % env->width));
	write(tty_fd(), output, ft_strlen(output));
	free(output);
}

void	window_size_update(int signum)
{
	t_env			*env;
	struct winsize	win;

	env = get_env(NULL);
	ioctl(0, TIOCGWINSZ, &win);
	// env->width = 1;
	env->width = (int)win.ws_col;
	env->height = (int)win.ws_row;
	write(tty_fd(), tgetstr("cl", NULL), ft_strlen(tgetstr("cl", NULL)));
	handle_term(env);
	(void)signum;
}

void	do_abort(int signum)
{
	t_env	*env;

	write(tty_fd(), tgoto(tgetstr("cm", NULL), 0, 0), ft_strlen(tgoto(tgetstr("cm", NULL), 0, 0)));
	write(tty_fd(), tgetstr("cd", NULL), 3);
	write(tty_fd(), tgetstr("ve", NULL), 12);
	close(tty_fd());
	env = get_env(NULL);
	tcsetattr(0, 0, env->old_term);
	exit(signum);
}

void	input_loop(t_env *env)
{
	char			input_string[8];
	unsigned long	inputs;
	char			str[200];

	write(tty_fd(), tgetstr("vi", NULL), 6);
	handle_term(env);
	ft_bzero(input_string, 8);
	env->put = 0;
	while ((read(0, input_string, 6)) != 0)
	{
		inputs = *((unsigned long *)input_string);
		//DEBUG
		write(tty_fd(), str, sprintf(str, "(%3d, %3d, %3d, %3d, %3d, %3d)\n%.12lx\n", input_string[0], input_string[1], input_string[2], input_string[3], input_string[4], input_string[5], inputs));
		//DEBUG
		handle_term(env);
		ft_bzero(input_string, 8);
	}
}

int		main(int argc, char **argv)
{
	t_env	env;
	int		ret;
	int		selected[argc];

	if (argc < 2)
		print_error("./ft_select input [input...]\n");
	//Clear env
	ft_bzero(&env, sizeof(env));
	//Get input
	env.argc = argc - 1;
	env.argv = argv + 1;
	//Get input 'width'
	env.col_width = get_col_width(env.argv, env.argc);
	//Prepare selected list
	ft_bzero(selected, argc * sizeof(int));
	env.selected = selected;
	//Get terminal type
	if ((env.termtype = getenv("TERM")) == NULL)
		print_error("Specify a terminal with 'setenv TERM'\n");
	//Fill terminal buffer
	if ((ret = tgetent(env.term_buffer, env.termtype)) <= 0)
		throw_error(NULL);
	//Get window size
	env.width = tgetnum("co");
	env.height = tgetnum("li");
	//Get terminal data
	tcgetattr(0, &env.term);
	env.term.c_lflag &= ~(ICANON);
	env.term.c_lflag &= ~(ECHO);
	env.term.c_cc[VMIN] = 1;
	env.term.c_cc[VTIME] = 0;
	tcgetattr(0, env.old_term);
	if (tcsetattr(0, TCSADRAIN, &env.term) == -1)
		throw_error(NULL);
	//Save env for global use
	get_env(&env);
	//Set signal catchers
	signal(SIGWINCH, &window_size_update);
	signal(SIGINT, &do_abort);
	signal(SIGINT, &do_abort);
	signal(SIGHUP, &do_abort);
	signal(SIGTERM, &do_abort);
	signal(SIGSTOP, &do_abort);
	signal(SIGCONT, &do_abort);
	signal(SIGSEGV, &do_abort);
	signal(SIGQUIT, &do_abort);
	signal(SIGFPE, &do_abort);
	signal(SIGALRM, &do_abort);
	signal(SIGKILL, &do_abort);
	signal(SIGABRT, &do_abort);
	signal(SIGUSR1, &do_abort);
	signal(SIGUSR2, &do_abort);
	//Start input loop
	input_loop(&env);
	//In case of read loop escape
	close(tty_fd());
	return (0);
}

/*
int		main(int argc, char **argv)
{
	char	str[2048];
	char	*termtype = getenv("TERM");
	char	term_buffer[2048];
	int		success;

	(void)argc;
	(void)argv;
	bzero(term_buffer, 2048);
	write(1, str, sprintf(str, "= Begin =\n"));
	// ------------------------------------------------------------ //
	//Check termtype global:
	if (termtype == NULL)
		printf("Specify a terminal type in your environment.\n");
	success = tgetent(term_buffer, termtype);
	// - Handle errors:
	if (success < 0)
	{
		printf("Could not access the termcap data base.\n");
		return (0);
	}
	if (success == 0)
	{
		printf("Terminal type '%s' is not defined.\n", termtype);
		return (0);
	}
	printf("Terminal type '%s' is defined!\n", termtype);
	printf("Terminal buffer: '%s'\n", term_buffer);
	printf("Success: '%d'\n", success);
	//Get info about terminal:
	printf("Terminal Size: (% 3d, % 3d)\n", tgetnum("co"), tgetnum("li"));
	printf("vi: '%s'\n", tgetstr("vi", NULL));
	printf("vi: '%s'\n", tgetstr("vi", NULL));
	// ------------------------------------------------------------ //
	write(1, str, sprintf(str, "=  End  =\n"));
	return (0);
}
*/
