/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscabell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 08:37:34 by vscabell          #+#    #+#             */
/*   Updated: 2020/03/02 14:38:35 by vscabell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	ft_breakline(char *str, char c)
{
	int i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	if (str[i] != c)
		return (-1);
	return (i);
}

static int	ft_newline(char **p_line, char **line, int i, char *buffer)
{
	char	*tmp;

	*line = ft_substr(*p_line, 0, i);
	tmp = ft_substr(*p_line, (i + 1), ft_strlen(*p_line) - i);
	free(*p_line);
	*p_line = tmp;
	if (*p_line && *p_line[0] == '\0')
	{
		free(*p_line);
		*p_line = NULL;
	}
	free(buffer);
	buffer = NULL;
	return (1);
}

static int	ft_endoffile(char **p_line, char **line, char *buffer)
{
	if (*p_line)
	{
		*line = ft_strdup(*p_line);
		free(*p_line);
		*p_line = NULL;
		free(buffer);
		buffer = NULL;
		return (0);
	}
	*line = ft_strdup("");
	free(buffer);
	buffer = NULL;
	return (0);
}

static int	ft_gnl(char **line, int fd, char *buffer)
{
	static char	*p_line[OPEN_MAX];
	char		*tmp;
	int			i;
	int			r_byte;

	if (p_line[fd] && (i = ft_breakline(p_line[fd], '\n')) >= 0)
		return (ft_newline(&p_line[fd], line, i, buffer));
	while ((r_byte = read(fd, buffer, BUFFER_SIZE)) > 0)
	{
		buffer[r_byte] = '\0';
		if (!p_line[fd])
			p_line[fd] = ft_strdup(buffer);
		else
		{
			tmp = ft_strjoin(p_line[fd], buffer);
			free(p_line[fd]);
			p_line[fd] = tmp;
		}
		if ((i = ft_breakline(p_line[fd], '\n')) >= 0)
			return (ft_newline(&p_line[fd], line, i, buffer));
	}
	return (ft_endoffile(&p_line[fd], line, buffer));
}

int			get_next_line(int fd, char **line)
{
	char	*buffer;

	if (fd < 0 || !line || BUFFER_SIZE < 1 || read(fd, NULL, 0) < 0)
		return (-1);
	if (!(buffer = malloc((BUFFER_SIZE + 1) * sizeof(char *))))
		return (0);
	return (ft_gnl(line, fd, buffer));
}
