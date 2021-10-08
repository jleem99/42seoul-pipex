/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleem <jleem@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 00:31:43 by jleem             #+#    #+#             */
/*   Updated: 2021/10/09 01:22:36 by jleem            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_parse.h"
#include "libft_bonus.h"
#include <errno.h>

static t_parsed_arg	parsed_arg_null(void)
{
	t_parsed_arg	parsed_arg;

	ft_bzero(&parsed_arg, sizeof(t_parsed_arg));
	errno = EINVAL;
	return (parsed_arg);
}

static t_parsed_arg	parse_arg_heredoc(int argc, char const *argv[])
{
	t_parsed_arg	parsed_arg;
	int const		n_commands = argc - 4;

	if (n_commands <= 1)
		return (parsed_arg_null());
	parsed_arg.infile = NULL;
	parsed_arg.outfile = argv[argc - 1];
	parsed_arg.commands = (char *const *)(argv + 3);
	parsed_arg.n_commands = n_commands;
	parsed_arg.is_heredoc = 1;
	parsed_arg.heredoc_limiter = argv[2];
	return (parsed_arg);
}

static t_parsed_arg	parse_arg_non_heredoc(int argc, char const *argv[])
{
	t_parsed_arg	parsed_arg;
	int const		n_commands = argc - 3;

	if (n_commands <= 1)
		return (parsed_arg_null());
	parsed_arg.infile = argv[1];
	parsed_arg.outfile = argv[argc - 1];
	parsed_arg.commands = (char *const *)(argv + 2);
	parsed_arg.n_commands = n_commands;
	parsed_arg.is_heredoc = 0;
	return (parsed_arg);
}

t_parsed_arg	parse_arg(int argc, char const *argv[])
{
	if (argc <= 1)
		return (parsed_arg_null());
	else if (ft_strcmp(argv[1], "here_doc") == 0)
		return (parse_arg_heredoc(argc, argv));
	else
		return (parse_arg_non_heredoc(argc, argv));
}
