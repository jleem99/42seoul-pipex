/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_spawner.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleem <jleem@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 23:45:46 by jleem             #+#    #+#             */
/*   Updated: 2021/10/09 07:43:20 by jleem            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_spawner.h"
#include "ft_process.h"
#include "ft_error.h"
#include <sys/wait.h>
#include <unistd.h>

static void	spawn_piped_process(t_process *process)
{
	process_backup_stdio(process);
	process_pipe_stdio(process);
	ft_spawn(process);
	process_restore_stdio(process);
}

void	spawner_spawn_processes(t_pipe_spawner *spawner)
{
	int	i;

	i = 0;
	while (i < spawner->n_processes)
	{
		spawn_piped_process(&spawner->processes[i]);
		i++;
	}
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
	if (DEBUG_PROCESSES)
		spawner_inspect_processes(spawner);
}

void	spawner_inspect_processes(t_pipe_spawner *spawner)
{
	int	i;

	i = 0;
	while (i < spawner->n_processes)
	{
		inspect_process(&spawner->processes[i]);
		i++;
	}
}
