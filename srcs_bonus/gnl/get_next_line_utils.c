/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 13:06:38 by ccadoret          #+#    #+#             */
/*   Updated: 2024/08/01 14:31:45 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "../../includes/get_next_line.h"
#include <stddef.h>

char	*ft_strjoin_spe(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*str;

	i = -1;
	j = 0;
	if ((!s1 && !s2) || (s1 == NULL && s2 == NULL))
	{
		str = NULL;
		return (str);
	}
	str = (char *)malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	while (s1[++i])
		str[i] = s1[i];
	while (s2[j])
	{
		str[i + j] = s2[j];
		j++;
	}
	str[j + i] = '\0';
	if (s1 != NULL)
		free(s1);
	return (str);
}

char	*ft_strdup(const char *src)
{
	char	*dup;
	int		i;

	i = 0;
	while (src[i])
		i++;
	dup = malloc(i + 1);
	if (dup != NULL)
	{
		i = 0;
		while (src[i])
		{
			dup[i] = src[i];
			i++;
		}
		dup[i] = '\0';
	}
	return (dup);
}

int	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}

int	ft_strchr_spe(const char *s, int c)
{
	int	i;

	i = 0;
	c = (char)c;
	while (s[i] != c && s[i])
		i++;
	if (s[i] != (char)c)
		return (-1);
	return (i + 1);
}

int	ft_strlcpy(char *dst, char const *src, int size)
{
	int	src_len;
	int	i;

	src_len = 0;
	if (size == 0)
		return (ft_strlen(src));
	if (size > 0)
	{
		while (src[src_len])
		{
			src_len++;
		}
		i = 0;
		while ((i < size - 1) && src[i])
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (src_len);
}
