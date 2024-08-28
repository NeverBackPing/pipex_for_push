#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <stdlib.h>
# include <errno.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdarg.h>
# include <limits.h>
# include <sys/wait.h>
# include "ft_printf.h"
# include "get_next_line.h"
# include "libft.h"

typedef struct s_pipex
{
	int			status;
	int			status2;
	int			fd[2];
	int			pipe_fd[2];
	char		buffer;
	pid_t		*child;
}	t_pipex;
#endif