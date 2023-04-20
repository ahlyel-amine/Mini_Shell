/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spliter.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 05:57:23 by aahlyel           #+#    #+#             */
/*   Updated: 2023/04/20 05:31:19 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	**alloc_for_words(int words_nbr)
{
	char	**splited;
	int		i;

	i = 0;
	splited = malloc(sizeof(char *) * (words_nbr + 1));
	while (i < words_nbr + 1)
		splited[i++] = NULL;
	return (splited);
}

char	**set_splited(char *line, int j, int count_inc, int call_count)
{
	static char **splited;
	static int	words_nbr;

	if (!count_inc)
		return (words_nbr++, NULL);
	else if (count_inc == -1)
		return (splited = alloc_for_words(words_nbr), splited);
	else if (count_inc == -2)
		return (splited);
	// splited[call_count - 1] = strndup(line, j);  //strdnduuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuup
	splited[call_count - 1] = ft_substr(line, 0, j);
	return (splited);
}

char	**spliter(char *line, int ref)
{
	char	**splited;
	int		i;
	int		j;
	int		set_call_counter;

	i = 0;
	set_call_counter = 1;
	splited = NULL;
	while (line[i])
	{
		j = 0;
		dquote_handler(&line, &i, ref, &set_call_counter);
		quote_handler(&line, &i, ref, &set_call_counter);
		strings_handler(&line, &i, ref, &set_call_counter);
		while (line[i] && !ft_isprint_nspc(line[i]))
			i++;
	}
	if (!ref)
	{
		set_splited(0, 0, -1, 0);
		splited = spliter(line, 1);
		free(line);
	}
	return (set_splited(0, 0, -2, 0));
}
