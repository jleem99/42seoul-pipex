/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_spawn.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleem <jleem@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 23:42:50 by jleem             #+#    #+#             */
/*   Updated: 2021/10/08 01:05:55 by jleem            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SPAWN_H
# define FT_SPAWN_H

# include "ft_process.h"

typedef struct	s_pipe_spawner
{
	t_piped_process	*processes;
	int				n_processes;
	t_pipe			*pipes;
	int				n_pipes;
	int				pipe_idx;
}				t_pipe_spawner;

/* ft_spawn.c */
void			ft_spawn(t_piped_process *process);
t_pipe_spawner	*init_pipe_spawner(int n_pipes);
void			free_pipe_spawner(t_pipe_spawner *spawner);

/* ft_spawner_func.c */
void			spawner_pipe_command(t_pipe_spawner *spawner,
					char const *command);
void			spawner_redirect_from_file(t_pipe_spawner *spawner,
					char const *command, char const *infile);
void			spawner_redirect_to_file(t_pipe_spawner *spawner,
					char const *command, char const *outfile);
void			spawner_wait_processes(t_pipe_spawner *spawner);

#endif
