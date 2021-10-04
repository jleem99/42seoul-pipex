/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleem <jleem@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 01:40:23 by jleem             #+#    #+#             */
/*   Updated: 2021/10/05 01:50:42 by jleem            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft_bonus.h"

#include <stdio.h>

int main(int argc, char const *argv[], char *envp[])
{
	if (argc <= 1)
		return (-1);
	// if (argc != 1 + 4)
	// 	return (-1);

	char const *const infile = argv[1];
	char const *const cmd1 = argv[2];
	char const *const cmd2 = argv[3];
	char const *const outfile = argv[4];

	int ret;
	// ret = execlp("/bin/ls", "ls", "-laG", "/usr", NULL);

	ret = ft_execvp(infile, argv + 1);
	printf("ret: %d\n", ret);

	return 0;
}
