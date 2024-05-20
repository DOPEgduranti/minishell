/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gduranti <gduranti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by gduranti          #+#    #+#             */
/*   Updated: 2024/05/02 15:46:27 by gduranti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in.h"

int	ft_errors_cd(char **mtx)
{
	char	*tmp;

	if (ft_matrix_len(mtx) > 2)
	{
		ft_putstr_fd("cd: too many arguments\n", 2);
		return (1);
	}
	tmp = getcwd(NULL, 0);
	if (tmp == NULL)
	{
		perror("cd");
		return (1);
	}
	free(tmp);
	return (0);
}

t_bool	ft_change_env(char **str, char *oldpwd, t_data *data)
{
	char	*mtx[3];
	int		i;

	mtx[0] = ft_strdup("export");
	mtx[1] = ft_strjoin("PWD=", *str);
	mtx[2] = NULL;
	ft_export(&data->envp, mtx);
	free(mtx[0]);
	free(mtx[1]);
	mtx[0] = ft_strdup("export");
	mtx[1] = ft_strdup(oldpwd);
	mtx[2] = NULL;
	ft_export(&data->envp, mtx);
	free(mtx[0]);
	free(mtx[1]);
	free(oldpwd);
	free(*str);
	i = find_in_env(data->envp, "PWD");
	free(data->pwd);
	data->pwd = ft_strdup(data->envp[i] + 4);
	return (TRUE);
}
