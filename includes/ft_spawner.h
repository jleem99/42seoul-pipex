/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_spawner.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleem <jleem@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 23:42:50 by jleem             #+#    #+#             */
/*   Updated: 2021/10/09 07:42:39 by jleem            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SPAWNER_H
# define FT_SPAWNER_H

# include "ft_process.h"

# ifdef DEBUG_PROCESSES
#  define DEBUG_PROCESSES	1
# else
#  define DEBUG_PROCESSES	0
# endif

typedef struct s_pipe_spawner
{
	t_process	*processes;
	int			n_processes;
	t_pipe		*pipes;
	int			n_pipes;
}				t_pipe_spawner;

/* ft_spawner.c */
void			ft_spawn(t_process *process);
t_pipe_spawner	*make_pipe_spawner(int n_commands, char *const *commands);
void			free_pipe_spawner(t_pipe_spawner *spawner);

/* ft_spawner_utils.c */
void			spawner_spawn_processes(t_pipe_spawner *spawner);
void			spawner_wait_processes(t_pipe_spawner *spawner);
void			spawner_inspect_processes(t_pipe_spawner *spawner);

#endif
