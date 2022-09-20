/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouay <adouay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 19:06:22 by adouay            #+#    #+#             */
/*   Updated: 2022/09/20 20:52:29 by adouay           ###   ########.fr       */
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
			free (paths);
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
	if (access(cmd_option[0], F_OK | R_OK) == 0)
		execve(cmd_option[0], cmd_option, envp);
	search_cmd_path(cmd_option, envp);
	free_double_array(cmd_option);
	exit(cmd_error(av));
}

void	create_child(t_pipex *pipex, int ac, char *av, char **envp)
{
	int		pid;
	int		fd[2];

	if (pipe(fd) == -1)
		exit (msg_error("pipe error"));
	pid = fork();
	if (pid == 0)
	{
		if (pipex->index == (ac - 1))
			make_dup(pipex->outfile_fd, 1);
		else
			make_dup(fd[1], STDOUT_FILENO);	
		close_pipe(fd);
		get_execve(av, envp);
	}
	if (pipex->index != (ac - 1))
		make_dup(fd[0], 0);
	close_pipe(fd);
}

// si infile pas existant pas faire premier commande mais le reste 
// cmd il y a un / alors acces si faux cmd_error
// si pas de / dans cmd alors search cmd path si pas trouver avec envp alors regarder dans le dossier courant si pas trouver cmd_error