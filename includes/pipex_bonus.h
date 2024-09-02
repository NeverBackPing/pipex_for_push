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
# define PIPE_ERR "Broken pipe"
//Struc
typedef struct s_pipex
{
	int			check;
	int			save_out;
	int			status;
	int			status2;
	int			fd[2];
	int			pipe_fd[2];
	char		*line;
	pid_t		pid;
	char		*infile;
	char		*outfile;
	char		*path;
	char		*path_find;
	char		*path_head;
	char		*cmd;
	char		**tmp;
	char		**flag;
	char		*directory;
	int			code;
	int			out;
	char		*exit_str;
}	t_pipex;
//Cmd
void	cmd(t_pipex *pipex, char *av, char **envp);
//Exec
void	execout(t_pipex *pipex, char *cmd, char **env);
//Fd
int		fd(t_pipex *pipex, char *finename, int check_fd);
//here doc
void	check_here_doc(t_pipex *pipex);
int		display_str(t_pipex *pipex, char **av);
int		read_infile(t_pipex *pipex, char **av);
//Pipex
void	manage_io(t_pipex *pipex, char **av);
//Return
void	perror_return(t_pipex *pipex, char *av);
int		write_pipe(int outfile, char *str);
void	write_str(char *str, int fd);
void	write_str2(char *str, char *str2, int fd);
#endif