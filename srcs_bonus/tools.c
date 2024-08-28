/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 13:59:33 by marvin            #+#    #+#             */
/*   Updated: 2024/08/01 13:59:33 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/cube3d_bonus.h"

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	if (c == '\0')
		return ((char *)&s[ft_strlen(s)]);
	while (s[i])
	{
		if (s[i] == (char)c)
			return ((char *)&s[i]);
		i++;
	}
	if (s[i] == (char)c)
		return ((char *)&s[i]);
	return (NULL);
}

void	print_tab(char **s)
{
	int	i;

	i = -1;
	printf("---------------DEBUT-----------------\n");
	while (s[++i])
	{
		printf("%s\n", s[i]);
	}
	printf("---------The End----------------\n");
}

void	free_tab(char **tab)
{
	int	i;

	i = -1;
	if (!tab)
		return ;
	while (tab[++i])
		free(tab[i]);
	free(tab);
}

int	ft_strncmp(const char *s1, const char *s2, int n, int cmd)
{
	int	i;

	i = 0;
	if (!s2 || ft_strlen(s1) < n)
		return (1);
	if (n < 1)
		return (0);
	while (s1[i] == s2[i] && i < n && s1[i])
		i++;
	if (cmd == 0 && i == n)
		return (0);
	else if (cmd == 1 && i == n && s1[i] == '\0')
		return (0);
	return (1);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	retur;
	int	signe;

	i = 0;
	retur = 0;
	signe = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			signe = -1 ;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		retur = (retur * 10) + (str[i] - '0');
		i++;
	}
	return (signe * retur);
}
