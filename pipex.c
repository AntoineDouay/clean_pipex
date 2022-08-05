/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouay <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 11:34:38 by adouay            #+#    #+#             */
/*   Updated: 2022/08/05 18:41:20 by adouay           ###   ########.fr       */
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

	if (type  == TRUNC)
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0664);
	if (type  == APPEND)
		fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0664);
	if (type  == RDONLY)
		fd = open(file, O_RDONLY);
	if (fd == -1)
		return (-10); // ERROR
}

int	get_commands(char **av, t_pipex *pipex)
{
	int i;

	i = 0;
	pipex->cmds = malloc(sizeof(char *) * (pipex->commands_nbr + 1));
	if (!pipex->cmds)
		return (1);
	while (i < pipex->commands_nbr)
	{
		pipex->cmds[i] = av[i + 2 + pipex->here_doc];
		i++;
	}
	pipex->cmds[i] = 0;
	return (0);
}

char	*path_finding(char **envp)
{
	int	i;

	i = 0;
	while(ft_strncmp(envp[i], "PATH", 4) != 0)
		i++;
	return (envp[i]);
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
	t_pipex	pipex;

	pipex.here_doc = 0;
	if (parse_args(ac, av, &pipex))
		return (0);
	pipex.commands_nbr = ac - 3 - pipex.here_doc;
	if (pipex.here_doc == 1)
		here_doc(&pipex, av);
	if (get_commands(av, &pipex))
		return (0);
	pipex.path_line = path_finding(envp) + 5;
	pipex.paths = ft_split(pipex.path_line, ':');
	while (++(pipex.cmds_pos) < pipex.commands_nbr)
		create_child(&pipex, envp);
	close_pipes(&pipex);
	close(pipex.infile_fd);
	close(pipex.outfile_fd);
	free (pipex.pipe);
	free (pipex.cmds);
	free_double_array(pipex.paths);
	return (0);
}
