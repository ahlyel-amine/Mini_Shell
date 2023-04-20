/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_tools2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 03:14:01 by aahlyel           #+#    #+#             */
/*   Updated: 2023/04/19 23:45:10 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
