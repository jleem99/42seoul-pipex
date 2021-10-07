/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_spawn.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleem <jleem@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 23:42:50 by jleem             #+#    #+#             */
/*   Updated: 2021/10/07 18:00:57 by jleem            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SPAWN_H
# define FT_SPAWN_H

# include "ft_process.h"

typedef struct	s_pipe_spawner
{
	t_pipe		*pipes;
	int			n_pipes;
	int			pipe_idx;
}				t_pipe_spawner;

void			ft_spawn(t_piped_process *process);
t_pipe_spawner	*init_pipe_spawner(int n_pipes);
void			free_pipe_spawner(t_pipe_spawner *spawner);

void			spawn_piped_process(t_piped_process *process);
void			spawner_pipe_command(t_pipe_spawner *spawner,
					char const *command);
void			spawner_redirect_from_fd(t_pipe_spawner *spawner,
					char const *command, int fd_from);
void			spawner_redirect_to_fd(t_pipe_spawner *spawner,
					char const *command, int fd_to);

#endif
