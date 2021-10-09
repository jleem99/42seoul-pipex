/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleem <jleem@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 08:13:56 by jleem             #+#    #+#             */
/*   Updated: 2021/10/09 12:23:50 by jleem            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_HEREDOC_H
# define FT_HEREDOC_H

# ifdef DEBUG_PROCESSES
#  define DEBUG_PROCESSES	1
# else
#  define DEBUG_PROCESSES	0
# endif

int		get_heredoc_writer(char const *limiter);

#endif
