# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jleem <jleem@student.42seoul.kr>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/28 23:28:03 by jleem             #+#    #+#              #
#    Updated: 2021/10/05 01:50:02 by jleem            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC				?= clang

WFLAGS			= -Wall -Wextra #-Werror
INCFLAGS		= -I$(INCDIR) -I$(LIBFTDIR)
CFLAGS_			= $(WFLAGS) $(INCFLAGS) $(CFLAGS)
unexport CFLAGS_

NAME			= pipex
SRCDIR			= src
INCDIR			= includes
OBJDIR			= build

SRCS			= $(wildcard $(SRCDIR)/*.c)
OBJS			= $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRCS))

LIBFT			= $(LIBFTDIR)/libft.a
LIBFTDIR		= libft
SUBMODULES		= $(LIBFT)

all				: $(NAME)

testarg			:
	env

$(NAME)			: $(OBJS) $(SUBMODULES)
	$(CC) $(CFLAGS_) $^  -o $@

$(OBJDIR)		:
	mkdir -p $@

$(OBJDIR)/%.o	: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS_) -c $^ -o $@

$(LIBFT)		:
	$(MAKE) -j 16 -C $(LIBFTDIR) bonus

.PHONY			: clean
clean			:
	$(RM) -r $(OBJDIR)
	$(MAKE) -C $(LIBFTDIR) clean

.PHONY			: fclean
fclean			: clean
	$(RM) $(NAME)
	$(MAKE) -C $(LIBFTDIR) fclean

.PHONY			: re
re				:
	$(MAKE) fclean
	$(MAKE) all

.PHONY			: bonus
bonus			: all
