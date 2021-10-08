/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleem <jleem@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 23:42:03 by jleem             #+#    #+#             */
/*   Updated: 2021/10/08 09:49:53 by jleem            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_error.h"
#include "libft_bonus.h"
#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void	handle_invalid_arg(void)
{
	ft_putendl_fd("Error: Invalid arguments", STDERR_FILENO);
	exit(EXIT_FAILURE);
}

void	handle_error(char const *err)
{
	perror(err);
	exit(EXIT_FAILURE);
}

void	handle_exec_error(char const *execfile)
{
	if (errno == EACCES)
	{
		ft_putstr_fd("permission denied: ", STDERR_FILENO);
		ft_putendl_fd(execfile, STDERR_FILENO);
		exit(EXIT_FAILURE); // exit(FT_EXIT_NOACCES)
	}
	else if (errno == ENOENT)
	{
		ft_putstr_fd("command not found: ", STDERR_FILENO);
		ft_putendl_fd(execfile, STDERR_FILENO);
		exit(FT_EXIT_NOCMD);
	}
	else
	{
		handle_error(FT_EEXEC);
	}
}
