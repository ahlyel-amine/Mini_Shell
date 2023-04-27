/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_tools2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 03:14:01 by aahlyel           #+#    #+#             */
/*   Updated: 2023/04/27 13:43:18 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "archive.h"

int	ft_isprint_nspc(int c)
{
	return (c > 0x20 && c <= 0x7e);
}



size_t ft_double_strlen(char **str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

char	**ft_joindstrs(char **ds1, char* *ds2)
{
	char	**words;
	int		ds1_len;	
	int		ds2_len;
	int		i;
	int		j;
	
	ds1_len = ft_double_strlen(ds1);
	ds2_len = ft_double_strlen(ds2);
	i = -1;
	j = 0;
	words = malloc(sizeof(char *) * (ds1_len + ds2_len + 1));
	if (!words)
		return (NULL);
	while (ds1[++i])
		words[i] = ds1[i];
	while (ds2[j])
		words[i++] = ds2[j++];
	words[i] = NULL;
	return (words);
}

int	ft_strnstrpos(const char *haystack, const char *needle)
{
	int	i;
	int	j;
	int	k;

	j = 0;
	if (!*needle || (haystack == needle))
		return (0);
	while (haystack[j])
	{
		i = 0;
		k = 0;
		while (needle[i] == haystack[j + k])
		{
			i++;
			k++;
			if (!needle[i])
				return (j + 1);
		}
		j++;
	}
	return (-1);
}
