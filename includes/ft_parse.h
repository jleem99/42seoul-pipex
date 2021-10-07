/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleem <jleem@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 00:31:50 by jleem             #+#    #+#             */
/*   Updated: 2021/10/08 07:30:21 by jleem            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PARSE_H
# define FT_PARSE_H

typedef struct	s_parsed_arg
{
	char const	*infile;
	char const	*outfile;
	char *const	*commands;
	int			n_commands;
	int			is_heredoc;
	char const	*heredoc_limiter;
}				t_parsed_arg;

t_parsed_arg	parse_arg(int argc, char const *argv[]);

#endif
