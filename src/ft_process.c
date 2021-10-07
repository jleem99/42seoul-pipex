/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_process.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleem <jleem@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 17:51:48 by jleem             #+#    #+#             */
/*   Updated: 2021/10/08 08:25:07 by jleem            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_process.h"
#include "ft_error.h"
#include "libft_bonus.h"
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

void	process_backup_stdio(t_process *process)
{
	process->stdin_save = dup(STDIN_FILENO);
	process->stdout_save = dup(STDOUT_FILENO);
}

void	process_pipe_stdio(t_process *process)
{
	if (process->lpipe.fd_read > 0)
	{
		dup2(process->lpipe.fd_read, STDIN_FILENO);
		close(process->lpipe.fd_read);
	}
	if (process->rpipe.fd_read > 0)
	{
		dup2(process->rpipe.fd_write, STDOUT_FILENO);
		close(process->rpipe.fd_write);
	}
	if (process->redirection.fd_in > 0)
		dup2(process->redirection.fd_in, STDIN_FILENO);
	if (process->redirection.fd_out > 0)
		dup2(process->redirection.fd_out, STDOUT_FILENO);
}

void	process_restore_stdio(t_process *process)
{
	dup2(process->stdin_save, STDIN_FILENO);
	dup2(process->stdout_save, STDOUT_FILENO);
	close(process->stdin_save);
	close(process->stdout_save);
}

void	process_close_unused_pipeends(t_process *process)
{
	close(process->stdin_save);
	close(process->stdout_save);
	if (process->rpipe.fd_read > 0)
		close(process->rpipe.fd_read);
}

void	init_process(t_process *process, char const *command)
{
	char **const	argv = ft_split(command, ' ');
	char *const		execfile = argv[0];

	ft_bzero(process, sizeof(t_process));
	process->command = command;
	process->execfile = execfile;
	process->argv = argv;
	process->lpipe.fd_read = -1;
	process->lpipe.fd_write = -1;
	process->rpipe.fd_read = -1;
	process->rpipe.fd_write = -1;
	process->redirection.fd_in = -1;
	process->redirection.fd_out = -1;
	process->stdin_save = -1;
	process->stdout_save = -1;
}

void	process_parental_cleanup(t_process *process, int pid)
{
	process->pid = pid;
	ft_free_split((void *)process->argv);
	if (process->redirection.fd_in > -1)
		close(process->redirection.fd_in);
	if (process->redirection.fd_out > -1)
		close(process->redirection.fd_out);
	// Todo: free(process);
}

void	process_redirect_from(t_process *process, char const *infile)
{
	int	const	fd_infile = open(infile, O_RDONLY); // Todo: Handle error

	process->redirection.fd_in = fd_infile;
	if (fd_infile < 0)
		process->spawn_err = FT_ENOENT;
}

void	process_redirect_to(t_process *process, char const *outfile)
{
	int const	fd_outfile = open(outfile, O_WRONLY | O_CREAT, 0644); // Todo: Handle error

	process->redirection.fd_out = fd_outfile;
	if (fd_outfile < 0)
		process->spawn_err = FT_ENOENT;
}
