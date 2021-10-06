/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_spawn.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleem <jleem@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 23:45:46 by jleem             #+#    #+#             */
/*   Updated: 2021/10/07 00:04:12 by jleem            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_spawn.h"
#include "ft_exec.h"
#include "ft_error.h"
#include "libft_bonus.h"
#include <unistd.h>
#include <sys/wait.h>

void	ft_spawn(char const *cmd)
{
	char **const	argv = ft_split(cmd, ' ');
	char *const		file = argv[0];
	int const		pid = fork();

	// Todo: Cleanup free_split calls
	if (pid < 0)
	{
		ft_free_split(argv);
		handle_error(FT_EFORK);
	}
	else if (pid == 0)
	{
		if (ft_execvp(file, argv) == -1)
		{
			ft_free_split(argv);
			handle_error(FT_EEXEC);
		}
	}
	else
	{
		ft_free_split(argv);
		waitpid(pid, NULL, WNOHANG); // WNOHANG | WUNTRACED
	}
}

t_pipe_spawner	init_pipe_spawner(char const *cmd1, char const *cmd2)
{
	t_pipe_spawner	pipe_spawner;
	int				fildes[2];

	ft_bzero(&pipe_spawner, sizeof(t_pipe_spawner));
	if (pipe(fildes) == -1)
	{
		handle_error(FT_EPIPE);
	}
	else
	{
		pipe_spawner.fd_read = fildes[0];
		pipe_spawner.fd_write = fildes[1];
		pipe_spawner.cmd1 = cmd1;
		pipe_spawner.cmd2 = cmd2;
	}
	return (pipe_spawner);
}

void	spawn_pipe_writer(t_pipe_spawner *spawner)
{
	int const	stdout_dup = dup(STDOUT_FILENO); // Todo: Handle error

	dup2(spawner->fd_write, STDOUT_FILENO);
	ft_spawn(spawner->cmd1);
	dup2(stdout_dup, STDOUT_FILENO);
	close(stdout_dup);
	close(spawner->fd_write);
}

void	spawn_pipe_reader(t_pipe_spawner *spawner)
{
	int const	stdin_dup = dup(STDIN_FILENO); // Todo: Handle error

	dup2(spawner->fd_read, STDIN_FILENO);
	ft_spawn(spawner->cmd2);
	dup2(stdin_dup, STDIN_FILENO);
	close(stdin_dup);
	close(spawner->fd_read);
}

void	spawn_pipe(t_pipe_spawner *spawner)
{
	spawn_pipe_writer(spawner);
	spawn_pipe_reader(spawner);
}
