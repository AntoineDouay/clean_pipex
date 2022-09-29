/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouay <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 11:27:51 by adouay            #+#    #+#             */
/*   Updated: 2022/09/27 15:04:10 by adouay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	file_error(char *file)
{
	ft_putstr_fd("bash: ", 2);
	ft_putstr_fd(file, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
	return (1);
}

int	arg_error(void)
{
	ft_putstr_fd("need more arg, syntax is :\n", 2);
	ft_putstr_fd("./pipex file1 cmd1 cmd2 cmd3 ... cmdn file2\n", 2);
	ft_putstr_fd("or ./pipex here_doc LIMITER cmd cmd1 file\n", 2);
	return (2);
}

int	cmd_error(char *cmd)
{
	if (cmd[0] == '\0')
		ft_putstr_fd("''", 2);
	else
		ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": command not found", 2);
	ft_putstr_fd("\n", 2);
	return (1);
}

int	msg_error(char *msg)
{
	ft_putstr_fd("bash: ", 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
	return (8);
}
