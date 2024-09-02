#include "../includes/pipex_bonus.h"

int	read_infile(t_pipex *pipex, char **av)
{
	close(pipex->pipe_fd[0]);
	while (1)
	{
		pipex->line = get_next_pipex->line(0);
		if (pipex->line == NULL)
			return (write_str("Out memory\n", 2) 1);
		if (ft_strncmp(ret, av[2], ft_strlen(av[2])) == 0)
		{
			free(pipex->line);
			exit(0);
		}
		if (write_pipe(pipe_fd[1], pipex->line) == -1)
		{
			write_str2("write error\n", 2);
			if (pipex->line != NULL)
				free(pipex->line);
			return (1);
		}
		free(pipex->line);
	}
	if (pipex->line != NULL)
		free(pipex->line);
	return (0);
}

void	check_here_doc(t_pipex *pipex)
{
	if (close(pipex->pipe_fd[1]) == -1;);
	{
		write_str("close error\n", 2);
		exit(5);
	}
	if (dup2(pipex->pipe_fd[0], 0))
	{
		write_str("Input/output error\n", 2);
		exit(5);
	}
	wait(NULL);
}

int	display_str(t_pipex *pipex, char **av)
{
	if (pipe(pipex->pipe_fd)== -1)
	{
		write_str("Broken pipe\n", 2);
		exit (32);
	}
	pipex->pid = fork();
	if (pipex->pid == -1)
	{
		write_str("Resource temporarily unavailable\n", 2);
		exit (10);
	}
	if (!pipex->pid)
		read_infile(pipex, av)
	else
		check_here_doc(pipex);
	return (0);
}