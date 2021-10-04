/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleem <jleem@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 19:52:08 by jleem             #+#    #+#             */
/*   Updated: 2021/10/05 01:52:02 by jleem            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_exec.h"
#include "libft_bonus.h"
#include <stdlib.h>

extern char **environ;

char	**get_paths(char *const envp[])
{
	int		i;
	int		is_path;
	char	**paths;
	char	**path_with_trailing_slash;

	i = 0;
	while (envp[i])
	{
		is_path = ft_strncmp(envp[i], "PATH=", 5) == 0;
		if (is_path)
		{
			paths = ft_split(envp[i] + 5, ':');
			return (paths);
		}
		i++;
	}
	i = 0;
	return NULL;
}

char	*join_path(char const *s1, char const *s2)
{
	char	*joined_path;
	int const	s1_len = ft_strlen(s1);
	int const	s2_len = ft_strlen(s2);
	
	joined_path = malloc(s1_len + s2_len + 2);
	ft_memcpy(joined_path, s1, s1_len);
	joined_path[s1_len] = '/';
	ft_memcpy(joined_path + s1_len + 1, s2, s2_len);
	joined_path[s1_len + s2_len + 1] = '\0';
	return (joined_path);
}

char	*find_executable_file_path(char const *file)
{
	int		i;
	char	**paths;
	char	*file_path;

	paths = get_paths(environ);
	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		file_path = join_path(paths[i], file);
		if (access(file_path, X_OK) == 0)
			return (file_path);
		free(file_path);
		i++;
	}
	return (NULL);
}
