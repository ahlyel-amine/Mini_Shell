/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spliter.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 05:57:23 by aahlyel           #+#    #+#             */
/*   Updated: 2023/04/23 20:01:23 by aahlyel          ###   ########.fr       */
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

char	**set_splited(char *line, int count_inc, int call_count)
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
	splited[call_count - 1] = line;
	return (splited);
}

// char	**spliter(char *line, int ref)
// {
// 	char	**splited;
// 	int		i;
// 	int		j;
// 	int		set_call_counter;

// 	i = 0;
// 	set_call_counter = 1;
// 	splited = NULL;
// 	while (line[i])
// 	{
// 		j = 0;
// 		dquote_handler(&line, &i, ref, &set_call_counter);
// 		quote_handler(&line, &i, ref, &set_call_counter);
// 		strings_handler(&line, &i, ref, &set_call_counter);
// 		while (line[i] && !ft_isprint_nspc(line[i]))
// 			i++;
// 	}
// 	if (!ref)
// 	{
// 		set_splited(0, -1, 0);
// 		splited = spliter(line, 1);
// 		free(line);
// 	}
// 	return (set_splited(0, -2, 0));
// }

t_arg	*new_arg(char *token, t_token x_token, int ref)
{
	static t_arg	*arg;
	t_arg			*new;
	t_arg			*tmp;
	
	if (ref == -1)
	{
		while (arg)
		{
			tmp = arg;
			arg = arg->next;
			free(tmp);
		}
		arg = NULL;
	}
	if (ref)
		return (arg);
	new = malloc(sizeof(t_arg));
	if (!new)
		return (NULL);
	new->token = token;
	new->x_token = x_token;
	new->next = NULL;
	if (!arg)
		arg = new;
	else
	{
		tmp = arg;
		while (arg->next)
			arg = arg->next;
		arg->next = new;
		arg = tmp;
	}
	return (arg);
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
		line = ft_strjoin(line, ft_strdup("\n"));
		line = ft_strjoin(line, dquote);
		quote_pos = ft_chrpos(line, c);
		if (quote_pos != -1)
			break ;
	}
	return (line);
}
char	*get_variables(char *line, int i)
{
	int	j;
	int	k;

	k = 0;
	while (line[i + k] && line[i + k] != '\"')
	{
		j = 0;
		if (line[i + k] == '$')
		{
			k++;
			if (ft_isdigit(line[i + k]))
			{
				line = ft_strjoin_free(ft_substr(line, 0, i + k - 2), ft_substr(line, i + k + 1, ft_strlen(line + i + k + 1)));
				k = 0;
				continue ;
			}
			while (line[i + k + j] && (ft_isalnum(line[i + k + j]) || line[i + k + j] == '_'))
				j++;
			k--;
			if (j)
			{
				new_arg(ft_substr(line, i + k, i + k + j), T_VARIABLE, 0);
				line = ft_strjoin_free(ft_substr(line, 0, i + k - 1), ft_substr(line, i + k + 1 + j, ft_strlen(line + i + k + 1 + j)));
				k = 0;
				continue ;
			}
		}
		k++;
	}
	return (line);
}
int dquote_handler(char **line, int i)
{
	char	*tmp;
	int		j;
	int		quote;

	quote = 0;
	j = 0;
	while ((*line)[i + j] && ((quote % 2) || (*line)[i + j] != ' '))
		if ((*line)[i + j++] == '\"')
			quote++;
	if ((quote % 2))
	{
		(*line) = read_until_chr(*line, '\"');
		// new_arg(0, 0, -1);
		return (quote_handler(line, i));
		// return (0);
	}
	tmp = ft_calloc(sizeof(char), (j - quote + 1));
	quote = 0;
	j = 0;
	while ((*line)[i + quote + j] && ((quote % 2) || (*line)[i + quote + j] != ' '))
	{
		if ((*line)[i + quote + j] == '\"')
		{
			quote++;
			continue ;
		}
		tmp[j] = (*line)[i + quote + j];
		j++;
	}
	new_arg(tmp, T_WORD, 0);
	return (i + quote + j);
}

int quote_handler(char **line, int i)
{
	char	*tmp;
	int		j;
	int		quote;

	quote = 0;
	j = 0;
	while ((*line)[i + j] && ((quote % 2) || (*line)[i + j] != ' '))
		if ((*line)[i + j++] == '\'')
			quote++;
	if ((quote % 2))
	{
		(*line) = read_until_chr(*line, '\'');
		new_arg(0, 0, -1);
		return (quote_handler(line, i));
		// return (0);
	}
	tmp = ft_calloc(sizeof(char), (j - quote + 1));
	quote = 0;
	j = 0;
	while ((*line)[i + quote + j] && ((quote % 2) || (*line)[i + quote + j] != ' '))
	{
		if ((*line)[i + quote + j] == '\'')
		{
			quote++;
			continue ;
		}
		tmp[j] = (*line)[i + quote + j];
		j++;
	}
	new_arg(tmp, T_WORD, 0);
	return (i + quote + j);
}

char	**spliter(char *line)
{
	char	**splited;
	int		i;
	int		j;

	i = 0;
	splited = NULL;
	while (line[i])
	{
		j = 0;
		while (line[i + j] && line[i + j] != ' ')
		{
			if (line[i + j] == '\"')
			{
				i  = dquote_handler(&line, i);
				break ;
			}
			if (line[i + j] == '\'')
			{
				i = quote_handler(&line, i);
				break ;
			}
			j++;
		}
		j = 0;
		while (line[i + j] && line[i + j] != ' ' && line[i + j] != '\"' && line[i + j] != '\'')
			j++;
		printf("%d %c\n", line[i + j], line[i + j]);
		if (j)
		{
			new_arg(ft_substr(line, i, j), 0, 0);
			i += j;
		}
		if (line[i] && line[i] == ' ')
			i++;
	}
	// if (!ref)
	// {
	// 	set_splited(0, -1, 0);
	// 	splited = spliter(line, 1);
	// 	free(line);
	// }
	return (NULL);
}
