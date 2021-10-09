/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleem <jleem@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 08:13:30 by jleem             #+#    #+#             */
/*   Updated: 2021/10/09 11:33:37 by jleem            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_heredoc.h"
#include "get_next_line.h"
#include "libft_bonus.h"
#include "ft_error.h"
#include <fcntl.h>
#include <stdio.h>

static char	*append_and_free_line(char *buffer, char *line)
{
	char *const	line_with_newline = ft_strjoin(line, "\n");
	char *const	new_buffer = ft_strjoin(buffer, line_with_newline);

	free(line_with_newline);
	free(buffer);
	free(line);
	return (new_buffer);
}

static void	heredoc(char const *limiter, int fd_write)
{
	char	*buffer;
	char	*line;
	int		gnl_ret;

	buffer = ft_strdup("");
	line = NULL;
	gnl_ret = 1;
	while (gnl_ret > 0)
	{
		write(STDOUT_FILENO, "heredoc> ", 10);
		gnl_ret = get_next_line(STDIN_FILENO, &line);
		if (ft_strcmp(line, limiter) == 0 || line[0] == '\0')
		{
			free(line);
			break ;
		}
		buffer = append_and_free_line(buffer, line);
	}
	if (gnl_ret < 0)
		handle_error(FT_EHEREDOC);
	write(fd_write, buffer, ft_strlen(buffer));
	close(fd_write);
}

#define ANSI_BRIGHT_CYAN		"\033[0;96m"
#define ANSI_RESET				"\033[0m"

int	init_heredoc(char const *limiter)
{
	int		pid;
	int		fildes[2];

	pipe(fildes);
	pid = fork();
	if (pid < 0)
	{
		handle_error(FT_EHEREDOC);
	}
	else if (pid == 0)
	{
		close(fildes[0]);
		heredoc(limiter, fildes[1]);
		exit(EXIT_SUCCESS);
	}
	else
	{
		if (DEBUG_PROCESSES)
			printf(ANSI_BRIGHT_CYAN"heredoc(pid: %5d)"ANSI_RESET"\n", pid);
		close(fildes[1]);
	}
	return (fildes[0]);
}
