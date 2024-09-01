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
//Mcro
# define CHILD "No child processes"
# define CND "command not found"
# define DENIED "Permission denied"
# define IO "Input/output error"
# define OFM "Out of memory"
# define NOSUCH "No such file or directory"
# define OPD "Operation not permitted"
# define PATH "PATH error"
//Struc
typedef struct s_pipex
{
	int			check;
	int			save_out;
	int			status;
	int			status2;
	int			fd[2];
	int			pipe_fd[2];
	char		buffer;
	pid_t		child;
	pid_t		child2;
	char		*infile;
	char		*outfile;
	char		*path;
	char		*path_find;
	char		*path_head;
	char		*cmd;
	char		**tmp;
	char		**flag;
	char		*directory;
	int			out;
	char		*exit_str;
}	t_pipex;
//
#endif