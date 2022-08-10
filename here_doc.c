/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouay <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 15:48:49 by adouay            #+#    #+#             */
/*   Updated: 2022/08/10 20:09:39 by adouay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
void	here_doc2(int fd[2], char *limiter)
{
	char	*line;
	int		limiter_len;

	limiter_len = ft_strlen(limiter);
	while (1)
	{
		write (0, "pipex here_doc>", 15);
		line = get_next_line(0, limiter);
		if (line == NULL)
			exit(0); // ERROR
		if (ft_strncmp(line, limiter, limiter_len) == 0 && line[limiter_len] == '\n')
		{
			free(line);
			close_pipe(fd);
			exit(0);
		}
		write(fd[1], &line, ft_strlen(line));
		free (line);
	}
}

void	here_doc(char **av)
{
	int		fd[2];
	int		pid;

	if (pipe(fd) == -1)
		return ; 	// ERROR
	pid = fork();
	if (pid == 0)
		here_doc2(fd, av[2]);
	else
	{
		make_dup(fd[0], STDIN_FILENO);
		close_pipe(fd);
		waitpid(pid, NULL, 0);
	}
}