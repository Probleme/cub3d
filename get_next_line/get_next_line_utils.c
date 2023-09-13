/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataouaf <ataouaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 03:05:22 by ataouaf           #+#    #+#             */
/*   Updated: 2023/09/13 08:15:13 by ataouaf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

// size_t	ft_strlen(char *str)
// {
// 	int	i;

// 	i = 0;
// 	while (str[i])
// 		i++;
// 	return (i);
// }

char	*ft_strchr(char *s, int c)
{
	int	i;

	i = 0;
	if (!s)
		return (NULL);
	while (s[i])
	{
		if (s[i] == (char )c)
			return ((char *)s + i);
		i++;
	}
	return (NULL);
}

// char	*ft_strjoin(char *s1, char *s2)
// {
// 	int		i;
// 	int		j;
// 	char	*str;

// 	if (!s2)
// 		return (NULL);
// 	str = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
// 	if (!str)
// 		return (NULL);
// 	i = -1;
// 	j = 0;
// 	while (s1[++i] != '\0')
// 		str[i] = s1[i];
// 	while (s2[j] != '\0')
// 		str[i++] = s2[j++];
// 	str[ft_strlen(s1) + ft_strlen(s2)] = '\0';
// 	return (str);
// }

char	*ft_strjoin1(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*str;

	if (!s1)
	{
		s1 = (char *)malloc(1 * sizeof(char));
		s1[0] = '\0';
	}
	if (!s2)
		return (NULL);
	str = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (!str)
		return (NULL);
	i = -1;
	j = 0;
	while (s1[++i] != '\0')
		str[i] = s1[i];
	while (s2[j] != '\0')
		str[i++] = s2[j++];
	str[ft_strlen(s1) + ft_strlen(s2)] = '\0';
	free(s1);
	return (str);
}
