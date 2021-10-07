/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_process.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleem <jleem@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 17:54:58 by jleem             #+#    #+#             */
/*   Updated: 2021/10/07 18:05:42 by jleem            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PROCESS_H
# define FT_PROCESS_H

typedef union	u_pipe
{
	int			fildes[2];
	struct
	{
		int		fd_read;
		int		fd_write;
	};
}				t_pipe;

typedef struct	s_piped_process
{
	t_pipe		lpipe;
	t_pipe		rpipe;
	int			stdin_dup;
	int			stdout_dup;
	char const	*command;
}				t_piped_process;

void	backup_process_stdio(t_piped_process *process);
void	pipe_process_stdio(t_piped_process *process);
void	restore_process_stdio(t_piped_process *process);

#endif
