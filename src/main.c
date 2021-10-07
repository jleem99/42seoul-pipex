/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleem <jleem@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 01:40:23 by jleem             #+#    #+#             */
/*   Updated: 2021/10/07 20:14:08 by jleem            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_parse.h"
#include "ft_spawn.h"
#include "ft_error.h"
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <stdlib.h>

void	pipex(t_parsed_arg *arg)
{
	t_pipe_spawner	*spawner;
	int				fd_infile;
	int				fd_outfile;
	int				pipe_exit_status;
	int				i;

	fd_infile = open(arg->infile, O_RDONLY); // Todo: Handle error
	fd_outfile = open(arg->outfile, O_WRONLY | O_CREAT, 0644); // Todo: Handle error
	spawner = init_pipe_spawner(arg->num_commands - 1);
	spawner_redirect_from_fd(spawner, arg->commands[0], fd_infile);
	i = 1;
	while (i < arg->num_commands - 1)
	{
		spawner_pipe_command(spawner, arg->commands[i]);
		i++;
	}
	spawner_redirect_to_fd(spawner, arg->commands[i], fd_outfile);
	spawner_wait_processes(spawner);
	pipe_exit_status = spawner->processes[spawner->n_processes - 1].status;
	free_pipe_spawner(spawner);
	exit(WEXITSTATUS(pipe_exit_status));
}

int main(int argc, char const *argv[])
{
	t_parsed_arg	arg;

	arg = parse_arg(argc, argv);
	if (arg.commands == NULL)
	{
		handle_invalid_arg();
	}
	else
	{
		pipex(&arg);
	}
	return (0);
}
