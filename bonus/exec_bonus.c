#include "../includes/pipex_bonus.h"

void	execout(t_pipex *pipex, char *cmd, char **env)
{
	char	**tmp_flag;

	tmp_flag = ft_split(cmd, ' ');
	pipex->path = get_path(pipex->tmp_flag, env);
	if (execve(path, s_cmd, env) == -1)
	{
		ft_free_tab(s_cmd);
		exit(0);
	}
}