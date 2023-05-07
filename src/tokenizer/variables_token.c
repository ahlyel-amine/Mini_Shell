/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables_token.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 12:31:51 by aahlyel           #+#    #+#             */
/*   Updated: 2023/05/07 19:32:44 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	check_is_assignement(char *line, int *value)
{
	int	i;
	t_var	var;

	set_zero_var(&var);
	i = 0;
	while (line[i] && line[i] != '=' && line[i] != '\'' && line[i] != '\"')
		i++;
	if (line[i] != '=')
		return (0);
	i++;
	*value = i;
	while (line[i] && line[i] != '$' && line[i] != '&' && line[i] != '|'
	&& (!ft_isspace(line[i]) || (var.quote || var.dquote)))
	{
		check_out_of_quotes(line[i], &var);
			i++;
	}
	while (ft_isspace(line[i]))
		i++;
	if (!line[i])
		return (1);
	return (0);
}

t_cmd	*get_token_variable_assignement(char *line)
{
	t_cmd	*cmd;
	char	*tmp;
	int		value;

	cmd = NULL;
	tmp = NULL;
	value = 0;
	if (!check_is_assignement(line, &value))
	{
		if (*line)
		{
			ft_putendl_fd("minishell:  dsdfghj: command not found tkherbi9", 2);
			free (line);
			return (NULL);
			// cmd = invalid_constructor(ft_strdup(line));
		}
	}
	else
	{
		tmp = ft_substr(line, value, ft_strlen(line + value));
		cmd = assignement_constructor(ft_substr(line, 0, value), skip_quotes(tmp, NULL, 0, 0));
		free (tmp);
	}
	return (free(line), cmd);
}