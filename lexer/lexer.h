/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gduranti <gduranti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by gduranti          #+#    #+#             */
/*   Updated: 2024/05/02 15:47:06 by gduranti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "../parser/parser.h"
# include "../bonus/bonus.h"
# pragma once

t_bool	open_quote_check(char *line, char *new_quote);
void	uselss_quotes(char **buff, char *quote);
char	*read_quotes(char *c);

void	quote_check(char **line);
t_bool	lexer(char **line, t_data *data);
t_bool	lexer_error(char *error, t_data *data, char c);
int		pipe_count(char *line, t_data *data);
t_bool	pipe_check(char *line);
t_bool	check_middle(char *line, t_quote *squote);
t_bool	check_start_end(char *line, t_quote *squote);

#endif
