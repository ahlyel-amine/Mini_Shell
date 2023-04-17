/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spliter.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 05:57:23 by aahlyel           #+#    #+#             */
/*   Updated: 2023/04/17 21:52:00 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_isprint_nspc(int c)
{
	return (c > 0x20 && c <= 0x7e);
}
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
	splited[call_count - 1] = strndup(line, j);  //strdnduuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuup
	return (splited);
}

char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*str;
	size_t	s1_len;
	size_t	s2_len;

	if (!s1 || !s2)
		return (NULL);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	str = (char *)ft_calloc((s1_len + s2_len + 1), sizeof(char));
	if (!str)
		return (NULL);
	ft_memcpy(str, s1, s1_len);
	ft_memcpy(str + s1_len, s2, s2_len);
	return (free(s1), free(s2), str);
}

char	*read_until_dquote(char *line)
{
	char	*dquote;

	while (1337)
	{
		dquote = readline("dquote> ");
		line = ft_strjoin_free(line, dquote);
		// tmp = ft_strjoin_free(tmp, ft_strdup("\n"));
		if (ft_strchr(line, '\"') != NULL)
			return (line);
	}
	return (line);
}

char	**dquote_handler(char *line, int *i, int ref, int *set_call_counter)
{
	char	**splited;
	int	j;

	j = 0;
	printf("%s\n", line);
	if (line[*i] == '\"')
	{
		(*i)++;
		while (line[*i + j] && line[*i + j] != '\"')
			j++;
		if (line[*i + j] != '\"')
		{
			line = read_until_dquote(line);
			(*set_call_counter)++;
			splited = dquote_handler(line, i, ref, set_call_counter);
		}
		else
		{
			splited = set_splited(line + *i - 1, j + 2, ref, *set_call_counter);
			(*set_call_counter)++;
			*i += j + 1;
		}
	}
	return (splited);
}

char	**quote_handler(char *line, int *i, int ref, int *set_call_counter)
{
	char	**splited;
	int	j;

	j = 0;
	if (line[*i] == '\'')
	{
		(*i)++;
		while (line[*i + j] && line[*i + j] != '\'')
			j++;
		splited = set_splited(line + *i - 1, j + 2, ref, *set_call_counter);
		(*set_call_counter)++;
		*i += j + 1;
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
		splited = dquote_handler(line, &i, ref, &set_call_counter);
		splited = quote_handler(line, &i, ref, &set_call_counter);
		if (ft_isprint_nspc(line[i]) && line[i] != '\'' && line[i] != '\"')
		{
			while (ft_isprint_nspc(line[i + j])  && line[i + j] != '\'' && line[i + j] != '\"')
				j++;
			splited = set_splited(line + i, j, ref, set_call_counter);
			set_call_counter++;
			i += j;
			j = 0;
		}
		while (line[i] && !ft_isprint_nspc(line[i]))
			i++;
	}
	if (!ref)
	{
		set_splited(0, 0, -1, 0);
		splited = spliter(line, 1);
	}
	return (splited);
}