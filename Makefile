# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jleem <jleem@student.42seoul.kr>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/28 23:28:03 by jleem             #+#    #+#              #
#    Updated: 2021/10/09 09:59:50 by jleem            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC				?= clang

WFLAGS			= -Wall -Wextra #-Werror
INCFLAGS		= -I$(INCDIR) -I$(LIBFTDIR) -I$(GNLDIR)
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
GNL				= $(GNLDIR)/get_next_line.a
GNLDIR			= get_next_line
SUBMODULES		= $(LIBFT) $(GNL)

.PHONY			: all
all				: $(NAME)

$(NAME)			: $(OBJS) $(SUBMODULES)
	$(CC) $(CFLAGS_) $^  -o $@

$(OBJDIR)		:
	mkdir -p $@

$(OBJDIR)/%.o	: $(SRCDIR)/%.c $(INCDIR)/*.h | $(OBJDIR)
	$(CC) $(CFLAGS_) -c $< -o $@

$(LIBFT)		:
	$(MAKE) -j 16 -C $(LIBFTDIR) bonus

$(GNL)			:
	$(MAKE) -j 16 -C $(GNLDIR) bonus

.PHONY			: clean
clean			:
	$(RM) -r $(OBJDIR)
	$(MAKE) -C $(LIBFTDIR) clean
	$(MAKE) -C $(GNLDIR) clean

.PHONY			: fclean
fclean			: clean
	$(RM) $(NAME)
	$(MAKE) -C $(LIBFTDIR) fclean
	$(MAKE) -C $(GNLDIR) fclean

.PHONY			: re
re				:
	$(MAKE) fclean
	$(MAKE) all

.PHONY			: bonus
bonus			: all
