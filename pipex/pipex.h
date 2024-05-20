/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gduranti <gduranti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by gduranti          #+#    #+#             */
/*   Updated: 2024/05/02 15:49:20 by gduranti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../built_in/built_in.h"

char	*path_execve(char *command, char **envp, t_data *data);
void	child(t_pipex *comm, t_data *data, t_pipex **origin, pid_t **pid);
void	io_redir(t_pipex *comm, t_data *data);
int		do_builtin(t_pipex *comm, t_data *data, t_pipex **origin, pid_t **pid);

void	non_pipe_close(t_data *data, t_pipex *comm);

/**
 * @brief This function will execute 2 commands between a SINGLE pipe
 * @example pipex(ft_split(commands, '|'), fd, , envp);
 * @param pipex The structure that contains the command to be executed
 * @param data The data structure that contains the environment variables
 * @return 0 if the commands are executed correctly;
 * -1 if an error occurred
 */
int		pipex(t_pipex *pipex, t_data *data);

#endif
