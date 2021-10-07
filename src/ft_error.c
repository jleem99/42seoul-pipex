/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleem <jleem@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 23:42:03 by jleem             #+#    #+#             */
/*   Updated: 2021/10/07 21:27:44 by jleem            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_error.h"
#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

extern int errno;

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
