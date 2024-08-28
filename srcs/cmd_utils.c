
#include "../includes/pipex.h"

void	denied(t_pipex *pipex)
{
	pipex->exit_str = ft_strdup(DENIED);
}

void	ouf_memory(t_pipex *pipex)
{
	pipex->exit_str = ft_strdup(OFM);
}

void	error_path(t_pipex *pipex)
{
	pipex->exit_str = ft_strdup(PATH);
	if (pipex->exit_str != NULL)
		ft_printf("%s\n", strerror(2));
	if (pipex->cmd != NULL)
		free(pipex->cmd);
}

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

void	print_error(t_pipex *pipex)
{
	if (ft_strchr(pipex->tmp[0], '/') != NULL)
	{
		pipex->exit_str = ft_strdup(NOSUCH);
	}
	else if (ft_strchr(pipex->tmp[0], '~') != NULL)
	{
		pipex->exit_str = ft_strdup(NOSUCH);
	}
	else
		pipex->exit_str = ft_strdup(CND);

}
