/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleem <jleem@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 23:42:03 by jleem             #+#    #+#             */
/*   Updated: 2021/10/08 08:47:40 by jleem            ###   ########.fr       */
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
	if (ft_strcmp(err, FT_EEXEC) == 0)
		exit(FT_EXIT_NOCMD);
	else
		exit(EXIT_FAILURE);
}
