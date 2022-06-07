/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalia <iwhana@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 00:00:41 by amalia            #+#    #+#             */
/*   Updated: 2021/11/22 08:42:10 by amalia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_read_saved(int fd, char *saved)
{
	char	*buf;
	int		rd_byt;

	buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (NULL);
	buf[BUFFER_SIZE] = '\0';
	rd_byt = 1;
	while (!ft_strchr(saved, '\n') && rd_byt != 0)
	{
		rd_byt = read(fd, buf, BUFFER_SIZE);
		if (rd_byt == -1)
		{
			free(buf);
			return (NULL);
		}
		buf[rd_byt] = '\0';
		saved = ft_strjoin(saved, buf);
	}
	free(buf);
	return (saved);
}

char	*ft_get_line(char *saved)
{
	int		i;
	char	*str;

	i = 0;
	if (!saved[i])
		return (NULL);
	while (saved[i] && saved[i] != '\n')
		i++;
	str = (char *)malloc(sizeof(char) * (i + 2));
	if (!str)
		return (NULL);
	i = 0;
	while (saved[i] && saved[i] != '\n')
	{
		str[i] = saved[i];
		i++;
	}
	if (saved[i] == '\n')
	{
		str[i] = saved[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_new_saved(char *saved)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	while (saved[i] && saved[i] != '\n')
		i++;
	if (!saved[i])
	{
		free(saved);
		return (NULL);
	}
	str = (char *)malloc(sizeof(char) * (ft_strlen(saved) - i + 1));
	if (!str)
		return (NULL);
	i++;
	j = 0;
	while (saved[i])
		str[j++] = saved[i++];
	str[j] = '\0';
	free(saved);
	return (str);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*saved;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	saved = ft_read_saved(fd, saved);
	if (!saved)
		return (NULL);
	line = ft_get_line(saved);
	saved = ft_new_saved(saved);
	return (line);
}
