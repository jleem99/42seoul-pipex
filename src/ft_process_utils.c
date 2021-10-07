/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_process_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleem <jleem@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 04:37:05 by jleem             #+#    #+#             */
/*   Updated: 2021/10/08 08:48:07 by jleem            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_process.h"
#include <sys/wait.h>

#define A_RESET		"\033[0m"
#define A_GREEN		"\033[0;92m"
#define A_BBLUE		"\033[0;94m"
#define A_MAGENTA	"\033[0;35m"

#include <stdio.h>
void	inspect_process(t_process *process)
{
	if (process->redirection.fd_in > 0)
		printf(A_MAGENTA"     redirection(%3d)"A_RESET" -/-> ",
			process->redirection.fd_in);
	else
		printf(A_BBLUE"lpipe(w:%3d -> r:%3d)"A_RESET" -/-> ",
			process->lpipe.fd_write, process->lpipe.fd_read);
	printf(A_GREEN"(pid: %5d | cmd: %13s | exit: %3d | sig: %2d)"A_RESET" -/-> ",
		process->pid, process->command,
		WEXITSTATUS(process->status), WTERMSIG(process->status));
	if (process->redirection.fd_out > 0)
		printf(A_MAGENTA"redirection(%3d)"A_RESET"\n",
			process->redirection.fd_out);
	else
		printf(A_BBLUE"lpipe(w:%3d -> r:%3d)"A_RESET"\n",
			process->rpipe.fd_write, process->rpipe.fd_read);
}
