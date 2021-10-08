/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleem <jleem@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 19:52:08 by jleem             #+#    #+#             */
/*   Updated: 2021/10/08 09:17:17 by jleem            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_exec.h"
#include "libft_bonus.h"
#include <stdlib.h>
#include <paths.h>

extern char **environ;

char	*ft_getenv(const char *name)
{
	char *const	search_string = ft_strjoin(name, "=");
	int const	search_len = ft_strlen(search_string);
	int			i;

	i = 0;
	while (environ[i])
	{
		if (ft_strncmp(environ[i], search_string, search_len) == 0)
		{
			free(search_string);
			return (environ[i] + search_len);
		}
		i++;
	}
	return NULL;
}

char	**get_paths()
{
	char	*path_env;

	path_env = ft_getenv("PATH");
	if (path_env == NULL)
		path_env = _PATH_DEFPATH;
	return (ft_split(path_env, ':'));
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

char	*find_file_path(char const *file, int access_mode)
{
	char **const	paths = get_paths();
	char			*file_path;
	int				i;

	i = 0;
	while (paths[i])
	{
		file_path = join_path(paths[i], file);
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
