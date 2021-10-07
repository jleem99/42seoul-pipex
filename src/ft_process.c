/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_process.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleem <jleem@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 17:51:48 by jleem             #+#    #+#             */
/*   Updated: 2021/10/07 17:55:04 by jleem            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_process.h"
#include <unistd.h>

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
