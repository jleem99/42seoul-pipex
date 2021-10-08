/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleem <jleem@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 19:49:42 by jleem             #+#    #+#             */
/*   Updated: 2021/10/09 02:52:33 by jleem            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_EXEC_H
# define FT_EXEC_H

char	*ft_getenv(const char *name);
char	**get_paths();
char	*join_path(char const *s1, char const *s2);
char	*find_file_path(char const *file, int access_mode);
int		ft_execvp(const char *file, char *const argv[]);

#endif
