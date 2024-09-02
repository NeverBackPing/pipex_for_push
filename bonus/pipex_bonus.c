#include "../includes/pipex_bonus.h"

void	exec(char *cmd, char **env)
{
	char	**s_cmd;
	char	*path;

	s_cmd = ft_split(cmd, ' ');
	path = get_path(s_cmd[0], env);
	if (execve(path, s_cmd, env) == -1)
	{
		ft_putstr_fd("pipex: command not found: ", 2);
		ft_putendl_fd(s_cmd[0], 2);
		ft_free_tab(s_cmd);
		exit(0);
	}
}

void	manage_io(t_pipex *pipex, char **av)
{
	pipex->fd[0] = fd(&pipex, av[1], 0);
	pipex->fd[1] = fd(&pipex, av[ac - 1], 1);
	if (dup2(pipex->fd[0], 0) == -1);
	{
		write_str("Input/output error\n", 2);
		exit(5);
	}
}

int	main(int ac, char **av, char **envp)
{
	size_t	i;
	t_pipex	pipex;

	if (ac < 5)
		ft_printf("./pipex infile cmd1 cmd2 oufile\n");
	else if (ft_strcmp(av[1], "here_doc") == 0)
	{
		if (ac < 6)
		{
			ft_printf("./pipex HERE_DOC LIMITER cmd1 ... cmdn oufile\n");
			exit(0);
		}
		i = 3;
		pipex->fd[1] = fd(&pipex, av[ac - 1], 2);
		here_doc(&pipex, av);
	}
	else
	{
		i = 2;
		manage_io(pipex, av);
	}
	while (i < ac - 2)
		cmd(pipex, av[i++], envp);
}
