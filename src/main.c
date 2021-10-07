/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleem <jleem@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 01:40:23 by jleem             #+#    #+#             */
/*   Updated: 2021/10/08 01:21:44 by jleem            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_parse.h"
#include "ft_spawn.h"
#include "ft_error.h"
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

#include <errno.h>
#include <stdio.h>
#include <string.h>
void	pipex(t_parsed_arg *arg)
{
	t_pipe_spawner	*spawner;
	int				pipe_exit_status;
	int				i;

	spawner = init_pipe_spawner(arg->num_commands);
	spawner_redirect_from_file(spawner, arg->commands[0], arg->infile);
	i = 1;
	while (i < arg->num_commands - 1)
	{
		spawner_pipe_command(spawner, arg->commands[i++]);
		i++;
	}
	spawner_redirect_to_file(spawner, arg->commands[i], arg->outfile);
	spawner_wait_processes(spawner);

	// for (int i = 0; i < spawner->n_processes; i++)
	// 	inspect_process(&spawner->processes[i]);

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
