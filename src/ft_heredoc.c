/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleem <jleem@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 08:13:30 by jleem             #+#    #+#             */
/*   Updated: 2021/10/12 09:54:17 by jleem            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_heredoc.h"
#include "get_next_line.h"
#include "libft_bonus.h"
#include "ft_error.h"
#include "ft_spawner.h"
#include <fcntl.h>
#include <stdio.h>

static char	*append_and_free_line(char *buffer, char *line)
{
	char *const	line_with_newline = ft_strjoin(line, "\n");
	char *const	new_buffer = ft_strjoin(buffer, line_with_newline);

	if (!line_with_newline || !new_buffer)
		handle_error(FT_ENOMEM);
	free(line_with_newline);
	free(buffer);
	free(line);
	return (new_buffer);
}

static char	*heredoc(char const *limiter)
{
	char	*buffer;
	char	*line;
	int		gnl_ret;

	buffer = ft_strdup("");
	if (!buffer)
		handle_error(FT_ENOMEM);
	line = NULL;
	gnl_ret = 1;
	while (gnl_ret > 0)
	{
		write(STDOUT_FILENO, "heredoc> ", 10);
		gnl_ret = get_next_line(STDIN_FILENO, &line);
		if (ft_strcmp(line, limiter) == 0 || gnl_ret == 0)
		{
			free(line);
			break ;
		}
		buffer = append_and_free_line(buffer, line);
	}
	if (gnl_ret < 0)
		handle_error(FT_EHEREDOC);
	return (buffer);
}

void	heredoc_writer(int *pipe_fildes, char *buffer)
{
	close(pipe_fildes[0]);
	write(pipe_fildes[1], buffer, ft_strlen(buffer));
	close(pipe_fildes[1]);
	exit(EXIT_SUCCESS);
}

#define A_BCYAN		"\033[0;96m"
#define A_RESET		"\033[0m"

int	get_heredoc_writer(char const *limiter)
{
	int		writer_pid;
	int		pipe_fildes[2];
	char	*heredoc_buffer;

	if (pipe(pipe_fildes) == -1)
		handle_error(FT_EPIPE);
	heredoc_buffer = heredoc(limiter);
	writer_pid = fork();
	if (writer_pid < 0)
		handle_error(FT_EHEREDOC);
	else if (writer_pid == 0)
		heredoc_writer(pipe_fildes, heredoc_buffer);
	else
		close(pipe_fildes[1]);
	if (DEBUG_PROCESSES)
		printf(A_BCYAN"heredoc(writer_pid: %5d)"A_RESET"\n", writer_pid);
	return (pipe_fildes[0]);
}
