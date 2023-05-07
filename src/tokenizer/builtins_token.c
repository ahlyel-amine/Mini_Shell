/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 12:31:34 by aahlyel           #+#    #+#             */
/*   Updated: 2023/05/07 22:43:31 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int check_nl_option(char *line, int i, int j)
{
	if (line[i + j] == '-' && line[i + j + 1] == 'n')
	{
		j++;
		while (line[i + j] == 'n')
			j++;
	}
	else if (line[i + j] == '\"' && line[i + j + 1] == '-' && line[i + j + 2] == 'n')
	{
		j += 2;
		while (line[i + j] == 'n')
			j++;
		if (line[i + j] == '\"')
			j++;
	}
	else if (line[i + j] == '\'' && line[i + j + 1] == '-' && line[i + j + 2] == 'n')
	{
		j += 2;
		while (line[i + j] == 'n')
			j++;
		if (line[i + j] == '\'')
			j++;
	}
	return (j);
}

static int	echo_has_option(char *line, int *i)
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
		j = check_nl_option(line, *i, j);
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

t_cmd	*call_builtin_constructor(char *quote, char *builtin)
{
	t_cmd	*cmd;

	cmd = builtin_constructor(ft_strdup(builtin), 0, quote);
	return (cmd);
}

t_cmd	*search_for_builtin(char *tmp, char *quote)
{
	t_cmd	*cmd;

	cmd = NULL;
	if (!ft_strncmp(tmp, "cd", 3))
		cmd = call_builtin_constructor(quote, "cd");
	else if (!ft_strncmp(tmp, "pwd", 4))
		cmd = call_builtin_constructor(quote, "pwd");
	else if (!ft_strncmp(tmp, "unset", 6))
		cmd = call_builtin_constructor(quote, "unset");
	else if (!ft_strncmp(tmp, "env", 4))
		cmd = call_builtin_constructor(quote, "env");
	else if (!ft_strncmp(tmp, "export", 7))
		cmd = call_builtin_constructor(quote, "export");
	else if (!ft_strncmp(tmp, "exit", 5))
		cmd = call_builtin_constructor(quote, "exit");
	else
		free(quote);
	return (cmd);
}

t_cmd	*get_token_builtins(char *line, int j)
{
	t_cmd	*cmd;
	char	*tmp;
	char	*quote;
	int		space;
	int		i;

	cmd = NULL;
	space  = skip_spaces_front(line + j);
	tmp = ft_substr(line, 0, j);

	quote = skip_quotes(line, NULL, j + space, 0);
	if (!ft_strncmp(tmp, "echo", 5))
	{
		space = echo_has_option(line + j, &i);
		cmd = builtin_constructor(ft_strdup("echo"), \
		space, skip_quotes(line, NULL, j + i, 0));
		free (quote);
	}
	else
		cmd = search_for_builtin(tmp, quote);
	return (free (line), free(tmp), cmd);
}
