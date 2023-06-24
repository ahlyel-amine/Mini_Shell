/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spliter_handlers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbrahm <aelbrahm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 07:29:46 by aahlyel           #+#    #+#             */
/*   Updated: 2023/06/24 18:32:36 by aelbrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "archive.h"

char	**quote_handler(char **line, int *i, int ref, int *set_call_counter)
{
	char	**splited;
	char	*tmp;
	int	j;
	int		quote;
	quote = 0;
	j = 0;
	tmp = NULL;
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
		tmp = ft_substr(*line, *i, j++);
		quote = j;
		while ((*line)[*i + j] && (*line)[*i + j] != ' ')
			j++;
		if (j - quote)
			tmp = ft_strjoin(tmp, ft_substr(*line + *i, quote, j - 1));
		splited = set_splited(tmp, ref, *set_call_counter);
		(*set_call_counter)++;
		*i += j + 1;
	}
	return (splited);
}

char	**dquote_handler(char **line, int *i, int ref, int *set_call_counter)
{
	char	**splited;
	char	*tmp;
	int	j;
	int		quote;
	quote = 0;
	j = 0;
	tmp = NULL;
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
		tmp = ft_substr(*line, *i, j++);
		quote = j;
		while ((*line)[*i + j] && (*line)[*i + j] != ' ')
		{
				printf("{%c}",(*line)[*i + j]);
			j++;
		}
		if (j - quote) 
			tmp = ft_strjoin(tmp, ft_substr(*line + *i + quote, 0, j - quote));
		splited = set_splited(tmp, ref, *set_call_counter);
		(*set_call_counter)++;
		*i += j;
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
		splited = set_splited(ft_substr(*line, *i, j), ref, *set_call_counter);
		(*set_call_counter)++;
		*i += j;
		j = 0;
	}
	return (splited);
}