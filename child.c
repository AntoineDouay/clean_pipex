/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouay <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 19:06:22 by adouay            #+#    #+#             */
/*   Updated: 2022/08/10 18:28:58 by adouay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	make_dup(int oldfd, int newfd)
{
	if (dup2(oldfd, newfd) == -1)
		printf ("hihihi\n");  // ERROR EXIT;
}

void	close_pipe(int fd[2])
{
	close(fd[0]);
	close(fd[1]);
}

void	get_execve(char *av, char **envp)
{
	char	*tmp;
	char	*cmd;
	char	**cmd_option;
	char	**paths;
	int	i;

	i = 0;

	cmd_option = ft_split(av, ' ');
	paths = ft_split(path_finding(envp) + 5, ':' );
	if(access(cmd_option[0], F_OK | R_OK) == 0)
		execve(cmd_option[0], cmd_option, envp);
	while (paths[i] != 0)
	{
		tmp = ft_strjoin(paths[i], "/");
		cmd = ft_strjoin(tmp, cmd_option[0]);
		free(tmp);
		if(access(cmd, F_OK | R_OK) == 0)
			execve(cmd, cmd_option, envp);
		free(cmd);
		i++;
	}
}

void	create_child(t_pipex *pipex, char *av, char **envp)
{
	int 	pid;
	int		fd[2];

	if (pipe(fd) == -1)
		printf("error pipe"); // ERROR;
	pid = fork();
	if (pid == 0)
	{
		if (pipex->infile_fd == -1)
			printf("INFILE -1\n"); // ERROR;
		make_dup(fd[1], STDOUT_FILENO);
		close_pipe(fd);
		get_execve(av, envp);		
	}
	make_dup(fd[0], 0);
	close_pipe(fd);
	waitpid(-1, NULL, WNOHANG);
}






