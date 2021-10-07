/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_spawn2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleem <jleem@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 23:45:46 by jleem             #+#    #+#             */
/*   Updated: 2021/10/07 18:05:13 by jleem            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_spawn.h"
#include "ft_process.h"

#include <stdio.h>
void	spawn_piped_process(t_piped_process *process)
{
	backup_process_stdio(process);
	pipe_process_stdio(process);
	ft_spawn(process);
	restore_process_stdio(process);
	printf("lpipe(w:%3d -> r:%3d) -/-> command(%10s) -/-> rpipe(w:%3d -> r:%3d)\n",
		process->lpipe.fd_write, process->lpipe.fd_read,
		process->command,
		process->rpipe.fd_write, process->rpipe.fd_read);
}

void	spawner_pipe_command(t_pipe_spawner *spawner, char const *cmd)
{
	t_piped_process	process;
	
	process.lpipe = spawner->pipes[spawner->pipe_idx];
	process.rpipe = spawner->pipes[spawner->pipe_idx + 1];
	spawner->pipe_idx++;
	process.command = cmd;
	spawn_piped_process(&process);
}

void	spawner_redirect_from_fd(t_pipe_spawner *spawner,
			char const *cmd, int fd_from)
{
	t_piped_process	process;

	process.lpipe.fd_read = fd_from;
	process.lpipe.fd_write = -1;
	process.rpipe = spawner->pipes[spawner->pipe_idx];
	process.command = cmd;
	spawn_piped_process(&process);
}

void	spawner_redirect_to_fd(t_pipe_spawner *spawner,
			char const *cmd, int fd_to)
{
	t_piped_process	process;

	process.lpipe = spawner->pipes[spawner->pipe_idx];
	process.rpipe.fd_read = -1;
	process.rpipe.fd_write = fd_to;
	process.command = cmd;
	spawn_piped_process(&process);
}
