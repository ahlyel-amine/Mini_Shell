/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_char.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 09:50:31 by aahlyel           #+#    #+#             */
/*   Updated: 2023/04/27 09:50:42 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	word_count(char *s, char c);

char	**ft_split_char(char const *s, char c)
{
	char	**splited;
	int		wc;
	int		i;
	int		tmp_count;

	if (!s)
		return (NULL);
	i = 0;
	wc = word_count((char *)s, c);
	splited = malloc((wc + 1) * sizeof(char *));
	while (i < wc)
	{
		tmp_count = 0;
		while (*s == c)
			s++;
		while (*(s + tmp_count) != c && *(s + tmp_count))
			tmp_count++;
		if (!tmp_count)
			break ;
		splited[i] = ft_substr(s, 0, tmp_count);
		s += tmp_count;
		i++;
	}
	splited[i] = NULL;
	return (splited);
}

static int	word_count(char *s, char c)
{
	int	i;

	i = 0;
	while (*(s++))
		if (*(s - 1) != c && (*s == c || !*s))
			i++;
	return (i);
}