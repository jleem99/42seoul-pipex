/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleem <jleem@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 19:49:42 by jleem             #+#    #+#             */
/*   Updated: 2021/10/05 01:47:47 by jleem            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_EXEC_H
# define FT_EXEC_H

# include <unistd.h>

int
ft_execl(const char *path, const char *arg0, ... /*, (char *)0 */);

int
ft_execle(const char *path, const char *arg0, ... /*, (char *)0, char *const envp[] */);

int
ft_execlp(const char *file, const char *arg0, ... /*, (char *)0 */);

int
ft_execv(const char *path, char *const argv[]);

int
ft_execvp(const char *file, char *const argv[]);

int
ft_execvP(const char *file, const char *search_path, char *const argv[]);

char	**get_paths(char *const envp[]);
char	*join_path(char const *s1, char const *s2);
char	*find_executable_file_path(char const *file);

#endif
