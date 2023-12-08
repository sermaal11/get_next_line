/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarin-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 16:40:24 by smarin-a          #+#    #+#             */
/*   Updated: 2023/11/20 19:50:29 by smarin-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*buffer_remainder(char *buff)
{
	int		buff_len;
	int		i;
	int		j;
	char	*buff_rema;

	buff_len = ft_strlen(buff);
	i = 0;
	while (buff[i] && buff[i] != '\n')
		i++;
	if (buff[i] == '\n')
		i++;
	buff_rema = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (buff_rema == NULL)
	{
		free(buff);
		return (NULL);
	}
	j = 0;
	while (buff[i] != '\0')
		buff_rema[j++] = buff[i++];
	buff_rema[j] = '\0';
	free(buff);
	buff = NULL;
	return (buff_rema);
}

char	*take_line(char *buff)
{
	int		i;
	char	*line;

	i = 0;
	while (buff[i] && buff[i] != '\n')
		i++;
	if (buff[i] == '\n')
		i++;
	line = (char *)malloc((i + 1) * sizeof(char));
	if (line == NULL)
		return (NULL);
	i = 0;
	while (buff [i] && buff[i] != '\n')
	{
		line[i] = buff[i];
		i++;
	}
	if (buff[i] == '\n')
	{
		line[i] = '\n';
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*read_until_nl(int fd, char *buff, char *temp)
{
	ssize_t	num_bytes;

	while (ft_strchr(buff, '\n') == NULL)
	{
		num_bytes = read(fd, buff, BUFFER_SIZE);
		if (num_bytes < 0)
		{
			free (temp);
			temp = NULL;
			return (NULL);
		}
		if (num_bytes == 0)
			return (temp);
		buff[num_bytes] = '\0';
		temp = ft_strjoin(temp, buff);
		if (temp == NULL)
		{
			free (temp);
			return (NULL);
		}
	}
	return (temp);
}

char	*read_buffer(int fd, char *buff)
{
	char	*temp;

	temp = NULL;
	if (buff == NULL)
	{
		buff = (char *)malloc(BUFFER_SIZE + 1);
		if (buff == NULL)
			return (NULL);
		ft_memset(buff, 0, BUFFER_SIZE + 1);
	}
	else
	{
		temp = ft_strjoin(temp, buff);
		if (temp == NULL)
			return (NULL);
	}
	temp = read_until_nl(fd, buff, temp);
	free (buff);
	buff = NULL;
	if (temp == NULL)
		return (NULL);
	return (temp);
}

char	*get_next_line(int fd)
{
	static char	*buff;
	char		*line;

	buff = read_buffer(fd, buff);
	if (buff == NULL || *buff == '\0')
	{
		free(buff);
		buff = NULL;
		return (NULL);
	}
	line = take_line(buff);
	buff = buffer_remainder(buff);
	if (!buff)
		free(buff);
	return (line);
}

/*
int	main(void)
{
	int		fd;
	int		i;
	char	*line;

	i = 0;
	fd = open("./1char.txt", O_RDONLY);
	if (fd == -1)
	{
		perror("Error abriendo el archivo");
		return (1);
	}
	line = get_next_line(fd);
	while (line != NULL)
	{
		printf("%s", line);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	system("leaks -q a.out");
	return (0);
}
*/
