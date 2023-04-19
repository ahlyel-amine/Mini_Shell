/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spliter_handlers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 07:29:46 by aahlyel           #+#    #+#             */
/*   Updated: 2023/04/19 06:46:05 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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