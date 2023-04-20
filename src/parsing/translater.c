/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translater.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 02:51:48 by aahlyel           #+#    #+#             */
/*   Updated: 2023/04/20 00:57:09 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	**split_to_3(char *word, char *separater, int befor_sep, int after_sep)
{
	char	**words;

	words = malloc(sizeof(char *) * 4);
	if (!words)
		return (NULL);
	words[3] = NULL;
	words[0] = ft_substr(word, 0, befor_sep);
	words[1] = ft_strdup(separater);
	words[2] = ft_substr(word, befor_sep + ft_strlen(separater), ft_strlen(word));
	return	(words);
}

char	**split_to_2(char *word, char *separater, int befor_sep, int after_sep)
{
	char	**words;

	words = malloc(sizeof(char *) * 3);
	if (!words)
		return (NULL);
	words[2] = NULL;
	if (befor_sep)
	{
		words[0] = ft_substr(word, 0, befor_sep);
		words[1] = ft_strdup(separater);
	}
	else
	{
		words[0] = ft_strdup(separater);
		words[1] = ft_substr(word, ft_strlen(separater), ft_strlen(word));
	}
	return	(words);
}

char	**separate_word(char *word, char *separater)
{
	char	**new_words;
	int	befor_sep;
	int	after_sep;
	
	new_words = NULL;
	befor_sep = ft_strnstrpos(word, separater) - 1;
	after_sep = ft_strlen(word) - ft_strlen(separater) - befor_sep;
	if (befor_sep && after_sep)
		new_words = split_to_3(word, separater, befor_sep, after_sep);
	else if (befor_sep || after_sep)
		new_words = split_to_2(word, separater, befor_sep, after_sep);
	return (new_words);
}

char	**check_for_args(char	*word)
{
	char	**new_words;
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(word);
	if (ft_strnstr(word, "&&", len) && ft_strlen(word) != 2)
		new_words = separate_word(word, "&&");
	return (new_words);
}

char	**replace_pointer(char **words, char **new_words, int i)
{
	char	**dwords;
	int	len1;
	int	len2;
	int	k = -1;
	int	j = 0;

	len1 = ft_double_strlen(words);
	len2 = ft_double_strlen(new_words);
	dwords = malloc(sizeof(char *) *  (len1 + len2));
	dwords[len1 + len2 - 1] = NULL;
	while (++k < i)
		dwords[k] = words[k];
	free(words[i]);
	while (j < len2)
		dwords[k++] = new_words[j++];
	while (++i < len1 - 1)
		dwords[k++] = words[i];
	return (dwords);
}

char	**words_to_args(char **words)
{
	char	**new_words;
	int	i;

	i = 0;
	while (words[i])
	{
		if (*words[i] == '\'' || *words[i] == '\"')
		{
			i++;
			continue ;
		}
		new_words = check_for_args(words[i]);
		return (replace_pointer(words, new_words, i));
		i++;
	}
	return (words);
}