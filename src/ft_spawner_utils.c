/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_spawner_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleem <jleem@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 23:45:46 by jleem             #+#    #+#             */
/*   Updated: 2021/10/09 01:23:37 by jleem            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_spawner.h"
#include "ft_exec.h"
#include "ft_error.h"
#include "libft_bonus.h"
#include <unistd.h>
#include <stdlib.h>

static void	child_routine(t_process *process)
{
	process_close_unused_pipeends(process);
	if (process->spawn_err)
		handle_error(process->spawn_err);
	else if (ft_execvp(process->execfile, process->argv) == -1)
		handle_exec_error(process->execfile);
	exit(FT_EXIT_UREACHBL);
}

void	ft_spawn(t_process *process)
{
	int const	pid = fork();

	if (pid < 0)
		handle_error(FT_EFORK);
	else if (pid == 0)
		child_routine(process);
	else
		process_parental_cleanup(process, pid);
}

t_pipe_spawner	*make_pipe_spawner(int n_commands, char *const *commands)
{
	// Todo: Use t_array for processes / pipes
	t_pipe_spawner	*spawner;
	int const		n_pipes = n_commands - 1;
	int				i;

	spawner = malloc(sizeof(t_pipe_spawner));
	if (!spawner)
		handle_error(FT_ENOMEM);
	spawner->processes = ft_calloc(n_commands, sizeof(t_process));
	spawner->n_processes = n_commands;
	spawner->pipes = ft_calloc(n_pipes, sizeof(t_pipe));
	spawner->n_pipes = n_pipes;
	if (!spawner->processes || !spawner->pipes)
		handle_error(FT_ENOMEM);
	i = 0;
	while (i < spawner->n_pipes)
		pipe(spawner->pipes[i++].fildes);
	i = 0;
	while (i < spawner->n_processes)
	{
		init_process(&spawner->processes[i], commands[i]);
		if (i != 0)
			spawner->processes[i].lpipe = spawner->pipes[i - 1];
		if (i != spawner->n_processes - 1)
			spawner->processes[i].rpipe = spawner->pipes[i];
		i++;
	}
	return (spawner);
}

void	free_pipe_spawner(t_pipe_spawner *spawner)
{
	free(spawner->processes);
	free(spawner->pipes);
	free(spawner);
}
