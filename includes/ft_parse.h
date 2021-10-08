/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleem <jleem@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 00:31:50 by jleem             #+#    #+#             */
/*   Updated: 2021/10/09 02:51:43 by jleem            ###   ########.fr       */
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

/* ft_parse.c */
t_parsed_arg	parse_arg(int argc, char const *argv[]);

/* ft_parse_command.c */
char			**parse_command(char const *command);

#endif
