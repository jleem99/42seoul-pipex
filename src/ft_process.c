/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_process.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleem <jleem@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 17:51:48 by jleem             #+#    #+#             */
/*   Updated: 2021/10/07 21:14:40 by jleem            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_process.h"
#include <unistd.h>
#include <sys/wait.h>

void	backup_process_stdio(t_piped_process *process)
{
	process->stdin_dup = dup(STDIN_FILENO);
	process->stdout_dup = dup(STDOUT_FILENO);
}

void	pipe_process_stdio(t_piped_process *process)
{
	dup2(process->lpipe.fd_read, STDIN_FILENO);
	dup2(process->rpipe.fd_write, STDOUT_FILENO);
	close(process->lpipe.fd_read);
	close(process->rpipe.fd_write);
}

void	restore_process_stdio(t_piped_process *process)
{
	dup2(process->stdin_dup, STDIN_FILENO);
	dup2(process->stdout_dup, STDOUT_FILENO);
	close(process->stdin_dup);
	close(process->stdout_dup);
}

#include <stdio.h>
void	inspect_process(t_piped_process *process)
{
	printf("lpipe(w:%3d -> r:%3d) -/-> (pid: %d | cmd: %10s | exit: %d) -/-> rpipe(w:%3d -> r:%3d)\n",
		process->lpipe.fd_write, process->lpipe.fd_read,
		process->pid, process->command, WEXITSTATUS(process->status),
		process->rpipe.fd_write, process->rpipe.fd_read);
}
