#include "../includes/pipex.h"

void	error_close(char *filename)
{
	write_str2(filename, ": close error\n", 2);
}

void	error_file(char *filename)
{
	write_str2(filename, ": No such file or directory\n", 2);
}

void	error_file_denied(char *filename, t_pipex *pipex)
{
	if (ft_strcmp(filename, pipex->outfile) == 0)
	{
		if (access(pipex->outfile, F_OK) == 0)
		{
			if (access(pipex->outfile, W_OK) != 0)
				write_str2(filename, " : Permission denied\n", 2);
		}
		else
		{
			pipex->exit_str = ft_strdup(OPD);
			write_str2(filename, " : No such file or directory\n", 2);
		}
	}
	else
		write_str2(filename, " : Permission denied\n", 2);
	return ;
}
