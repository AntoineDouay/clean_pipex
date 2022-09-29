/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouay <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 00:15:49 by adouay            #+#    #+#             */
/*   Updated: 2022/09/26 12:49:44 by adouay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef GET_NEXT_LINE_BONUS_H

# define GET_NEXT_LINE_BONUS_H

# include <stdio.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stddef.h>

char	*get_next_line(int fd, char *limiter);
char	*ft_strjoin_pimped(char *s1, char *s2);
char	*ft_strchr_gnl(const char *s, int c);
int		ft_strncmp_gnl(const char *s1, const char *s2, size_t n);
size_t	ft_strlen_gnl(const char *s);

#endif
