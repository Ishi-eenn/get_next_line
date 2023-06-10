/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsishika <tsishika@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 15:30:48 by tsishika          #+#    #+#             */
/*   Updated: 2023/06/10 10:38:18 by tsishika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*read_file(int fd, char *buff, char *save)
{
	int		status;
	char	*save_temp;

	status = 1;
	while (status != 0)
	{
		status = read(fd, buff, BUFFER_SIZE);
		if (status == -1)
			return (NULL);
		if (status == 0)
			break ;
		buff[status] = '\0';
		if (!save)
			save = ft_strdup("");
		save_temp = save;
		save = ft_strjoin(save_temp, buff);
		free(save_temp);
		save_temp = NULL;
		if (ft_strchr(buff, '\n'))
			break ;
	}
	return (save);
}

char	*ft_clear(char *line)
{
	int		i;
	char	*save;

	i = 0;
	while (line[i] != '\n' && line[i] != '\0')
		i++;
	if (line[i] == '\0' || line[1] == '\0')
		return (NULL);
	save = ft_substr(line, i + 1, ft_strlen(line) - i);
	if (*save == '\0')
	{
		free(save);
		save = NULL;
	}
	line[i + 1] = '\0';
	return (save);
}

char	*get_next_line(int fd)
{
	char			*buff;
	char			*line;
	static char		*save[OPEN_MAX];

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buff = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buff)
		return (NULL);
	line = read_file(fd, buff, save[fd]);
	free(buff);
	buff = NULL;
	if (line)
		save[fd] = ft_clear(line);
	return (line);
}
