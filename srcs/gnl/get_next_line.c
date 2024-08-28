/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccadoret <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 13:06:30 by ccadoret          #+#    #+#             */
/*   Updated: 2023/10/24 13:06:34 by ccadoret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "../../includes/get_next_line.h"
#include <stdio.h>
#include <fcntl.h>

char	*free_var(char *return_value, char *free_value)
{
	free(free_value);
	return (return_value);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*new;
	size_t	slen;
	size_t	finish;

	if (!s)
		return (0);
	slen = ft_strlen(s);
	finish = 0;
	if (start < slen)
		finish = slen - start;
	if (finish > len)
		finish = len;
	new = (char *)malloc(sizeof(char) * (finish + 1));
	if (!new)
		return (0);
	ft_strlcpy(new, s + start, finish + 1);
	return (new);
}

char	*read_line(int fd)
{
	char	*line_str;
	char	*tmp;
	int		size;

	size = 1;
	tmp = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	line_str = ft_strdup("");
	while (size > 0)
	{
		size = read(fd, tmp, BUFFER_SIZE);
		if (size < 0)
		{
			free(tmp);
			free(line_str);
			return (NULL);
		}
		tmp[size] = '\0';
		line_str = ft_strjoin_spe(line_str, tmp);
		if (ft_strchr_spe(tmp, '\n') != -1)
			return (free_var(line_str, tmp));
	}
	return (free_var(line_str, tmp));
}

char	*get_next_line(int fd)
{
	static char	*surp;
	char		*line;
	char		*tmp;

	if (surp == NULL)
		line = read_line(fd);
	else
	{
		tmp = read_line(fd);
		line = ft_strjoin_spe(surp, tmp);
		surp = free_var(NULL, tmp);
	}
	if (!line || line == NULL || *line == '\0')
		return (free_var(NULL, line));
	if (ft_strchr_spe(line, '\n') != -1)
	{
		surp = ft_substr(line, ft_strchr_spe(line, '\n'), ft_strlen(line));
		if (*surp == '\0' || !surp)
			surp = free_var(NULL, surp);
		tmp = ft_strdup(line);
		free(line);
		line = ft_substr(tmp, 0, ft_strchr_spe(tmp, '\n'));
		return (free_var(line, tmp));
	}
	return (line);
}

/*int	main(void)
{
	int		fd;
	char	*s;

	fd = open("test2.txt", O_RDONLY);
	s = get_next_line(fd);
	printf("[%s]", s);
	free(s);
	s = get_next_line(fd);
	printf("[%s]", s);
	free(s);
	s = get_next_line(fd);
	printf("[%s]", s);
	free(s);
	s = get_next_line(fd);
	printf("[%s]", s);
	free(s);
	s = get_next_line(fd);
	printf("[%s]", s);
	free(s);
	s = get_next_line(fd);
	printf("[%s]", s);
	free(s);
	s = get_next_line(fd);
	printf("[%s]", s);
	free(s);
	s = get_next_line(fd);
	printf("[%s]", s);
	free(s);
	s = get_next_line(fd);
	printf("[%s]", s);
	free(s);
	s = get_next_line(fd);
	printf("[%s]", s);
	free(s);
	s = get_next_line(fd);
	printf("[%s]", s);
	free(s);
	s = get_next_line(fd);
	printf("[%s]", s);
	free(s);
	return (0);
}*/
