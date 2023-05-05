/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 12:31:46 by aahlyel           #+#    #+#             */
/*   Updated: 2023/05/04 21:37:20 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_cmd	*get_token_operator_pipe(char *line)
{
	t_cmd	*pipe_line;
	int		i;
	int		operator_pipe;
	t_var	var;
	char	*tmp;

	set_zero_var(&var);
	i = -1;
	operator_pipe = 0;
	while (line[++i])
	{
		check_out_of_quotes(line[i], &var);
		if (!var.quote && !var.dquote && line[i] == '|')
		{
			operator_pipe = 1;
			tmp = ft_substr_skip_space(line, 0, i);
			if (!*tmp)
			{
				free (tmp);
				free (line);
				ft_putendl_fd("minishell: syntax error near unexpected token `|'\n", 2);
				return (NULL);
			}
			else
			{
				pipe_line = get_token_operator_pipe(tmp);
				if (pipe_line)
				pipe_line = pipe_constructor(pipe_line,
				get_token_operator_pipe(ft_substr(line, i + 1, ft_strlen(line + i + 1))));
			}
			free (line);
			break ;
		}
	}
	if (!operator_pipe)
	{
		pipe_line = get_token_redir(remove_unused_parenthesis(ft_strdup(line)));
		free (line);
	}
	return (pipe_line);
}
