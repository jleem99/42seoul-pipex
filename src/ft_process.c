/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_process.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleem <jleem@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 17:51:48 by jleem             #+#    #+#             */
/*   Updated: 2021/10/12 09:46:51 by jleem            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_process.h"
#include "ft_error.h"
#include "ft_parse.h"
#include "libft_bonus.h"
#include <fcntl.h>

void	init_process(t_process *process, char const *command)
{
	char **const	argv = parse_command(command);
	char			*execfile;

	execfile = NULL;
	if (!argv)
		handle_error(FT_ENOMEM);
	else
		execfile = argv[0];
	ft_bzero(process, sizeof(t_process));
	if (execfile == NULL)
		process->spawn_err = FT_EINVLCMD;
	process->command = command;
	process->execfile = execfile;
	process->argv = argv;
	process->lpipe.fd_read = -1;
	process->lpipe.fd_write = -1;
	process->rpipe.fd_read = -1;
	process->rpipe.fd_write = -1;
	process->redirection.fd_in = -1;
	process->redirection.fd_out = -1;
}

void	process_parental_cleanup(t_process *process, int pid)
{
	process->pid = pid;
	close(process->lpipe.fd_read);
	close(process->rpipe.fd_write);
	ft_free_split((void *)process->argv);
	if (process->redirection.fd_in > -1)
		close(process->redirection.fd_in);
	if (process->redirection.fd_out > -1)
		close(process->redirection.fd_out);
}

void	process_redirect_from_file(t_process *process, char const *infile)
{
	int const	fd_infile = open(infile, O_RDONLY);

	if (fd_infile < 0)
		process->spawn_err = FT_EINPUT;
	else
		process->redirection.fd_in = fd_infile;
}

void	process_redirect_to_file(t_process *process, char const *outfile)
{
	int const	fd_outfile = open(outfile, O_WRONLY | O_TRUNC | O_CREAT, 0644);

	if (fd_outfile < 0)
		process->spawn_err = FT_EOUTPUT;
	else
		process->redirection.fd_out = fd_outfile;
}

void	process_redirect_to_file_append(t_process *process,
			char const *outfile)
{
	int const	fd_outfile = open(outfile, O_WRONLY | O_APPEND | O_CREAT, 0644);

	if (fd_outfile < 0)
		process->spawn_err = FT_EOUTPUT;
	else
		process->redirection.fd_out = fd_outfile;
}
