/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 12:31:34 by aahlyel           #+#    #+#             */
/*   Updated: 2023/04/27 12:39:15 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	echo_has_option(char *line, int *i)
{
	int	has_option;
	int	j;

	*i = 0;
	has_option = 0;
	while (line[*i])
	{
		while (ft_isspace(line[*i]))
			(*i)++;
		j = 0;
		if (line[*i + j] == '-' && line[*i + j + 1] == 'n')
		{
			j++;
			while (line[*i + j] == 'n')
				j++;
		}
		else if (line[*i + j] == '\"' && line[*i + j + 1] == '-' && line[*i + j + 2] == 'n')
		{
			j += 2;
			while (line[*i + j] == 'n')
				j++;
			if (line[*i + j] == '\"')
				j++;
		}
		else if (line[*i + j] == '\'' && line[*i + j + 1] == '-' && line[*i + j + 2] == 'n')
		{
			j += 2;
			while (line[*i + j] == 'n')
				j++;
			if (line[*i + j] == '\'')
				j++;
		}
		if (ft_isspace(line[*i + j]) || !line[*i + j])
		{
			has_option = 1;
			*i += j;
		}
		else
			break ;
	}
	return (has_option);
}

t_cmd	*get_token_builtins(char *line, int i, int j)
{
	t_cmd *cmd= NULL;
	int has_option = 0;
	if (!ft_strncmp(ft_substr(line + i, 0, j), "echo", 5))
	{
		has_option = echo_has_option(line + i + j, &i);
		cmd = builtin_constructor(ft_strdup("echo"), \
		has_option, quotes(line, i + j));
		echo(cmd);
	}
	else if (!ft_strncmp(ft_substr(line + i, 0, j), "cd", 3))
	{
		cmd = builtin_constructor(ft_strdup("cd"), \
		has_option, quotes(line, i + j));
	}
	else if (!ft_strncmp(ft_substr(line + i, 0, j), "pwd", 4))
	{
		cmd = builtin_constructor(ft_strdup("pwd"), \
		has_option, quotes(line, i + j));
	}
	else if (!ft_strncmp(ft_substr(line + i, 0, j), "unset", 6))
	{
		cmd = builtin_constructor(ft_strdup("unset"), \
		has_option, quotes(line, i + j));
	}
	else if (!ft_strncmp(ft_substr(line + i, 0, j), "env", 4))
	{
		cmd = builtin_constructor(ft_strdup("env"), \
		has_option, quotes(line, i + j));
	}
	else if (!ft_strncmp(ft_substr(line + i, 0, j), "export", 7))
	{
		cmd = builtin_constructor(ft_strdup("export"), \
		has_option, quotes(line, i + j));
	}
	else if (!ft_strncmp(ft_substr(line + i, 0, j), "exit", 5))
	{
		cmd = builtin_constructor(ft_strdup("exit"), \
		has_option, quotes(line, i + j));
	}
	return (cmd);
}