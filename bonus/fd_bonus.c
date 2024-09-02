#include "../includes/pipex_bonus.h"

int	fd(t_pipex *pipex, char *finename, int check_fd)
{
	if (check_fd == 0)
		pipiex->code = open(filename, O_RDONLY, 0777);
	if (check_fd == 1)
		pipiex->code = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (check_fd == 2)
		pipiex->code = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0777);
	if (pipiex->code == -1)
		exit(0);
	return (pipiex->code);
}
