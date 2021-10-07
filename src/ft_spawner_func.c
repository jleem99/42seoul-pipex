/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_spawner_func.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleem <jleem@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 23:45:46 by jleem             #+#    #+#             */
/*   Updated: 2021/10/07 20:16:07 by jleem            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_spawn.h"
#include "ft_process.h"
#include <sys/wait.h>

static void	spawn_piped_process(t_piped_process *process)
{
	backup_process_stdio(process);
	pipe_process_stdio(process);
	ft_spawn(process);
	restore_process_stdio(process);
}

void	spawner_pipe_command(t_pipe_spawner *spawner, char const *cmd)
{
	t_piped_process *const	process =
		&spawner->processes[spawner->pipe_idx + 1];

	process->lpipe = spawner->pipes[spawner->pipe_idx];
	process->rpipe = spawner->pipes[spawner->pipe_idx + 1];
	spawner->pipe_idx++;
	process->command = cmd;
	spawn_piped_process(process);
}

void	spawner_redirect_from_fd(t_pipe_spawner *spawner,
			char const *cmd, int fd_from)
{
	t_piped_process *const	process = &spawner->processes[0];

	process->lpipe.fd_read = fd_from;
	process->lpipe.fd_write = -1;
	process->rpipe = spawner->pipes[0];
	process->command = cmd;
	spawn_piped_process(process);
}

void	spawner_redirect_to_fd(t_pipe_spawner *spawner,
			char const *cmd, int fd_to)
{
	t_piped_process *const	process =
		&spawner->processes[spawner->n_processes - 1];

	process->lpipe = spawner->pipes[spawner->pipe_idx];
	process->rpipe.fd_read = -1;
	process->rpipe.fd_write = fd_to;
	process->command = cmd;
	spawn_piped_process(process);
}

void	spawner_wait_processes(t_pipe_spawner *spawner)
{
	int	status;
	int	i;

	i = 0;
	while (i < spawner->n_processes)
	{
		waitpid(spawner->processes[i].pid, &status, 0);
		spawner->processes[i].status = status;
		i++;
	}
}
