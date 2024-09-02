#include "../includes/pipex_bonus.h"


/*int	first_check_path(t_pipex *pipex)
{
	pipex->path_find = ft_strdup(pipex->cmd);
	if (pipex->path_find == NULL)
		return (1);
	if (access(pipex->path_find, F_OK) == 0)
	{
		if (access(pipex->path_find, X_OK) == 0)
			return (free(pipex->path_find), 0);
		else
			return (denied(pipex), free(pipex->path_find), 1);
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
}*/

int	write_pipe(int outfile, char *str)
{
	if (write(outfile, str, ft_strlen(str)) == -1)
		return (-1);
	return (0);
}

void	write_str(char *str, int fd)
{
	write(fd, str, ft_strlen(str));
}

void	write_str2(char *str, char *str2, int fd)
{
	write(fd, str, ft_strlen(str));
	write(fd, str2, ft_strlen(str2));
}

void	error_return(t_pipex_b *pipex, char *av)
{
	if (pipex->out == 1)
		write_str("Operation not permitted\n", STDERR_FILENO);
	if (pipex->out == 2)
		write_str2(av, " :No such file or directory\n", STDERR_FILENO);
	if (pipex->out == 5)
		write_str("Input/output error\n", STDERR_FILENO);
	if (pipex->out == 12)
		write_str("Out memory\n", STDERR_FILENO);
	if (pipex->out == 13)
		write_str2(av, " :Permission denied\n", STDERR_FILENO);
	if (pipex->out == 127)
		write_str2(av, " :command not found\n", STDERR_FILENO);
}