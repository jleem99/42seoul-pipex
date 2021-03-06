/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_process.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleem <jleem@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 17:54:58 by jleem             #+#    #+#             */
/*   Updated: 2021/10/11 22:57:11 by jleem            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PROCESS_H
# define FT_PROCESS_H

typedef union u_pipe
{
	int			fildes[2];
	struct
	{
		int		fd_read;
		int		fd_write;
	};
}				t_pipe;

typedef struct s_redirection
{
	int		fd_in;
	int		fd_out;
}			t_redirection;

typedef struct s_process
{
	char const		*command;
	char const		*execfile;
	char *const		*argv;
	int				pid;
	int				exit_status;
	t_pipe			lpipe;
	t_pipe			rpipe;
	t_redirection	redirection;
	char const		*spawn_err;
}					t_process;

/* ft_process.c */
void	init_process(t_process *process, char const *command);
void	process_parental_cleanup(t_process *process, int pid);
void	process_redirect_from_file(t_process *process, char const *infile);
void	process_redirect_to_file(t_process *process, char const *outfile);
void	process_redirect_to_file_append(t_process *process,
			char const *outfile);

/* ft_process_utils.c */
void	process_pipe_stdio(t_process *process);
void	process_close_unused_pipeends(t_process *process);
void	inspect_process(t_process *process);

#endif
