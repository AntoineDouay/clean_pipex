/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouay <adouay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 19:06:22 by adouay            #+#    #+#             */
/*   Updated: 2022/09/24 23:20:21 by adouay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	search_cmd_path(char **cmd_option, char **envp)
{
	char	*tmp;
	char	*cmd;
	char	**paths;
	int		i;

	i = 0;
	paths = ft_split(path_finding(envp) + 5, ':' );
	while (paths[i] != 0)
	{
		tmp = ft_strjoin(paths[i], "/");
		cmd = ft_strjoin(tmp, cmd_option[0]);
		free(tmp);
		if (access(cmd, F_OK | R_OK) == 0)
		{	
			free_double_array(paths);
			execve(cmd, cmd_option, envp);
		}
		free(cmd);
		i++;
	}
	free_double_array(paths);
}

void	get_execve(char *av, char **envp)
{
	char	**cmd_option;

	cmd_option = ft_split(av, ' ');
	if (ft_strchr(cmd_option[0], 47) != NULL)
	{
		execve(cmd_option[0], cmd_option, NULL);
		free_double_array(cmd_option);
		exit(cmd_error(av));
	}
	if (envp[0])
		search_cmd_path(cmd_option, envp);
	free_double_array(cmd_option);
	exit(cmd_error(av));
}

void	first_child(t_pipex *pipex)
{
	if (pipex->infile_fd == -1)
		exit (0);
	if (pipex->here_doc == 0)
		make_dup(pipex->infile_fd, 0);
	else if (pipex->here_doc == 1)
		make_dup(pipex->fd[2], 0);
	make_dup(pipex->fd[1], 1);
	close (pipex->fd[0]);
}

void	last_child(t_pipex *pipex)
{	
	make_dup(pipex->fd[2], 0);
	make_dup(pipex->outfile_fd, 1);
	close(pipex->fd[1]);
}

void	create_child(t_pipex *pipex, int ac, char **av, char **envp)
{
	int		pid;

	pipex->fd[2] = pipex->fd[0];
	if (pipe(pipex->fd) == -1)
		exit (msg_error("pipe error"));
	pid = fork();
	if (pid == -1)
		exit (msg_error("fork error"));
	if (pid == 0)
	{
		if (pipex->index == 2)
			first_child(pipex);
		else if (pipex->index == (ac - 2))
			last_child(pipex);
		else
		{
			make_dup(pipex->fd[2], 0);
			make_dup(pipex->fd[1], 1);
			close(pipex->fd[0]);
		}
		get_execve(av[pipex->index], envp);
	}
	close(pipex->fd[1]);
	if (pipex->fd[2] > 0)
		close(pipex->fd[2]);
}

		//	if (pipex->fd[1] > 0)

		//if ((pipex->index == 2 && pipex->infile_fd == -1))
		//	exit(0);
		// if (pipex->index == 2)
		//	first_child(pipex);
		//{
		//	if (pipex->here_doc == 0)
		//		make_dup(pipex->infile_fd, 0);
		//	if (pipex->here_doc == 1)
		//		make_dup(pipex->fd[2], 0);
		//	make_dup(pipex->fd[1], 1);
		//	close(pipex->fd[0]);
		//}
