/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleem <jleem@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 23:42:03 by jleem             #+#    #+#             */
/*   Updated: 2021/10/09 03:05:08 by jleem            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_error.h"
#include "ft_process.h"
#include "libft_bonus.h"
#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void	handle_error(char const *err)
{
	ft_putstr_fd(PROGRAM_NAME": ", STDERR_FILENO);
	if (ft_strcmp(err, FT_EINPUT) == 0 || (ft_strcmp(err, FT_EOUTPUT) == 0))
	{
		ft_putstr_fd(err, STDERR_FILENO);
		ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
	}
	else
	{
		perror(err);
	}
	exit(EXIT_FAILURE);
}

void	handle_exec_error(char const *execfile)
{
	if (errno == EACCES)
	{
		ft_putstr_fd(PROGRAM_NAME": ", STDERR_FILENO);
		ft_putstr_fd(execfile, STDERR_FILENO);
		ft_putstr_fd(": permission denied\n", STDERR_FILENO);
		exit(EXIT_FAILURE); // exit(FT_EXIT_NOACCES)
	}
	else if (errno == ENOENT)
	{
		ft_putstr_fd(PROGRAM_NAME": ", STDERR_FILENO);
		ft_putstr_fd(execfile, STDERR_FILENO);
		ft_putstr_fd(": command not found\n", STDERR_FILENO);
		exit(FT_EXIT_NOCMD);
	}
	else
	{
		handle_error(FT_EEXEC);
	}
}
