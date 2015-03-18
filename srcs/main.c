/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgauvrit <tgauvrit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/11 16:16:41 by tgauvrit          #+#    #+#             */
/*   Updated: 2015/03/18 19:47:06 by tgauvrit         ###   ########.fr       */
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

void	handle_term(t_env *env)
{
	char	*output;
	int		i;
	int		x;
	int		y;

	if ((1 + (env->argc / (env->height - 1))) * (env->col_width + 1) > env->width)
	{
		write(tty_fd(), "Increase window size...\n", 24);
		return ;
	}
	// output = ft_strdup(tgoto(tgetstr("cm", NULL), 0, 0));
	// ft_strjoinfree(&output, tgetstr("cd", NULL));
	output = ft_strdup(tgoto(tgetstr("cm", NULL), 0, 0));
	clear_terminal(env, &output);
	i = 0;
	while (i < env->argc)
	{
		x = (i / (env->height - 1)) * (env->col_width + 1);
		y = i % (env->height - 1);
		ft_strjoinfree(&output, tgoto(tgetstr("cm", NULL), x, y));
		if (i == env->curr_arg)
			ft_strjoinfree(&output, tgetstr("us", NULL));
		if (env->selected[i] == 1)
			ft_strjoinfree(&output, tgetstr("mr", NULL));
		ft_strjoinfree(&output, env->argv[i]);
		// ft_strjoinfree(&output, "\n");
		ft_strjoinfree(&output, tgetstr("me", NULL));
		i++;
	}
	//ft_strjoinfree(&output, tgoto(tgetstr("cm", NULL), 0, env->curr_arg));//1 + ((env->curr_arg / env->width) * env->col_width), env->curr_arg % env->width));
	write(tty_fd(), output, ft_strlen(output));
	free(output);
}

void	window_size_update(int signum)
{
	t_env			*env;
	struct winsize	win;

	env = get_env(NULL);
	ioctl(0, TIOCGWINSZ, &win);
	env->width = (int)win.ws_col;
	env->height = (int)win.ws_row;
	handle_term(env);
	(void)signum;
}

void	reset_term(t_env *env)
{
	ft_putstr_fd(tgetstr("ve", NULL), tty_fd());
	ft_putstr_fd(tgetstr("te", NULL), tty_fd());
	tcsetattr(0, 0, env->old_term);
	close(tty_fd());
}

void	do_abort(int signum)
{
	reset_term(get_env(NULL));
	// perror(NULL);//DEBUG
	exit(signum);
}

void	do_stop(int signum)
{
	reset_term(get_env(NULL));
	//Handle useless signum
	(void)signum;
}

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
	*(temp - 1) = '\n';
	reset_term(env);
	ft_putstr_fd(str, 1);
	exit(0);
}

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

void	input_loop(t_env *env)
{
	char			input_string[8];
	unsigned long	inputs;
	// char			str[200];
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
		// //DEBUG
		// write(tty_fd(), str, sprintf(str, "(%3d, %3d, %3d, %3d, %3d, %3d)\n%.12lx\n", input_string[0], input_string[1], input_string[2], input_string[3], input_string[4], input_string[5], inputs));
		// ft_bzero(input_string, 8);
		// continue ;
		// //DEBUG
		//If escape, exit
		if (inputs == FT_SELECT_KEY_ESCAPE)
			do_abort(0);
		//If space, make selected. (+ 1 % 2)
		else if (inputs == FT_SELECT_KEY_SPACE && (inputs = FT_SELECT_KEY_DOWN))
			env->selected[env->curr_arg] = (env->selected[env->curr_arg] + 1) % 2;
		//If arrow, move selection
		if (inputs == FT_SELECT_KEY_UP)
			env->curr_arg = (env->curr_arg == 0 ? env->argc - 1 : env->curr_arg - 1);
		else if (inputs == FT_SELECT_KEY_DOWN)
			env->curr_arg = (env->curr_arg == env->argc - 1 ? 0 : env->curr_arg + 1);
		else if (inputs == FT_SELECT_KEY_LEFT && (env->height - 1) < env->argc)
			env->curr_arg -= (env->height - 1);
		else if (inputs == FT_SELECT_KEY_RIGHT && (env->height - 1) < env->argc)
			env->curr_arg += (env->height - 1);
		//If backspace/delete, delete
		else if (inputs == FT_SELECT_KEY_BACKSPACE || inputs == FT_SELECT_KEY_DELETE)
			do_delete(env);
		//If enter, return
		else if (inputs == FT_SELECT_KEY_ENTER)
			do_return(env);
		//Loop around check
		height = env->height - 1;
		width = ((env->argc - 1) / height) + 1;
		size = width * height;
		extra = env->argc % height;
		//=
		if (env->curr_arg < 0)
		{
			env->curr_arg += size;
			if (env->curr_arg > env->argc - 1)
				env->curr_arg -= height;
		}
		//=
		if (env->curr_arg > env->argc - 1)
		{
			env->curr_arg -= size;
			if (env->curr_arg < 0)
				env->curr_arg += height;
		}
		//Draw terminal
		handle_term(env);
		ft_bzero(input_string, 8);
	}
}

void	set_signals(void)
{
	signal(SIGWINCH, &window_size_update);
	signal(SIGCONT, &do_startup);
	// signal(SIGSTOP, &do_stop);
	// signal(SIGTSTP, &do_stop);
	signal(SIGINT, &do_abort);
	signal(SIGINT, &do_abort);
	signal(SIGHUP, &do_abort);
	signal(SIGTERM, &do_abort);
	signal(SIGSEGV, &do_abort);
	signal(SIGQUIT, &do_abort);
	signal(SIGFPE, &do_abort);
	signal(SIGALRM, &do_abort);
	signal(SIGKILL, &do_abort);
	signal(SIGABRT, &do_abort);
	signal(SIGUSR1, &do_abort);
	signal(SIGUSR2, &do_abort);
}

void	do_startup(int signum)
{
	t_env	*env;

	set_signals();
	env = get_env(NULL);
	//Get terminal data
	tcgetattr(0, &env->term);
	env->term.c_lflag &= ~(ICANON);
	env->term.c_lflag &= ~(ECHO);
	env->term.c_cc[VMIN] = 1;
	env->term.c_cc[VTIME] = 0;
	tcgetattr(0, env->old_term);
	if (tcsetattr(0, TCSADRAIN, &env->term) == -1)
		throw_error(NULL);
	//Start separate terminal buffer
	if (env->ti == 0)
	{
		ft_putstr_fd(tgetstr("ti", NULL), tty_fd());
		env->ti = 1;
	}
	//Handle useless signum
	(void)signum;
	// //Restart loop
	// input_loop(env);
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
	//SAVE CURSOR:		sc [save current cursor position (P)]
	//RESTORE CURSOR:	rc [restore cursor to position of last save_cursor]
	//Save env for global use
	get_env(&env);
	//Program loop startup
	env.ti = 0;
	do_startup(0);
	input_loop(&env);
	// ft_putstr_fd("DEBUG", tty_fd());
	// sleep(2);
	//In case of read loop escape
	// ft_putstr_fd(tgetstr("ve", NULL), tty_fd());
	// ft_putstr_fd(tgetstr("te", NULL), tty_fd());
	// tcsetattr(0, 0, env.old_term);
	reset_term(&env);
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
