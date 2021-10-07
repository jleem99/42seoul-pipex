/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_process.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleem <jleem@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 17:51:48 by jleem             #+#    #+#             */
/*   Updated: 2021/10/08 01:00:55 by jleem            ###   ########.fr       */
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

#define A_RESET		"\033[0m"
#define A_GREEN		"\033[0;92m"
#define A_BBLUE		"\033[0;94m"
#include <stdio.h>
void	inspect_process(t_piped_process *process)
{
	printf(A_BBLUE"lpipe(w:%3d -> r:%3d)"A_RESET" -/-> ",
		process->lpipe.fd_write, process->lpipe.fd_read);
	printf(A_GREEN"(pid: %6d | cmd: %10s | exit: %3d | %2d/%2d)"A_RESET" -/-> ",
		process->pid, process->command, WEXITSTATUS(process->status),
		process->stdin_dup, process->stdout_dup);
	printf(A_BBLUE"lpipe(w:%3d -> r:%3d)"A_RESET"\n",
		process->rpipe.fd_write, process->rpipe.fd_read);
}
