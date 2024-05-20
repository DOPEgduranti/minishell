/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gduranti <gduranti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by gduranti          #+#    #+#             */
/*   Updated: 2024/05/02 15:50:35 by gduranti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_bool	ft_isthesameas(char *s1, char *s2)
{
	if (ft_strcmp(s1, s2) == 0)
		return (TRUE);
	return (FALSE);
}

int	do_builtin(t_pipex *comm, t_data *data, t_pipex **origin, pid_t **pid)
{
	int	ret;

	ret = 0;
	if (ft_strcmp(comm->cmd[0], "echo") == 0)
		ret = ft_echo(comm->cmd);
	else if (ft_strcmp(comm->cmd[0], "pwd") == 0)
		ft_pwd();
	else if (ft_strcmp(comm->cmd[0], "export") == 0)
		ret = ft_export(&data->envp, comm->cmd);
	else if (ft_strcmp(comm->cmd[0], "unset") == 0)
		ret = ft_unset(comm->cmd, &data->envp);
	else if (ft_strcmp(comm->cmd[0], "env") == 0)
		ret = ft_env(data->envp, &comm->cmd[1]);
	else if (ft_strcmp(comm->cmd[0], "exit") == 0)
		ret = ft_exit(comm->cmd, data, origin, pid);
	else if (ft_strcmp(comm->cmd[0], "cd") == 0)
		ret = ft_cd(comm->cmd, data);
	non_pipe_close(data, comm);
	if (data->in_pipe == TRUE && data->cmd_nbr <= data->pipe_nbr)
		close(data->fd[data->cmd_nbr][1]);
	return (ret);
}

void	non_pipe_close(t_data *data, t_pipex *comm)
{
	if (data->in_pipe == FALSE)
	{
		if (comm->fd_in >= 0 && comm->fd_in != STDIN_FILENO)
			close(comm->fd_in);
		if (comm->fd_out >= 0 && comm->fd_out != STDOUT_FILENO)
			close(comm->fd_out);
	}
}

void	io_redir(t_pipex *comm, t_data *data)
{
	if (comm->fd_in != STDIN_FILENO && comm->fd_in >= 0)
	{
		if (dup2(comm->fd_in, STDIN_FILENO) == -1)
			ft_error("child_stdin", DUP, 13, data);
	}
	if (comm->fd_out != STDOUT_FILENO && comm->fd_out >= 0)
	{
		if (dup2(comm->fd_out, STDOUT_FILENO) == -1)
			ft_error("child", DUP, 13, data);
	}
}
