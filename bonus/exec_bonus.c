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

void	execout(t_pipex_b *pipex, char *cmd, char **envp)
{
	char	**tmp_flag;

	tmp_flag = ft_split(cmd, ' ');
	//pipex->path = get_path(pipex->tmp_flag, env);
	if (execve(pipex->path, tmp_flag, envp) == -1)
	{
		clean_split(tmp_flag);
		exit(0);
	}
}