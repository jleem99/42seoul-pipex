/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleem <jleem@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 19:52:04 by jleem             #+#    #+#             */
/*   Updated: 2021/10/12 09:50:49 by jleem            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_exec.h"
#include "libft_bonus.h"
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <paths.h>

extern char	**environ;

char	*ft_getenv(const char *name)
{
	size_t const	namelen = ft_strlen(name);
	char			*var;
	int				i;

	i = 0;
	while (environ[i])
	{
		var = environ[i];
		if (ft_strncmp(var, name, namelen) == 0 && var[namelen] == '=')
			return (var + namelen + 1);
		i++;
	}
	return (NULL);
}

char	**get_paths(void)
{
	char	*path_env;

	path_env = ft_getenv("PATH");
	if (path_env == NULL)
		path_env = _PATH_DEFPATH;
	return (ft_split(path_env, ':'));
}

char	*join_path(char const *s1, char const *s2)
{
	int const	s1_len = ft_strlen(s1);
	int const	s2_len = ft_strlen(s2);
	char		*joined_path;

	joined_path = malloc(s1_len + s2_len + 2);
	if (!joined_path)
		return (NULL);
	ft_memcpy(joined_path, s1, s1_len);
	joined_path[s1_len] = '/';
	ft_memcpy(joined_path + s1_len + 1, s2, s2_len);
	joined_path[s1_len + s2_len + 1] = '\0';
	return (joined_path);
}

char	*find_file_path(char const *file, int access_mode)
{
	char **const	paths = get_paths();
	char			*file_path;
	int				i;

	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		file_path = join_path(paths[i], file);
		if (!file_path)
		{
			ft_free_split(paths);
			return (NULL);
		}
		if (access(file_path, access_mode) == 0)
		{
			ft_free_split(paths);
			return (file_path);
		}
		free(file_path);
		i++;
	}
	ft_free_split(paths);
	return (NULL);
}

int	ft_execvp(const char *file, char *const argv[])
{
	char const	*file_path;

	if (ft_strchr(file, '/') != NULL)
		file_path = file;
	else
		file_path = find_file_path(file, X_OK);
	if (file_path == NULL)
	{
		if (errno == ENOMEM)
			return (-1);
		else
			file_path = find_file_path(file, F_OK);
	}
	if (file_path == NULL)
	{
		if (errno != ENOMEM)
			errno = ENOENT;
		return (-1);
	}
	return (execve(file_path, argv, environ));
}
