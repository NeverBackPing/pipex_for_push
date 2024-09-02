#include "../includes/pipex_bonus.h"

void	cmd(t_pipex *pipex, char *av, char **envp)
{
	if (pipe(pipex->pipe_fd) == -1)
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
	{
		close(pipex->pipe_fd[0]);
		dup2(pipex->pipe_fd[1], 1);
		execout(pipex, av, env);
	}
	else
	{
		close(pipex->pipe_fd[1]);
		dup2(pipex->pipe_fd[0], 0);
	}
}
