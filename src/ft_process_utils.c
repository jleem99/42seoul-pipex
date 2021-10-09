/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_process_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleem <jleem@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 04:37:05 by jleem             #+#    #+#             */
/*   Updated: 2021/10/09 11:30:05 by jleem            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_process.h"
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>

void	process_backup_stdio(t_process *process)
{
	process->stdin_save = dup(STDIN_FILENO);
	process->stdout_save = dup(STDOUT_FILENO);
}

void	process_restore_stdio(t_process *process)
{
	dup2(process->stdin_save, STDIN_FILENO);
	dup2(process->stdout_save, STDOUT_FILENO);
	close(process->stdin_save);
	close(process->stdout_save);
}

void	process_pipe_stdio(t_process *process)
{
	if (process->lpipe.fd_read != -1)
	{
		dup2(process->lpipe.fd_read, STDIN_FILENO);
		close(process->lpipe.fd_read);
	}
	if (process->rpipe.fd_read != -1)
	{
		dup2(process->rpipe.fd_write, STDOUT_FILENO);
		close(process->rpipe.fd_write);
	}
	if (process->redirection.fd_in != -1)
		dup2(process->redirection.fd_in, STDIN_FILENO);
	if (process->redirection.fd_out != -1)
		dup2(process->redirection.fd_out, STDOUT_FILENO);
}

void	process_close_unused_pipeends(t_process *process)
{
	close(process->stdin_save);
	close(process->stdout_save);
	if (process->rpipe.fd_read != -1)
		close(process->rpipe.fd_read);
}

#define A_RESET		"\033[0m"
#define A_GREEN		"\033[0;92m"
#define A_BBLUE		"\033[0;94m"
#define A_BMAGENTA	"\033[0;95m"

void	inspect_process(t_process *process)
{
	if (process->redirection.fd_in >= 0)
		printf(A_BMAGENTA"     redirection(%3d)"A_RESET" -/-> ",
			process->redirection.fd_in);
	else
		printf(A_BBLUE"lpipe(w:%3d -> r:%3d)"A_RESET" -/-> ",
			process->lpipe.fd_write, process->lpipe.fd_read);
	printf(
		A_GREEN"(pid: %5d | cmd: %13s | exit: %3d | sig: %2d)"A_RESET" -/-> ",
		process->pid, process->command,
		WEXITSTATUS(process->status), WTERMSIG(process->status));
	if (process->redirection.fd_out >= 0)
		printf(A_BMAGENTA"redirection(%3d)"A_RESET"\n",
			process->redirection.fd_out);
	else
		printf(A_BBLUE"lpipe(w:%3d -> r:%3d)"A_RESET"\n",
			process->rpipe.fd_write, process->rpipe.fd_read);
}
