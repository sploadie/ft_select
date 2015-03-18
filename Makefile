# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tgauvrit <tgauvrit@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/11/20 16:35:37 by tgauvrit          #+#    #+#              #
#    Updated: 2015/03/18 20:28:37 by tgauvrit         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =			ft_select

CC =			gcc
FLAGS =			-Wall -Werror -Wextra $(HEADER_FLAGS) -g
HEADER_FLAGS =	-I $(HEADER_DIR) -I $(FT_LIB_DIR)
LIBRARIES =		-L$(FT_LIB_DIR) -l$(FT_LIB_NAME) -ltermcap

FT_LIB_NAME =	ft
FT_LIB_DIR =	./libft/
FT_LIB =		$(FT_LIB_DIR)lib$(FT_LIB_NAME).a

HEADER_DIR =	./includes/
HEADERS =		$(HEADER_DIR)ft_select.h

SRC_DIR =		./srcs/
SRC_COMPILED =	main.o \
				error.o \
				ft_strjoinfree.o \
				get_col_width.o \
				get_env.o \
				tty_fd.o \
				clear_terminal.o \
				handle_term.o \
				window_size_update.o \
				reset_term.o \
				do_abort.o \
				do_return.o \
				do_delete.o \
				input_loop.o \
				do_startup.o

COMPILED =		$(SRC_COMPILED)

all: $(NAME)

$(NAME): $(FT_LIB) $(SRC_COMPILED)
	$(CC) $(FLAGS) $(LIBRARIES) $< $(SRC_COMPILED) -o $@

$(SRC_COMPILED): %.o: $(SRC_DIR)%.c $(HEADERS)
	$(CC) -c $(FLAGS) $< -o $@

$(FT_LIB):
	@make -C $(FT_LIB_DIR);

clean:
	@make clean -C $(FT_LIB_DIR);
	-/bin/rm -f $(COMPILED)

fclean: clean
	-/bin/rm -f $(FT_LIB)
	-/bin/rm -f $(NAME)

re: fclean all
