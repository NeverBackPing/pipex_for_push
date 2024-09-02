#include "../includes/pipex_bonus.h"


/*char	*my_getenv(char *name, char **env)
{
	int		i;
	int		j;
	char	*sub;

	i = 0;
	while (env[i])
	{
		j = 0;
		while (env[i][j] && env[i][j] != '=')
			j++;
		sub = ft_substr(env[i], 0, j);
		if (ft_strcmp(sub, name) == 0)
		{
			free(sub);
			return (env[i] + j + 1);
		}
		free(sub);
		i++;
	}
	return (NULL);
}

char	*get_path(char *cmd, char **env)
{
	int		i;
	char	*exec;
	char	**allpath;
	char	*path_part;
	char	**s_cmd;

	i = -1;
	allpath = ft_split(my_getenv("PATH", env), ':');
	s_cmd = ft_split(cmd, ' ');
	while (allpath[++i])
	{
		path_part = ft_strjoin(allpath[i], "/");
		exec = ft_strjoin(path_part, s_cmd[0]);
		free(path_part);
		if (access(exec, F_OK | X_OK) == 0)
		{
			ft_free_tab(s_cmd);
			return (exec);
		}
		free(exec);
	}
	ft_free_tab(allpath);
	ft_free_tab(s_cmd);
	return (cmd);
}*/

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

	i = 2;
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
		pipex.fd[1] = fd(&pipex, av[ac - 1], 2);
		display_str(&pipex, av);
	}
	else
		manage_io(&pipex, av, ac);
	while (i < (size_t)ac - 2)
		cmd(&pipex, av[i++], envp);
	dup2(pipex->fd[1], STDOUT_FILENO);
	execout(&pipex, cmd, envp);
}
