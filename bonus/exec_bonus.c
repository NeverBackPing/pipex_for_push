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

int	envp_path(char **envp, t_pipex_b *pipex)
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

int	access_path(t_pipex_b *pipex, char *cmd)
{
	if (access(pipex->path, F_OK) == 0)
	{
		if (access(pipex->path, X_OK) == 0)
			return (1);
		else
			return (write_str2(cmd, ": permission denied\n", 2), 1);
	}

	return (0);
}

int	find_path(t_pipex_b *pipex, char *cmd, char **envp)
{
	char	*tmp_dir;

	if ((ft_strchr(cmd, '~') != NULL) && ft_strchr(cmd, '/'))
		return (write_str2(cmd, ": No such file or directory\n", 2), 1);
	envp_path(envp, pipex);
	pipex->directory = ft_strtok(pipex->path_head, ':');
	while (pipex->directory != NULL)
	{
		tmp_dir = ft_strjoin(pipex->directory, "/");
		if (tmp_dir == NULL)
			return (free(pipex->directory), free(pipex->path), free(tmp_dir), 1);
		pipex->path = ft_strjoin(tmp_dir, cmd);
		if (pipex->path == NULL)
			return (free(pipex->directory), free(pipex->path), free(tmp_dir), 1);
		if (access_path(pipex, cmd))
			return (free(pipex->directory), free(tmp_dir), 0);
		pipex->directory = ft_strtok(NULL, ':');
		free(pipex->path);
		free(tmp_dir);
	}
	return (write_str2(cmd,": Command not found\n", 2), 1);
}

void	execout(t_pipex_b *pipex, char *cmd, char **envp)
{
	char	**tmp_flag;

	tmp_flag = ft_split(cmd, ' ');
	find_path(pipex, tmp_flag[0], envp);
	if (execve(pipex->path, tmp_flag, envp) == -1)
	{
		clean_split(tmp_flag);
		close(pipex->fd[1]);
		exit(0);
	}
}
