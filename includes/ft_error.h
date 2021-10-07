/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleem <jleem@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 23:41:37 by jleem             #+#    #+#             */
/*   Updated: 2021/10/07 19:12:38 by jleem            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_ERROR_H
# define FT_ERROR_H

# define FT_EFORK	"fork"
# define FT_EEXEC	"exec"
# define FT_EPIPE	"pipe"
# define FT_ENOMEM	"malloc"

void	handle_invalid_arg(void);
void	handle_error(char const *err);

#endif
