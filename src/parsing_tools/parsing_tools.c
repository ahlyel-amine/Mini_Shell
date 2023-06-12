/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 07:20:43 by aahlyel           #+#    #+#             */
/*   Updated: 2023/06/12 17:40:23 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../include/minishell.h"

int	ft_chrpos(char *line,  char c)
{
	int	i = 0;
	
	if (!line)
		return (-1);
	while (line[i] && line[i] != c)
		i++;
	if (line[i] == c)
		return (i);
	return (-1);
}

int	ft_isvariable(char c)
{
	// return (ft_isalnum(c) || c == '_' || c == '*' || c == '$');
	return (c != '&' && c != '|' && c != '<' && c != '>' && c != '(' && c != ')');
}

char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*str;
	size_t	s1_len;
	size_t	s2_len;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	str = (char *)ft_calloc((s1_len + s2_len + 1), sizeof(char));
	if (!str)
		return (NULL);
	ft_memcpy(str, s1, s1_len);
	ft_memcpy(str + s1_len, s2, s2_len);
	return (free(s1), free(s2), str);
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
	free(ds1);
	free(ds2);
	return (words);
}