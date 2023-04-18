/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spliter.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 05:57:23 by aahlyel           #+#    #+#             */
/*   Updated: 2023/04/18 07:21:23 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	**alloc_for_words(int words_nbr)
{
	char	**splited;
	int		i;

	i = 0;
	splited = malloc(sizeof(char *) * words_nbr + 1);
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
	splited[call_count - 1] = strndup(line, j);  //strdnduuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuup
	return (splited);
}

 
char	*read_until_chr(char *line, char c)
{
	char	*dquote;
	int		quote_pos;

	while (1337)
	{
		if (c == '\'')
			dquote = readline("quote> ");
		else
			dquote = readline("dquote> ");
		line = ft_strjoin_free(line, ft_strdup("\n"));
		line = ft_strjoin_free(line, dquote);
		quote_pos = ft_chrpos(line + 1, c);
		if (quote_pos != -1)
			break ;
	}
	return (line);
}

char	**quote_handler(char **line, int *i, int ref, int *set_call_counter)
{
	char	**splited;
	int	j;

	j = 0;
	splited = NULL;
	if ((*line)[*i] == '\'')
	{
		(*i)++;
		while ((*line)[*i + j] && (*line)[*i + j] != '\'')
			j++;
		if ((*line)[*i + j] != '\'')
		{
			(*line) = read_until_chr(*line, '\'');
			(*i)--;
			return (splited);
		}
		splited = set_splited((*line) + *i - 1, j + 2, ref, *set_call_counter);
		(*set_call_counter)++;
		*i += j + 1;
	}
	return (splited);
}

char	**dquote_handler(char **line, int *i, int ref, int *set_call_counter)
{
	char	**splited;
	int	j;

	j = 0;
	splited = NULL;
	if ((*line)[*i] == '\"')
	{
		(*i)++;
		while ((*line)[*i + j] && (*line)[*i + j] != '\"')
			j++;
		if ((*line)[*i + j] != '\"')
		{
			(*line) = read_until_chr(*line, '\"');
			(*i)--;
			return (splited);
		}
		splited = set_splited((*line) + *i - 1, j + 2, ref, *set_call_counter);
		(*set_call_counter)++;
		*i += j + 1;
	}
	return (splited);
}

char	**strings_handler(char **line, int *i, int ref, int *set_call_counter)
{
	char	**splited;
	int	j;

	j = 0;
	splited = NULL;
	if ((*line)[*i] != '\"' && (*line)[*i] != '\'' && ft_isprint_nspc((*line)[*i]))
	{
		while (ft_isprint_nspc((*line)[*i + j])  && (*line)[*i + j] != '\'' && (*line)[*i + j] != '\"')
			j++;
		splited = set_splited((*line) + *i, j, ref, *set_call_counter);
		(*set_call_counter)++;
		*i += j;
		j = 0;
	}
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
	}
	return (set_splited(0, 0, -2, 0));
}
