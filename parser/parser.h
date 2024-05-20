/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gduranti <gduranti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 15:29:56 by gduranti          #+#    #+#             */
/*   Updated: 2024/05/02 15:48:40 by gduranti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "../pipex/pipex.h"
# pragma once

//parser
t_type	ft_file_type(char *str, int *offset);
t_bool	get_command(int *off, char *str, t_parser *prs, t_data *data);
t_bool	get_inout(int *off, char *str, t_parser *prs, t_data *data);
int		i_skip_pippe(char *str, int i);
char	*cut_pars_str(char *str, char *node);
t_bool	parser(char *str, t_data *data, int offset, t_parser prs);
char	*ft_reparsing(char *str, int i, t_data *data, t_quote squote);
int		get_cmd_name(char *str, int *offset, t_quote squote);
char	*remove_quotes(char *str, int *offset);
void	ft_cmdquote(char **str, int *offset);

/**
 * @brief expand $
 * @param tmp string to be expanded
 * @return string with $VAR expanded
*/
char	*expand_name(char *str, t_data *data);
char	*expand_dollar(char *str, char *tmp, size_t *i, t_data *data);
char	*expand_dollar2(char *str, char *tmp, size_t *i, t_data *data);

//quotes
// void	quote_start(t_bool *quote, char c, char *quote_type);
// void	quote_waiting(char **tmp, t_bool *quote, char *quote_type, t_type type);
// void	quote_display(char *quote_type);
// t_bool	check_quote(char *tmp, char quote_type, t_type type, int index);

#endif
