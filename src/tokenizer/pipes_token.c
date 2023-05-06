/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 12:31:46 by aahlyel           #+#    #+#             */
/*   Updated: 2023/05/06 21:15:06 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static t_cmd	*check_for_pipe(char *line, int i, int *operator_pipe, t_var var);

t_cmd	*get_token_operator_pipe(char *line)
{
	t_cmd	*pipe_line;
	int		i;
	int		operator_pipe;
	t_var	var;

	set_zero_var(&var);
	operator_pipe = 0;
	i = 0;
	while (line[i])
	{
		check_out_of_quotes(line[i], &var);
		pipe_line = check_for_pipe(line, i++, &operator_pipe, var);
		if (pipe_line)
			break ;
	}
	if (!operator_pipe)
	{
		pipe_line = get_token_redir(remove_unused_parenthesis(ft_strdup(line)));
		free (line);
	}
	return (pipe_line);
}

static t_cmd	*check_for_pipe(char *line, int i, int *operator_pipe, t_var var)
{
	t_cmd	*pipe_line;
	char	*tmp;

	pipe_line = NULL;
	if (!var.quote && !var.dquote && line[i] == '|')
	{
		*operator_pipe = 1;
		tmp = ft_substr_skip_space(line, 0, i);
		if (!*tmp)
			return (free(tmp), panic_recursive(ERR_PIPE, line), NULL);
		else
		{
			pipe_line = get_token_operator_pipe(tmp);
			if (pipe_line)
				pipe_line = pipe_constructor(pipe_line, \
				get_token_operator_pipe(ft_substr(line, i + 1, ft_strlen(line + i + 1))));
		}
		free (line);
	}
	return (pipe_line);
}
