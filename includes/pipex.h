/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjossain <sjossain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 15:30:03 by sjossain          #+#    #+#             */
/*   Updated: 2024/04/16 14:47:56 by sjossain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

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
# define PIPE_ERR "Pipe error"
//Struc
typedef struct s_pipex
{
	int			check;
	int			check_aout;
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
//CMD
int		clean_path(t_pipex *pipex, char *av);
int		check_path(t_pipex *pipex, char *av, char **envp);
//CMD utile
void	clean_split(char **array);
void	error_path(t_pipex *pipex);
void	denied(t_pipex *pipex);
void	ouf_memory(t_pipex *pipex);
void	print_error(t_pipex *pipex);
//CMD utile 2
int		access_exe(char *str, t_pipex *pipex);
int		nb_wave(t_pipex *pipex);
void	path_clean(t_pipex *pipex, char *tmp_dir);
int		path_envp(char **envp, t_pipex *pipex);
//Error system
void	str_error(t_pipex *pipex, char *str);
void	exit_error(t_pipex *pipex, char **av);
void	exit_error2(t_pipex *pipex, char **av);
void	system_err(t_pipex *pipex, const char *str);
//Exec
int		exec_cmd(t_pipex *pipex, char *av, char **envp);
int		exec_alloc(t_pipex *pipex, char **tmp_flag);
//Exit
void	exit_out(t_pipex *pipex);
//Fd
void	close_file(t_pipex *pipex);
void	file_descriptor(t_pipex *pipex, char **av);
//Fd error
void	error_file_denied(char *filename, t_pipex *pipex);
void	error_file(char *filename);
void	error_close(char *filename);
//Fd utile
void	close_check(t_pipex  *pipex, char *filename);
int		close_fd(t_pipex *pipex);
size_t	count_arg(char **str);
char	*find_file(char *str);
void	free_file(t_pipex *pipex);
//Fork
int		child_fork(t_pipex *pipex, char **av, char **envp);
int		child2_fork(t_pipex *pipex, char **av, char **envp);
//Main
int		fork_main(t_pipex *pipex, char **av, char **envp);
//Pipe utile
int		find_cmd(t_pipex *pipex);
void	perror_return(t_pipex *pipex, char *av);
int		write_pipe(int outfile, char *str);
void	write_str(char *str, int fd);
void	write_str2(char *str, char *str2, int fd);
#endif