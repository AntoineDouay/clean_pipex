/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouay <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 19:06:22 by adouay            #+#    #+#             */
/*   Updated: 2022/08/11 19:56:08 by adouay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	make_dup(int oldfd, int newfd)
{
	if (dup2(oldfd, newfd) == -1)
		exit (msg_error("dup2 error"));
}

void	close_pipe(int fd[2])
{
	close(fd[0]);
	close(fd[1]);
}

void	free_double_array(char **tab)
{
	int	i;

	i = 0;
	while (tab[i] != 0)
	{
		free (tab[i]);
		i++;
	}
	free (tab);
	return ;
}

void	get_execve(char *av, char **envp)
{
	char	*tmp;
	char	*cmd;
	char	**cmd_option;
	char	**paths;
	int		i;

	i = 0;
	cmd_option = ft_split(av, ' ');
	if (access(cmd_option[0], F_OK | R_OK) == 0)
		execve(cmd_option[0], cmd_option, envp);
	paths = ft_split(path_finding(envp) + 5, ':' );
	while (paths[i] != 0)
	{
		tmp = ft_strjoin(paths[i], "/");
		cmd = ft_strjoin(tmp, cmd_option[0]);
		free(tmp);
		if (access(cmd, F_OK | R_OK) == 0)
		{	
			free (paths);
			execve(cmd, cmd_option, envp);
		}
		free(cmd);
		i++;
	}
	free_double_array(cmd_option);
	free_double_array(paths);
	exit(cmd_error(av));
}

void	create_child(char *av, char **envp)
{
	int		pid;
	int		fd[2];

	if (pipe(fd) == -1)
		exit (msg_error("pipe error"));
	pid = fork();
	if (pid == 0)
	{
		make_dup(fd[1], STDOUT_FILENO);
		close_pipe(fd);
		get_execve(av, envp);
	}
	make_dup(fd[0], 0);
	close_pipe(fd);
	waitpid(-1, NULL, WNOHANG);
}
