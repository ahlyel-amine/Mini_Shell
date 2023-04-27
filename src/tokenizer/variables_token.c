/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables_token.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 12:31:51 by aahlyel           #+#    #+#             */
/*   Updated: 2023/04/27 12:34:35 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"


int	check_is_assignement(char *line, int *value)
{
	int	i;
	int	quote;
	int	dquote;

	i = 0;
	quote = 0;
	dquote = 0;
	(void)value;
	while (line[i] && line[i] != '=' && line[i] != '\'' && line[i] != '\"')
		i++;
	if (line[i] != '=')
		return (0);
	i++;
	*value = i;
	while (line[i] && line[i] != '$' && line[i] != '&' && line[i] != '|'
	&& (!ft_isspace(line[i]) || (quote || dquote)))
	{
		check_out_of_quotes(line[i], &quote, &dquote);
			i++;
		
	}
	while (ft_isspace(line[i]))
		i++;
	if (!line[i])
		return (1);
	return (0);
}

t_cmd	*get_token_variable_assignement(char *line, int j)
{
	t_cmd	*cmd;
	int		value;

	cmd = NULL;

	value = 0;
	(void)j;
	if (!check_is_assignement(line, &value))
		cmd = invalid_constructor(line);
	else
		cmd = assignement_constructor(ft_substr(line, 0, value),
			quotes(ft_substr(line, value, ft_strlen(line + value)), 0));
	return (free(line), cmd);
}