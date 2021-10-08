/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_command.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleem <jleem@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 01:22:15 by jleem             #+#    #+#             */
/*   Updated: 2021/10/09 02:15:00 by jleem            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_parse.h"
#include "libft_bonus.h"
#include <errno.h>

#define RET_PARSE_UNDONE		2
#define RET_PARSE_DONE_ARG		1
#define RET_PARSE_DONE_NOARG	0
#define RET_PARSE_ERROR			-1

/*
 * Finds next arg from str.
 * This function passes arg's start(inclusive), end(exclusive) pointer-
 * through argument. (char const **start, char const **end)
 *
 * [return values]
 *  2: Parsing undone
 *  1: Parsing done (Args were parsed in this call)
 *  0: Parsing done (No args were parsed in this call)
 * -1: Parsing error
 */
int	find_next_arg(char const *str, char const **start, char const **end)
{
	char	quote;
	int		i;

	i = 0;
	while (str[i] == ' ')
		i++;
	if (str[i] == '\0')
		return (RET_PARSE_DONE_NOARG);
	else if (str[i] == '\'' || str[i] == '"')
		return (find_next_arg_quoted(&str[i + 1], start, end, str[i]));
	else
		return (find_next_arg_spaced(&str[i], start, end));
}

static int	find_next_arg_quoted(char const *str_start,
	char const **start, char const **end, char quote)
{
	char *const	ptr_next_quote = ft_strchr(str_start, quote);

	*start = str_start;
	if (ptr_next_quote == NULL)
	{
		*end = ft_strchr(str_start, '\0');
		return (RET_PARSE_ERROR);
	}
	else
	{
		*end = ptr_next_quote;
		return (RET_PARSE_UNDONE);
	}
}

static int	find_next_arg_spaced(char const *str_start,
	char const **start, char const **end)
{
	char *const	ptr_next_space = ft_strchr(str_start, ' ');

	*start = str_start;
	if (ptr_next_space == NULL)
	{
		*end = ft_strchr(str_start, '\0');
		return (RET_PARSE_DONE_ARG);
	}
	else
	{
		*end = ptr_next_space;
		return (RET_PARSE_UNDONE);
	}
}

int	get_argc(char const *command)
{
	char const	*arg_start;
	char const	*arg_end;
	int			argc;
	char		find_ret;

	argc = 0;
	find_ret = RET_PARSE_UNDONE;
	while (find_ret == RET_PARSE_UNDONE)
	{
		find_ret = find_next_arg(command, &arg_start, &arg_end);
		command = arg_end + 1;
		if (find_ret == RET_PARSE_UNDONE || find_ret == RET_PARSE_DONE_ARG)
			argc++;
	}
	if (find_ret == RET_PARSE_ERROR)
		return (-1);
	else
		return (argc);
}

char	**parse_command(char const *command) // Todo: Handle empty command
{
	char const	*arg_start;
	char const	*arg_end;
	int			argc;
	char		**argv;
	int			i;

	if (command[0] == '\0')
		return (ft_split("", NULL));
	argc = get_argc(command);
	if (argc < 0)
	{
	 	errno = EINVAL;
		return (ft_split("", NULL));
	}
	argv = ft_calloc(argc + 1, sizeof(char *));
	i = 0;
	while (i < argc)
	{
		find_next_arg(command, &arg_start, &arg_end);
		argv[i] = ft_substr(arg_start, 0, arg_end - arg_start);
		command = arg_end + 1;
		i++;
	}
	return (argv);
}
