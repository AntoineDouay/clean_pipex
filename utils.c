/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouay <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 23:17:35 by adouay            #+#    #+#             */
/*   Updated: 2022/09/24 23:23:18 by adouay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	make_dup(int oldfd, int newfd)
{
	if (dup2(oldfd, newfd) == -1)
		exit (msg_error("dup2 error"));
}

void	close_pipe(int fd[3])
{
	if (fd[0] > 0)
		close(fd[0]);
	if (fd[1] > 0)
		close(fd[1]);
	if (fd[2] > 0)
		close(fd[2]);
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
