/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouay <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 11:34:38 by adouay            #+#    #+#             */
/*   Updated: 2022/08/10 19:14:25 by adouay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	parse_args(int ac, char **av, t_pipex *pipex)
{
	if (ac < 5)
		return (1);
	if (ft_strncmp(av[1], "here_doc", 8) == 0 && av[1][8] == '\0')
		pipex->here_doc = 1;												// ac < 6 ERROR
	else if (access(av[1], F_OK | R_OK) == -1)
		return (1); // ERROR INFILE 
	return (0);
}

int	open_file(char *file, t_type type)
{
	int	fd;

	if (type == TRUNC)
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC | O_CLOEXEC, 0664);
	if (type == APPEND)
		fd = open(file, O_WRONLY | O_CREAT | O_APPEND | O_CLOEXEC, 0664);
	if (type == RDONLY)
		fd = open(file, O_RDONLY | O_CLOEXEC);
	if (fd == -1)
		return (-10); // ERROR
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
	return(envp[i]);
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
	free (tab[i]);
	free (tab);
	return ;
}

int	main(int ac, char **av, char **envp)
{
	char	*path_line;
	t_pipex	pipex;

	pipex.here_doc = 0;
	if (parse_args(ac, av, &pipex))
		return (0);
	if (pipex.here_doc == 1)
	{	
		pipex.index = 3;
		here_doc(av);
		pipex.outfile_fd = open_file(av[ac - 1], APPEND);
	}
	else
	{ 
		pipex.index = 2;
		pipex.infile_fd = open_file(av[1], RDONLY); //ERROR -1 A GERER
		make_dup(pipex.infile_fd, STDIN_FILENO);
		pipex.outfile_fd = open_file(av[ac - 1], TRUNC); //ERROR -1 A GERER
	}
	path_line = path_finding(envp);
	if (path_line == NULL)
		return (0); // ERROR PATH
	pipex.paths = ft_split(path_line + 5, ':');
	while (pipex.index < (ac - 2))
		create_child(&pipex, av[pipex.index++], envp);
	make_dup(pipex.outfile_fd, STDOUT_FILENO);
	get_execve(av[ac - 2], envp);
	return (0);
}
