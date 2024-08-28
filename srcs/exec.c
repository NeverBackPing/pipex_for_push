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

int	exec_cmd(t_pipex *pipex, char *av, char **envp)
{
	int		i;
	int		j;
	int		len;
	char	**tmp_flag;

	i = 0;
	j = 1;
	tmp_flag = ft_split(av, ' ');
	if (tmp_flag == NULL)
		return (1);
	len = count_arg(tmp_flag);
	pipex->flag = (char **)malloc((len + 1) * sizeof(char *));
	if (pipex->flag == NULL)
		return (clean_split(tmp_flag), 1);
	pipex->flag[i++] = ft_strdup(pipex->cmd);
	while (i < len && tmp_flag[j] != NULL)
	{
		pipex->flag[i++] = ft_strdup(tmp_flag[j++]);
		if (pipex->flag[i - 1] == NULL)
			return (clean_split(tmp_flag), clean_split(pipex->flag), 1);
	}
	pipex->flag[i] = NULL;
	if (execve(pipex->path_find, pipex->flag, envp) == -1)
		return (clean_split(pipex->flag), clean_split(tmp_flag), 1);
	return (0);
}
