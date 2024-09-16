/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjossain <sjossain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 02:03:39 by sjossain          #+#    #+#             */
/*   Updated: 2024/08/15 02:03:59 by sjossain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	exec_aout(t_pipex *pipex, char **envp)
{
	pipex->flag = ft_split(pipex->cmd, ' ');
	if (pipex->flag == NULL)
		return (1);
	if (pipex->cmd[0] == '.' && pipex->cmd[1] == '/')
	{
		if (execve(pipex->cmd, pipex->flag, envp) == -1)
		{
			str_error(pipex, pipex->cmd);
			clean_split(pipex->flag);
			free(pipex->path_find);
			free(pipex->cmd);
			return (1);
		}
		else
			return (clean_split(pipex->flag), free(pipex->cmd), 0);
	}
	return (0);
}

int	exec_alloc(t_pipex *pipex, char **tmp_flag)
{
	pipex->flag = (char **)malloc(( count_arg(tmp_flag) + 1) * sizeof(char *));
	if (pipex->flag == NULL)
		return (clean_split(tmp_flag), 1);
	pipex->flag[0] = ft_strdup(pipex->cmd);
	if (pipex->flag == NULL)
		return (clean_split(tmp_flag), 1);
	return (0);
}

int	exec_cmd(t_pipex *pipex, char *av, char **envp)
{
	size_t		i;
	char		**tmp_flag;

	i = 1;
	pipex->out = 0;
	if (pipex->cmd[0] == '.' && pipex->cmd[1] == '/')
	{
		if (exec_aout(pipex, envp) == 0)
			return (0);
		else
			return (1);
	}
	tmp_flag = ft_split(av, ' ');
	if (tmp_flag == NULL || exec_alloc(pipex, tmp_flag))
		return (1);
	while (i < count_arg(tmp_flag) && tmp_flag[i] != NULL)
	{
		pipex->flag[i] = ft_strdup(tmp_flag[i]);
		if (pipex->flag[i - 1] == NULL)
			return (clean_split(tmp_flag), clean_split(pipex->flag), 1);
		i++;
	}
	pipex->flag[i] = NULL;
	if (execve(pipex->path_find, pipex->flag, envp) == -1)
	{
		str_error(pipex, pipex->cmd);
		free(pipex->path_find);
		free(pipex->cmd);
		return (clean_split(pipex->flag), clean_split(tmp_flag), 1);
	}
	return (0);
}
