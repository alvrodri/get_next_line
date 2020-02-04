/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvrodri <alvrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 11:09:58 by alvrodri          #+#    #+#             */
/*   Updated: 2020/02/04 14:28:12 by alvrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		ft_split_line(char **files, int fd, int bytes, char **line)
{
	char *tmp;

	tmp = files[fd];
	if (bytes == 0 && !files[fd])
	{
		*line = ft_strdup("");
		return (0);
	}
	if (!ft_strchr(files[fd], '\n'))
	{
		*line = ft_strdup(files[fd]);
		free(files[fd]);
		files[fd] = NULL;
		return (0);
	}
	*line = ft_substr(tmp, 0, ft_strlen(tmp) - ft_strlen(ft_strchr(tmp, '\n')));
	files[fd] = ft_strdup(ft_strchr(tmp, '\n') + 1);
	free(tmp);
	return (1);
}

int		get_next_line(int fd, char **line)
{
	int			bytes;
	char		*buff;
	char		*tmp;
	static char	*files[4096];

	if (fd == -1 || !line || !(buff = malloc(sizeof(char) * (BUFFER_SIZE + 1)))
	|| read(fd, buff, 0) == -1 || BUFFER_SIZE <= 0)
		return (-1);
	while ((bytes = read(fd, buff, BUFFER_SIZE)) > 0)
	{
		buff[bytes] = '\0';
		if (files[fd] == NULL)
			files[fd] = ft_strdup(buff);
		else
		{
			tmp = ft_strdup(files[fd]);
			free(files[fd]);
			files[fd] = ft_strjoin(tmp, buff);
			free(tmp);
		}
		if (ft_strchr(buff, '\n'))
			break ;
	}
	free(buff);
	return (ft_split_line(files, fd, bytes, line));
}
