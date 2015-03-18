/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgauvrit <tgauvrit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/26 16:57:01 by tgauvrit          #+#    #+#             */
/*   Updated: 2015/03/18 21:00:36 by tgauvrit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SELECT_H
# define FT_SELECT_H

/*
** Permitted Functions:
** isatty
** ttyname
** ttyslot
** ioctl
** getenv
** tcsetattr
** tcgetattr
** tgetent
** tgetflag
** tgetnum
** tgetstr
** tgoto
** tputs
** open
** close
** write
** malloc
** free
** read
** exit
** signal
*/

# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <limits.h>
# include <termios.h>
# include <termcap.h>
# include <curses.h>
# include <sys/ioctl.h>
# include "libft.h"

# define FT_SELECT_KEY_ESCAPE 0x1b
# define FT_SELECT_KEY_SPACE 0x20
# define FT_SELECT_KEY_UP 0x415b1b
# define FT_SELECT_KEY_DOWN 0x425b1b
# define FT_SELECT_KEY_RIGHT 0x435b1b
# define FT_SELECT_KEY_LEFT 0x445b1b
# define FT_SELECT_KEY_ENTER 0xa
# define FT_SELECT_KEY_BACKSPACE 0x7f
# define FT_SELECT_KEY_DELETE 0x7e335b1b

typedef struct		s_env
{
	int				argc;
	char			**argv;
	int				*selected;
	char			term_buffer[2048];
	char			*termtype;
	struct termios	term;
	struct termios	*old_term;
	int				width;
	int				height;
	int				curr_arg;
	int				col_width;
	int				ti;
}					t_env;

void				do_startup(int signum);
void				clear_terminal(t_env *env, char **str);
void				window_size_update(int signum);
int					tty_fd(void);
void				reset_term(t_env *env);
void				input_loop(t_env *env);
void				handle_term(t_env *env);
t_env				*get_env(t_env *env);
int					get_col_width(char **list, int size);
void				ft_strjoinfree(char **line, char *add);
void				throw_error(char *str);
void				print_error(char *str);
void				do_startup(int signum);
void				do_return(t_env *env);
void				do_delete(t_env *env);
void				do_abort(int signum);
void				do_stop(int signum);

#endif
