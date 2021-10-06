/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleem <jleem@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 01:40:23 by jleem             #+#    #+#             */
/*   Updated: 2021/10/06 23:56:51 by jleem            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_spawn.h"
#include "ft_error.h"
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char const *argv[])
{
	char const		*infile = argv[1];
	char const		*cmd1 = argv[2];
	char const		*cmd2 = argv[3];
	char const		*outfile = argv[4];
	t_pipe_spawner	pipe_spawner;

	if (argc != 1 + 4)
	{
		handle_invalid_arg();
	}
	else
	{
		pipe_spawner = init_pipe_spawner(cmd1, cmd2);
		dup2(open(infile, O_RDONLY), STDIN_FILENO);
		dup2(open(outfile, O_WRONLY | O_CREAT, 0644), STDOUT_FILENO);
		spawn_pipe(&pipe_spawner);
	}
	return (0);
}
