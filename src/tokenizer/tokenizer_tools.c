/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_tools.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 12:40:17 by aahlyel           #+#    #+#             */
/*   Updated: 2023/05/07 19:35:25 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../include/minishell.h"

void	something_wrong(char *error, void *to_free)
{
	free(to_free);
	ft_putendl_fd(error, 2);
	set__get_option_variables(0, FREE);
	exit(1);
}

void	check_out_of_quotes(char c, t_var *var)
{
	if (c == '\"' && !(var->quote))
			(var->dquote) = !(var->dquote);
	if (c == '\'' && !(var->dquote))
		(var->quote) = !(var->quote);
}
void	transform_dollar(char *line, int *i, int *k, char **tmp)
{
	if (ft_isdigit(line[*i + 1]))
		*i += 2;
	else if (line[*i] == '$' && (!line[*i + 1] || ft_isspace(line[*i + 1])))
		(*tmp)[(*k)++] = line[(*i)++];
	else if (line[*i] == '$' && line[*i + 1] == '$')
		(*tmp)[(*k)++] = line[(*i)++];
	else if (line[*i] == '$')
	{
		(*i)++;
		(*tmp)[(*k)++] = '\"';
		while (ft_isalnum(line[*i]) || line[*i] == '_')
			(*tmp)[(*k)++] = line[(*i)++];
		(*tmp)[(*k)++] = '\"';
	}
}

int	delete_quotes(char *line, char **tmp, int i, int is_word)
{
	t_var	var;
	int		k;

	k = 0;
	set_zero_var(&var);
	while (line[i])
	{
		check_out_of_quotes(line[i], &var);
		if (!var.quote && !var.dquote && ft_isspace(line[i]))
		{
			if (is_word)
				break ;
			(*tmp)[k++] = line[i];
		}
		else if ((line[i] == '\"' && var.quote) || (line[i] == '\'' && var.dquote))
			(*tmp)[k++] = line[i];
		else if (line[i] == '$' && (var.dquote || (!var.dquote && !var.quote)))
		{
			transform_dollar(line, &i, &k, tmp);
			continue ;
		}
		else if (line[i] != '\'' && line[i] != '\"')
			(*tmp)[k++] = line[i];
		i++;
	}
	return (i);
}

char	*skip_quotes(char *line, int *i, int j, int is_word)
{
	char	*tmp;
	int		a;

	if (is_word)
		tmp = ft_calloc(1, ft_strlen(line + *i) + 1);
	else
		tmp = ft_calloc(1, ft_strlen(line + j) + 1);
	if (!tmp)
		return (NULL);
	if (is_word)
		*i = delete_quotes(line, &tmp, *i, is_word);
	else
		delete_quotes(line, &tmp, j, is_word);
	return (tmp);
}

int	skip_spaces_front(char *line)
{
	int	i;

	i = 0;
	while (ft_isspace(line[i]))
		i++;
	return (i);
}

void	pr_custom_err(char *error, void *ptr, char *custom)
{
	char	*msg;

	msg = ft_strjoin(error, custom);
	ft_putendl_fd(msg, 2);
	ft_putchar_fd('\n', 2);
	free(msg);
	free (ptr);
}
void	panic_recursive(char *error, void *ptr)
{
	ft_putendl_fd(error, 2);
	free (ptr);
}