/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouay <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 11:34:38 by adouay            #+#    #+#             */
/*   Updated: 2022/08/11 20:02:52 by adouay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	parse_args(int ac, char **av, t_pipex *pipex)
{
	if (ac < 5)
		exit (arg_error());
	if (ft_strncmp(av[1], "here_doc", 8) == 0 && av[1][8] == '\0')
		pipex->here_doc = 1;
	if	(ac < 6 && pipex->here_doc == 1)
		exit (arg_error());
	if (access(av[1], F_OK | R_OK) == -1 && pipex->here_doc == 0)
		exit (file_error(av[1]));  
	return ;
}

int	open_file(char *file, t_type type)
{
	int	fd;

	if (type == TRUNC)
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC | O_CLOEXEC, 0664);
	if (type == APPEND)
		fd = open(file, O_WRONLY | O_CREAT | O_APPEND | O_CLOEXEC, 0664);
	if (type == RDONLY)
		fd = open(file, O_RDONLY | O_CLOEXEC, 0664);
	if (fd == -1)
		exit (msg_error("open error"));
	return (fd);
}

char	*path_finding(char **envp)
{
	int	i;

	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "PATH", 4) != 0)
		i++;
	if (!envp[i])
		return (NULL);
	return (envp[i]);
}

int	main(int ac, char **av, char **envp)
{
	char	*path_line;
	t_pipex	pipex;

	pipex.here_doc = 0;
	parse_args(ac, av, &pipex);
	if (pipex.here_doc == 1)
	{	
		pipex.index = 3;
		here_doc(av);
		pipex.outfile_fd = open_file(av[ac - 1], APPEND);
	}
	else
	{
		pipex.index = 2;
		pipex.infile_fd = open_file(av[1], RDONLY);
		make_dup(pipex.infile_fd, 0);
		pipex.outfile_fd = open_file(av[ac - 1], TRUNC);
	}
	path_line = path_finding(envp);
	if (path_line == NULL)
		exit(msg_error("path not found"));
	while (pipex.index < (ac - 2))
		create_child(av[pipex.index++], envp);
	make_dup(pipex.outfile_fd, 1);
	get_execve(av[ac - 2], envp);
	return (0);
}
