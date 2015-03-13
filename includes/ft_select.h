/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgauvrit <tgauvrit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/26 16:57:01 by tgauvrit          #+#    #+#             */
/*   Updated: 2015/03/13 18:11:07 by tgauvrit         ###   ########.fr       */
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

# define TERM_BUF 4000

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
	int				put;
	int				curr_arg;
	int				col_width;
}					t_env;

#endif
