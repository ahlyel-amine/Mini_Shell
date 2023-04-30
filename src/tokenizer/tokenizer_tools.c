/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_tools.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 12:40:17 by aahlyel           #+#    #+#             */
/*   Updated: 2023/04/30 16:08:01 by aahlyel          ###   ########.fr       */
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

char	*quotes(char *line, int i)
{
	int		k;
	int		quote;
	int		dquote;
	char	*tmp;

	tmp = malloc(ft_strlen(line + i) + 1);
	quote = 0;
	dquote = 0;
	k = 0;
	while (line[i])
	{
		if (line[i] == '\"' && !quote)
			dquote++;
		else if (line[i] == '\'' && !dquote)
			quote++;
		if (dquote == 2)
			dquote = 0;
		else if (quote == 2)
			quote = 0;
		while (ft_isspace(line[i]) && ft_isspace(line[i + 1]) && !quote && !dquote)
			i++;
		if (ft_isspace(line[i]) && !line[i + 1])
		{
			i++;
			continue ;
		}
		if (!quote && !dquote && ft_isspace(line[i]))
			tmp[k++] = line[i];
		else if ((line[i] == '\"' && quote) || (line[i] == '\'' && dquote))
			tmp[k++] = line[i];
		else if (line[i] == '$' && (dquote || (!dquote && !quote)))
		{
			if (ft_isdigit(line[i + 1]))
				i += 2;
			else if (line[i] == '$' && !line[i + 1])
				i++;
			else if (line[i] == '$')
			{
				i++;
				tmp[k++] = '\"';
				while (ft_isalnum(line[i]) || line[i] == '_')
					tmp[k++] = line[i++];
			}
			continue ;
		}
		else if (line[i] != '\'' && line[i] != '\"')
			tmp[k++] = line[i];
		i++;
	}
	tmp[k] = 0;
	return (tmp);
}
