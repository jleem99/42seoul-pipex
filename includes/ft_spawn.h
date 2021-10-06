/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_spawn.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleem <jleem@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 23:42:50 by jleem             #+#    #+#             */
/*   Updated: 2021/10/07 00:03:17 by jleem            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SPAWN_H
# define FT_SPAWN_H

typedef struct	s_pipe_spawner
{
	int			fd_read;
	int			fd_write;
	char const	*cmd1;
	char const	*cmd2;
}				t_pipe_spawner;

void			ft_spawn(char const *cmd);

t_pipe_spawner	init_pipe_spawner(char const *cmd1, char const *cmd2);
void			spawn_pipe_writer(t_pipe_spawner *spawner);
void			spawn_pipe_reader(t_pipe_spawner *spawner);
void			spawn_pipe(t_pipe_spawner *spawner);

#endif
