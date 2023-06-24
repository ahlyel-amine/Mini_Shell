/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spliter.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbrahm <aelbrahm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 05:57:23 by aahlyel           #+#    #+#             */
/*   Updated: 2023/06/24 18:33:04 by aelbrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "archive.h"

int	count_arguments(char *line)
{
	int	i;
	int	quote;
	int	dquote;
	int counter;

	counter = 0;
	dquote = 0;
	quote = 0;
	i = 0;
	while (line[i])
	{
		while (ft_isspace(line[i]))
			i++;
		check_out_of_quotes(line[i], &quote, &dquote);
		while (line[i] && !quote && !dquote && !ft_isspace(line[i]))
		{
			check_out_of_quotes(line[i], &quote, &dquote);
			i++;
		}
		if (ft_isspace(line[i]) || !line[i])
				counter++;
		else if (quote)
		{
			while (line[i] != '\'')
				i++;
			if (ft_isspace(line[i]) || !line[i])
				counter++;
		}
		else if (dquote)
		{
			while (line[i] != '\"')
				i++;
			if (line[i] == '\"')
				i++;
			if (ft_isspace(line[i]) || !line[i])
				counter++;
		}
	}
	return (counter);
}

char	**select_arguments(char *line, int count)
{
	int		i;
	int		quote;
	int		dquote;
	int 	j;
	char	**cmd;

	cmd = malloc(sizeof (char *) * (count + 1));
	cmd[count] = NULL;
	count = 0;
	quote = 0;
	dquote = 0;
	i = 0;
	j = 0;

	while (line[i + j])
	{
		while (ft_isspace(line[i + j]))
			j++;
		check_out_of_quotes(line[i + j], &quote, &dquote);
		while (line[i + j] && !quote && !dquote && !ft_isspace(line[i + j]))
		{
			check_out_of_quotes(line[i + j], &quote, &dquote);
			j++;
		}
		if (ft_isspace(line[i + j]) || !line[i + j])
		{
			cmd[count++] = ft_substr(line, i, j);
			i += j;
		}
		else if (quote)
		{
			while (line[i + j] != '\'')
				j++;
			if (ft_isspace(line[i + j]) || !line[i + j])
			{
				cmd[count++] = ft_substr(line, i, j);
				i += j;
			}
		}
		else if (dquote)
		{
			while (line[i + j] != '\"')
				j++;
			if (line[i + j] == '\"')
				j++;
			if (ft_isspace(line[i + j]) || !line[i + j])
			{
				cmd[count++] = ft_substr(line, i, j - 1);
				i += j;
			}
		}
		j = 0;
	}
	j = 0;
	return (cmd);
}

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
	splited[call_count - 1] = line;
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
		set_splited(0, -1, 0);
		splited = spliter(line, 1);
		free(line);
	}
	return (set_splited(0, -2, 0));
}

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
		if (!dquote)
		{
			new_arg(0, 0, -1);
			ft_putendl_fd("unexpected EOF while looking for matching \"\'", 2);
			ft_putendl_fd("minishell: syntax error: unexpected end of file", 2);
			return (NULL);
		}
		line = ft_strjoin(line, ft_strdup("\n"));
		line = ft_strjoin(line, dquote);
		quote_pos = ft_chrpos(line, c);
		if (quote_pos != -1)
			break ;
	}
	return (line);
}
char	*get_variables(char *line, int ref)
{
	int		i;
	int		k;
	int		call_count = 0;

	i = 0;
	while (line[i])
	{
		k = 0;
		if (line[i + k] == '$')
		{
			k++;
			if (ft_isdigit(line[i + k]))
			{
				line = ft_strjoin_free(ft_substr(line, 0, i), ft_substr(line, i + 2, ft_strlen(line + i + 2)));
				i = 0;
				continue ;
			}
		}
		i++;
	}
	i = 0;
	while (line[i])
	{
		k = 0;
		if (line[i + k] == '$')
		{
			k++;
			while (line[i + k] && (ft_isalnum(line[i + k]) || line[i + k] == '_'))
				k++;
			if (k > 1)
			{
				set_splited(ft_substr(line, 0, i), ref, ++call_count);
				set_splited(ft_substr(line, i, k), ref, ++call_count);
				line = ft_substr(line, i + k, ft_strlen(line + i + k));
				set_splited(ft_strdup(line), ref, ++call_count);
				i = 0;
				continue ;
			}
		}
		i++;
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
	while ((*line)[i + j] && ((quote % 2) || !ft_isspace((*line)[i + j])))
		if ((*line)[i + j++] == '\'')
			quote++;
	tmp = ft_calloc(sizeof(char), (j - quote + 1));
	quote = 0;
	j = 0;
	while ((*line)[i + quote + j] && ((quote % 2) || !ft_isspace((*line)[i + quote + j])))
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

int dquote_handler(char **line, int i)
{
	char	*tmp;
	int		j;
	int		quote;
	int		k;

	quote = 0;
	j = 0;
	while ((*line)[i + j] && ((quote % 2) || !ft_isspace((*line)[i + j])))
		if ((*line)[i + j++] == '\"')
			quote++;
	j = 0;
	quote = 0;
	while ((*line)[i + j] && (!ft_isspace((*line)[i + j]) || (quote % 2)))
	{
		if ((*line)[i + j] == '$')
		{
			if (ft_isdigit((*line)[i + j + 1]))
			{
				*line = ft_strjoin_free(ft_substr(*line, 0, i + j), ft_substr(*line, i + j + 2, ft_strlen(*line + i + j + 2)));
				continue ;
			}
		}
		if ((*line)[i + j] == '\"')
			quote++;
		j++;
	}
	j = 0;
	quote = 0;
	while ((*line)[i + j] && (!ft_isspace((*line)[i + j]) || (quote % 2)))
	{
		k = 0;
		if ((((*line)[i + j] == '$') && (!(*line)[i + j + 1] || (!ft_isalnum((*line)[i + j + 1]) && (*line)[i + j + 1] != '_'))))
		{
			new_arg(ft_substr(*line, i + j, 1), T_WORD, 0);
			j++;
			continue ;
		}
		if ((*line)[i + j] == '$')
		{
			k++;
			while ((*line)[i + j + k] && (ft_isalnum((*line)[i + j + k]) || (*line)[i + j + k] == '_'))
				k++;
			if (k > 1)
			{
				new_arg(ft_substr(*line, i + j, k), T_VARIABLE, 0);
				j += k;
				continue ;
			}
		}
		while ((*line)[i + j] && (*line)[i + j] == '\"')
		{
			quote++;
			j++;
		}
		if (!(*line)[i + j])
			continue ;
		tmp = ft_calloc(sizeof(char), ft_strlen(*line + i + j));
		while ((*line)[i + j] && (!ft_isspace((*line)[i + j]) || (quote % 2)) && (*line)[i + j] != '$')
		{
			if ((*line)[i + j] == '\"')
			{
				quote++;
				j++;
				continue ;
			}
			tmp[k] = (*line)[i + j++];
			k++;
		}
		if (k)
			new_arg(ft_strdup(tmp), T_WORD, 0);
		free(tmp);
	}
	return (i + j);
}

int	nonquote_handler(char *line, int i)
{
	int	j;

	j = 0;
	while (line[i + j] && !ft_isspace(line[i + j]) && line[i + j] != '\"' && line[i + j] != '\'')
		j++;
	if (j)
	{
		new_arg(ft_substr(line, i, j), T_WORD, 0);
		i += j;
	}
	while (line[i] && ft_isspace(line[i]))
		i++;
	return (i);
}

void	spliter(char *line)
{
	int		i;
	int		j;

	i = 0;
	while (line[i])
	{
		j = 0;
		while (line[i + j] && !ft_isspace(line[i + j]))
		{
			if (line[i + j] == '\"')
			{
				i = dquote_handler(&line, i);
				if (i == -1)
					return ;
				continue ;
			}
			if (line[i + j] == '\'')
			{
				i = quote_handler(&line, i);
				if (i == -1)
					return ;
				continue ;
			}
			j++;
		}
			j = 0;
		while (line[i + j] && !ft_isspace(line[i + j]) && line[i + j] != '\"' && line[i + j] != '\'')
			j++;
		if (j)
		{
			new_arg(ft_substr(line, i, j), T_WORD, 0);
			i += j;
		}
		while (line[i] && ft_isspace(line[i]))
			i++;
		// i = nonquote_handler(line, i);
	}
}
