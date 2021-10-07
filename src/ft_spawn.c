/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_spawn.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleem <jleem@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 23:45:46 by jleem             #+#    #+#             */
/*   Updated: 2021/10/08 00:03:59 by jleem            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_spawn.h"
#include "ft_exec.h"
#include "ft_error.h"
#include "libft_bonus.h"
#include <unistd.h>
#include <stdlib.h>

void	ft_spawn(t_piped_process *process)
{
	char **const	argv = ft_split(process->command, ' ');
	char *const		file = argv[0];
	int const		pid = fork();

	if (pid < 0)
	{
		handle_error(FT_EFORK);
	}
	else if (pid == 0)
	{
		close(process->lpipe.fd_write);
		close(process->rpipe.fd_read);
		if (ft_execvp(file, argv) == -1)
			handle_error(FT_EEXEC);
	}
	ft_free_split(argv);
}

t_pipe_spawner	*init_pipe_spawner(int n_processes)
{
	// Todo: Use t_array for processes / pipes
	t_pipe_spawner	*spawner;
	int const		n_pipes = n_processes - 1;
	int				i;

	spawner = malloc(sizeof(t_pipe_spawner));
	if (!spawner)
		handle_error(FT_ENOMEM);
	spawner->processes = malloc(sizeof(t_piped_process) * n_processes);
	spawner->n_processes = n_processes;
	spawner->pipes = malloc(sizeof(t_pipe) * n_pipes);
	spawner->n_pipes = n_pipes;
	if (!spawner->pipes || !spawner->processes)
		handle_error(FT_ENOMEM);
	i = 0;
	while (i < n_pipes)
		pipe(spawner->pipes[i++].fildes);
	spawner->pipe_idx = 0;
	return (spawner);
}

void	free_pipe_spawner(t_pipe_spawner *spawner)
{
	free(spawner->processes);
	free(spawner->pipes);
	free(spawner);
}
