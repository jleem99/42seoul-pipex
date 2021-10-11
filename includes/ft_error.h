/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleem <jleem@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 23:41:37 by jleem             #+#    #+#             */
/*   Updated: 2021/10/11 23:37:48 by jleem            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_ERROR_H
# define FT_ERROR_H

# ifndef PROGRAM_NAME
#  define PROGRAM_NAME		"pipex"
# endif
# define FT_EFORK			"fork"
# define FT_EEXEC			"exec"
# define FT_EPIPE			"pipe"
# define FT_ENOMEM			"malloc"
# define FT_EINPUT			"input"
# define FT_EOUTPUT			"output"
# define FT_EINVLARG		"parse arg"
# define FT_EINVLCMD		"parse cmd"
# define FT_EHEREDOC		"heredoc"
# define FT_EXIT_NOACCES	126
# define FT_EXIT_NOCMD		127
# define FT_EXIT_UREACHBL	1

typedef struct s_process	t_process;

void	handle_error(char const *err);
void	handle_exec_error(char const *execfile);

#endif
