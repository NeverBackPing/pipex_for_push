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

int	clean_path(t_pipex *pipex, char *av)
{
	char	**cmd;
	char	*tmp;

	if (ft_strchr(pipex->tmp[0], '~') == NULL)
		return (0);
	if (nb_wave(pipex) > 1)
		return (print_error(pipex), clean_split(pipex->tmp), 1);
	clean_split(pipex->tmp);
	pipex->tmp = ft_split(av, ' ');
	if (pipex->tmp == NULL)
		return (clean_split(pipex->tmp), ouf_memory(pipex), 1);
	if (pipex->tmp[0][0] == '~' && pipex->tmp[0][1] == '/')
		return (1);
	cmd = ft_split(pipex->tmp[0], '~');
	if (cmd == NULL)
		return (clean_split(pipex->tmp), ouf_memory(pipex), 1);
	clean_split(pipex->tmp);
	tmp = ft_strjoin("/", cmd[0]);
	if (tmp == NULL)
		return (clean_split(cmd), ouf_memory(pipex), 1);
	pipex->tmp = ft_split(tmp, ' ');
	free(tmp);
	if (pipex->tmp == NULL)
		return (clean_split(pipex->tmp), clean_split(cmd), ouf_memory(pipex), 1);
	return (clean_split(cmd), 0);
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
	pipex->check_aout = 0;
	pipex->path_find = ft_strdup(pipex->cmd);
	if (pipex->path_find == NULL)
		return (1);
	if (access(pipex->path_find, F_OK) == 0)
	{
		if (access(pipex->path_find, X_OK) == 0)
		{
			pipex->check_aout = 2;
			return (free(pipex->path_find), 0);
		}
		else if (access(pipex->path_find, X_OK) != 0)
			return (denied(pipex), free(pipex->path_find), 1);
	}
	return (free(pipex->path_find), 0);
}

int	find_path(t_pipex *pipex)
{
	char	*tmp_dir;

	if (first_check_path(pipex))
		return (1);
	else if (pipex->check_aout == 2)
		return (0);
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
	if (clean_path(pipex, av))
			return (1);
	if ((pipex->tmp[0][0] == '/' && access(pipex->tmp[0], F_OK) == 0))
		pipex->cmd = ft_strdup((pipex->tmp[0] + find_cmd(pipex)));
	else
		pipex->cmd = ft_strdup(pipex->tmp[0]);
	if (pipex->cmd == NULL)
		return (clean_split(pipex->tmp), ouf_memory(pipex), 1);
	if (((pipex->cmd[0] == '.') && (pipex->cmd[1] == '/'))
			&& access(pipex->cmd, F_OK) != 0)
	{
		pipex->check_aout = 4;
		return (/*print_error(pipex),*/ clean_split(pipex->tmp), free(pipex->cmd), 1);
	}
	if (path_envp(envp, pipex))
		return (error_path(pipex), clean_split(pipex->tmp), 1);
	if (find_path(pipex))
		return (free(pipex->cmd), clean_split(pipex->tmp), 1);
	return (clean_split(pipex->tmp), 0);
}
