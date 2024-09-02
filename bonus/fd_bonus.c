#include "../includes/pipex_bonus.h"

int	fd(t_pipex_b *pipex, char *filename, int check_fd)
{
	if (check_fd == 0)
		pipex->code = open(filename, O_RDONLY, 0777);
	if (check_fd == 1)
		pipex->code = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (check_fd == 2)
		pipex->code = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0777);
	if (pipex->code == -1)
		exit(0);
	return (pipex->code);
}
