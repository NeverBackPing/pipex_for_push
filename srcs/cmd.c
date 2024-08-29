/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjossain <sjossain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 12:53:13 by sjossain          #+#    #+#             */
/*   Updated: 2024/08/07 12:53:13 by sjossain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	clean_path(t_pipex *pipex)
{
	char	**cmd_tmp;
	char	*tmp;

	if (((pipex->cmd[0] != '~') || pipex->cmd[1] == '/') || nb_wave(pipex) > 1)
		return (1);
	cmd_tmp = ft_split(pipex->cmd, '~');
	if (cmd_tmp == NULL)
		return (1);
	free(pipex->cmd);
	tmp = ft_strdup(cmd_tmp[0]);
	if (tmp == NULL)
		return (clean_split(cmd_tmp), 1);
	pipex->cmd = ft_strjoin("/", tmp);
	if (pipex->cmd == NULL)
		return (clean_split(cmd_tmp), free(tmp), 1);
	if (access(pipex->cmd, F_OK) == 0)
	{
		clean_split(cmd_tmp);
		if (access(pipex->cmd, X_OK) == 0)
			return (free(tmp), 0);
		else
			return (free(tmp), denied(pipex), 1);
	}
	return (clean_split(cmd_tmp), free(tmp), 0);
}

int	access_path(t_pipex *pipex)
{
	if (access(pipex->path_find, F_OK) == 0)
	{
		if (access(pipex->path_find, X_OK) == 0)
			return (1);
		else
			return (denied(pipex), 1);
	}
	return (0);
}

int	first_check_path(t_pipex *pipex)
{
	pipex->path_find = ft_strdup(pipex->cmd);
	if (pipex->path_find == NULL)
		return (1);
	if (access(pipex->path_find, F_OK) == 0)
	{
		if (access(pipex->path_find, X_OK) == 0)
			return (0);
		else
			return (denied(pipex), 1);
	}
	return (free(pipex->path_find), 0);
}

int	find_path(t_pipex *pipex)
{
	char	*tmp_dir;

	if ((ft_strchr(pipex->cmd, '~') != NULL) && (clean_path(pipex)))
		return (print_error(pipex), 1);
	if (first_check_path(pipex))
		return (1);
	pipex->directory = ft_strtok(pipex->path_head, ':');
	while (pipex->directory != NULL)
	{
		tmp_dir = ft_strjoin(pipex->directory, "/");
		if (tmp_dir == NULL)
			return (free(pipex->directory), path_clean(pipex, tmp_dir), 1);
		pipex->path_find = ft_strjoin(tmp_dir, pipex->cmd);
		if (pipex->path_find == NULL)
			return (free(pipex->directory), path_clean(pipex, tmp_dir), 1);
		if (access_path(pipex))
			return (free(pipex->directory), free(tmp_dir), 0);
		pipex->directory = ft_strtok(NULL, ':');
		path_clean(pipex, tmp_dir);
	}
	return (print_error(pipex), 1);
}

int	check_path(t_pipex *pipex, char *av, char **envp)
{
	if (av == NULL || envp == NULL || *av == '\0')
		return (1);
	if (pipex->path_find != NULL)
		return (0);
	pipex->tmp = ft_split(av, ' ');
	if (pipex->tmp == NULL)
		return (clean_split(pipex->tmp), ouf_memory(pipex), 1);
	pipex->cmd = ft_strdup(pipex->tmp[0]);
	if (pipex->cmd == NULL)
		return (clean_split(pipex->tmp), ouf_memory(pipex), 1);
	//attention v v v v v v v v v v v v v v v v
	if (((pipex->cmd[0] == '.') && (pipex->cmd[1] == '/'))
			&& access(pipex->cmd, F_OK) != 0)
		return (print_error(pipex), clean_split(pipex->tmp), 1);
	if (path_envp(envp, pipex))
		return (error_path(pipex), clean_split(pipex->tmp), 1);
	if (find_path(pipex))
		return (free(pipex->cmd), clean_split(pipex->tmp), 1);
	return (clean_split(pipex->tmp), 0);
}
