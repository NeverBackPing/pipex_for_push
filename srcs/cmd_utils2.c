/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjossain <sjossain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 16:14:49 by sjossain          #+#    #+#             */
/*   Updated: 2024/09/11 16:14:49 by sjossain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	denied_exe(t_pipex *pipex)
{
	pipex->exit_str = ft_strdup(DENIED);
}

int	access_exe(char *str, t_pipex *pipex)
{
	pipex->path_find = NULL;
	if (access(str, F_OK) == 0 && ((str[0] == '.') && (str[1] == '/')))
	{
		pipex->path_find = ft_strdup(str);
		if (pipex->path_find == NULL)
			return (1);
		if (access(pipex->path_find, X_OK) == 0)
			return (0);
		else
			return (denied_exe(pipex), 1);
	}
	return (0);
}

int	path_envp(char **envp, t_pipex *pipex)
{
	int	i;

	i = 0;
	pipex->path_head = NULL;
	while (envp[i] != NULL)
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			pipex->path_head = envp[i] + 5;
			break ;
		}
		i++;
	}
	if (pipex->path_head == NULL)
		return (1);
	return (0);
}

void	path_clean(t_pipex *pipex, char *tmp_dir)
{
	if (pipex->path_find != NULL)
		free(pipex->path_find);
	if (tmp_dir != NULL)
		free(tmp_dir);
}

int	nb_wave(t_pipex *pipex)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (pipex->cmd[i] != '\0')
	{
		if (pipex->cmd[i] == '~')
			len++;
		i++;
	}
	return (len);
}
