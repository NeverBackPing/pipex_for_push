#include "../includes/pipex_bonus.h"

void	clean_split(char **array)
{
	int	i;

	i = 0;
	if (array == NULL)
		return ;
	if (array)
	{
		while (array[i] != NULL)
			free(array[i++]);
		free(array);
	}
}

/*int	find_path(t_pipex *pipex)
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
}*/

void	execout(t_pipex_b *pipex, char *cmd, char **envp)
{
	char	**tmp_flag;

	tmp_flag = ft_split(cmd, ' ');
	/*if (get_path(pipex->tmp_flag, env));
		return ;*/
	if (execve(pipex->path, tmp_flag, envp) == -1)
	{
		clean_split(tmp_flag);
		exit(0);
	}
}