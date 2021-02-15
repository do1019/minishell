/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogata <dogata@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/29 08:40:57 by dogata            #+#    #+#             */
/*   Updated: 2021/02/15 23:58:36 by dogata           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#define SUCCESS 1
#define ERROR -1
#define REACHED_EOF 0
#define FD_MAX 256
#define BUFFER_SIZE 1024

static int	free_rt(int result, char **s1, char **s2)
{
	if (s1)
	{
		free(*s1);
		*s1 = NULL;
	}
	if (s2)
	{
		free(*s2);
		*s2 = NULL;
	}
	return (result);
}

static int	store_in_line_join(int fd, char **save, char *buf, char **line)
{
	char	*nl;
	char	*tmp;
	int		rv;

	while ((rv = read(fd, buf, BUFFER_SIZE)) > 0)
	{
		buf[rv] = '\0';
		if ((nl = ft_strchr(buf, '\n')))
		{
			if (!(tmp = ft_substr(buf, 0, nl - buf)))
				return (free_rt(ERROR, &(*save), NULL));
			if (!(*line = ft_free_strjoin(*save, tmp)))
				return (free_rt(ERROR, &buf, &tmp));
			if (!(*save = ft_substr(buf, (nl - buf) + 1, ft_strlen(nl + 1))))
				return (free_rt(ERROR, &tmp, NULL));
			return (free_rt(SUCCESS, &buf, &tmp));
		}
		else if (!(*save = ft_free_strjoin(*save, buf)))
			return (free_rt(ERROR, &buf, NULL));
	}
	return (rv == 0 ? free_rt(0, &buf, NULL) : free_rt(ERROR, &buf, NULL));
}

static int	store_in_line(char **save, char **line, char *nl)
{
	char	*tmp;

	tmp = *save;
	if (nl)
	{
		if (!(*line = ft_substr(*save, 0, nl - *save)))
			return (ERROR);
		if (!(*save = ft_substr(*save, (nl - *save) + 1, ft_strlen(nl + 1))))
			return (ERROR);
		return (free_rt(SUCCESS, &tmp, NULL));
	}
	else if (!(*line = ft_strdup(tmp)))
		return (free_rt(ERROR, &(*save), NULL));
	return (free_rt(REACHED_EOF, &(*save), NULL));
}

int			get_next_line(int fd, char **line)
{
	static char	*save[FD_MAX + 1];
	char		*buf;
	char		*new_line;
	int			result;

	if (fd < 0 || FD_MAX < fd || BUFFER_SIZE < 1 || !line)
		return (ERROR);
	if (!save[fd])
		if (!(save[fd] = ft_strdup("")))
			return (ERROR);
	if ((new_line = ft_strchr(save[fd], '\n')))
		return (store_in_line(&save[fd], line, new_line));
	if (!(buf = malloc(sizeof(char) * (BUFFER_SIZE + 1))))
		return (free_rt(ERROR, &save[fd], NULL));
	if ((result = store_in_line_join(fd, &save[fd], buf, line)) != 0)
		return (result == SUCCESS ? SUCCESS : ERROR);
	return (store_in_line(&save[fd], line, NULL));
}
