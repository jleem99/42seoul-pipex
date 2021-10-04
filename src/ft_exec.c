/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleem <jleem@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 19:52:04 by jleem             #+#    #+#             */
/*   Updated: 2021/10/05 01:52:48 by jleem            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_exec.h"

extern char **environ;

// v => argument vector (array)
// l => argument location (variadic)
// p => search for path (when file name does not contain slash)
// e => specify env / otherwise use extern environ

// execv
// execv e *
// execv p
// execv P (override path with given argument)

// evecl
// execl e
// execl p

// int
//      execl(const char *path, const char *arg0, ... /*, (char *)0 */);

//      int
//      execle(const char *path, const char *arg0, ...
//          /*, (char *)0, char *const envp[] */);

//      int
//      execlp(const char *file, const char *arg0, ... /*, (char *)0 */);

//      int
//      execv(const char *path, char *const argv[]);

//      int
//      execvp(const char *file, char *const argv[]);

//      int
//      execvP(const char *file, const char *search_path, char *const argv[]);
    // The functions execlp(), execvp(), and execvP() will duplicate the actions of
    //  the shell in searching for an executable file if the specified file name
    //  does not contain a slash ``/'' character.  For execlp() and execvp(), search
    //  path is the path specified in the environment by ``PATH'' variable.  If this
    //  variable is not specified, the default path is set according to the
    //  _PATH_DEFPATH definition in <paths.h>, which is set to ``/usr/bin:/bin''.
    //  For execvP(), the search path is specified as an argument to the function.
    //  In addition, certain errors are treated specially.

int ft_execvp(const char *file, char *const argv[])
{
    char    *file_path;

    file_path = file;
	if (access(file_path, X_OK) != 0)
        file_path = find_executable_file_path(file);
    return (execve(file_path, argv, environ));
}
