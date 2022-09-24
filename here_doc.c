/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouay <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 15:48:49 by adouay            #+#    #+#             */
/*   Updated: 2022/09/23 18:25:16 by adouay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	here_doc2(int fd[3], char *limiter)
{
	char	*line;
	int		limiter_len;

	limiter_len = ft_strlen(limiter);
	while (1)
	{
		write (0, "pipex here_doc>", 15);
		line = get_next_line(0, limiter);
		if (line == NULL)
		{
			close_pipe(fd);
			exit(0);
		}
		if (ft_strncmp(line, limiter, limiter_len) == 0
			&& line[limiter_len] == '\n')
		{
			free(line);
			fd[2] = fd[0];
			close_pipe(fd);
			exit(0);
		}
		ft_putstr_fd(line, fd[1]);
		free (line);
	}
}

void	here_doc(t_pipex *pipex, char *av)
{
	int		pid;

	if (pipe(pipex->fd) == -1)
		exit (msg_error("pipe error"));
	pid = fork();
	if (pid == -1)
		exit (msg_error("fork error"));
	if (pid == 0)
		here_doc2(pipex->fd, av);
	else
	{
		close(pipex->fd[1]);
		waitpid(pid, NULL, 0);
	}
}
