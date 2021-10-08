/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleem <jleem@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 01:40:23 by jleem             #+#    #+#             */
/*   Updated: 2021/10/09 07:48:30 by jleem            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_parse.h"
#include "ft_spawner.h"
#include "ft_error.h"
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

void	pipex(t_parsed_arg *arg)
{
	t_pipe_spawner	*spawner;
	t_process		*first_process;
	t_process		*last_process;
	int				pipe_exit_status;

	spawner = make_pipe_spawner(arg->n_commands, arg->commands);
	first_process = &spawner->processes[0];
	last_process = &spawner->processes[spawner->n_processes - 1];
	process_redirect_from(first_process, arg->infile);
	process_redirect_to(last_process, arg->outfile);
	spawner_spawn_processes(spawner);
	spawner_wait_processes(spawner);
	pipe_exit_status = last_process->status;
	free_pipe_spawner(spawner);
	exit(WEXITSTATUS(pipe_exit_status));
}

int	main(int argc, char const *argv[])
{
	t_parsed_arg	arg;

	arg = parse_arg(argc, argv);
	if (arg.commands == NULL)
		handle_error(FT_EINVLARG);
	else
		pipex(&arg);
	return (0);
}
