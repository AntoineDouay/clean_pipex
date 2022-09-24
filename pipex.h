/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouay <adouay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 11:34:30 by adouay            #+#    #+#             */
/*   Updated: 2022/09/24 23:21:52 by adouay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H

# define PIPEX_H

# include "libft/libft.h"
# include "get_next_line_bonus.h"
# include <unistd.h>
# include <sys/wait.h>

# include <stdio.h>

typedef struct s_pipex{
	int		fd[3];
	int		here_doc;
	int		index;
	int		infile_fd;
	int		outfile_fd;	
}	t_pipex;

typedef enum e_type{
	APPEND,
	TRUNC,
	RDONLY,
}	t_type;
/* ---- pipex.c ----*/
void	parse_args(int ac, char **av, t_pipex *pipex);
char	*path_finding(char **envp);
int		open_file(char *file, t_type type);
void	heredoc_or_not(t_pipex *pipex, int ac, char **av);
/* ---- child.c ----*/
void	create_child(t_pipex *pipex, int ac, char **av, char **envp);
void	get_execve(char *av, char **envp);
/* ---- error.c ----*/
int		file_error(char *file);
int		arg_error(void);
int		cmd_error(char *cmd);
int		msg_error(char *msg);
/* ---- here_doc.c ---- */
void	here_doc(t_pipex *pipex, char *av);
/* ---- utils.c ---- */
void	make_dup(int oldfd, int newfd);
void	close_pipe(int fd[3]);
void	free_double_array(char **tab);

#endif
