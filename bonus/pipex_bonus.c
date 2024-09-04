#include "../includes/pipex_bonus.h"

void	manage_io(t_pipex_b *pipex, char **av, int ac)
{
	pipex->fd[0] = fd(pipex, av[1], 0);
	pipex->fd[1] = fd(pipex, av[ac - 1], 1);
	if (dup2(pipex->fd[0], 0) == -1)
	{
		write_str("Input/output error\n", 2);
		exit(5);
	}
}

int	main(int ac, char **av, char **envp)
{
	size_t	i;
	t_pipex_b	pipex;
	const int save_fd = dup(STDOUT_FILENO);

	i = 2;
	if (ac < 5)
		return (ft_printf("./pipex infile cmd1 cmd2 oufile\n"), 0);
	else if (ft_strcmp(av[1], "here_doc") == 0)
	{
		if (ac < 6)
		{
			ft_printf("./pipex HERE_DOC LIMITER cmd1 ... cmdn oufile\n");
			exit(0);
		}
		i = 3;
		pipex.fd[1] = fd(&pipex, av[ac - 1], 2);
		display_str(&pipex, av);
	}
	else
		manage_io(&pipex, av, ac);
	while (i < (size_t)ac - 2)
		cmd(&pipex, av[i++], envp);
	dup2(pipex.fd[1], STDOUT_FILENO);
	execout(&pipex, av[i], envp);
	dup2(STDOUT_FILENO, save_fd);
}
