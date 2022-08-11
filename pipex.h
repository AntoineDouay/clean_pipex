/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouay <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 11:34:30 by adouay            #+#    #+#             */
/*   Updated: 2022/08/11 19:17:47 by adouay           ###   ########.fr       */
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
	int		pid;
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

char	*path_finding(char **envp);
void	make_dup(int oldfd, int newfd);
void	create_child(char *av, char **envp);
void	close_pipe(int fd[2]);
void	free_double_array(char **tab);
void	here_doc(char **av);
void	get_execve(char *av, char **envp);
int		file_error(char *file);
int		arg_error(void);
int		cmd_error(char *cmd);
int		msg_error(char *msg);

#endif
