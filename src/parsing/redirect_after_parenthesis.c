/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_after_parenthesis.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 17:31:07 by aahlyel           #+#    #+#             */
/*   Updated: 2023/06/12 17:32:49 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_cmd	*check_redirect_append(char **line, int i, t_var var, int *quit)
{
	t_redir_content	red;
	t_cmd			*operator;
	int				k;

	*quit = 0;
	operator = NULL;
	if ((*line)[i] == '>' && (*line)[i + 1] == '>' && !var.quote && !var.dquote)
	{
		if (!check_for_syntax(line, i))
		{
			*quit = -1;
			return (operator);
		}
		k = fill_redir_content(*line, i, &red, F_APPEND);
		operator = and_parser(\
			ft_strjoin_free(remove_unused_parenthesis(ft_substr(*line, 0, i)), \
			ft_substr(*line, k, ft_strlen(*line + k))));
		operator = redir_constructor(operator, red);
		free (*line);
		*line = NULL;
		*quit = 1;
	}
	return (operator);
}

t_cmd	*check_redirect_herdoc_after(char **line, int i, t_var var, int *quit)
{
	t_redir_content	red;
	t_cmd			*operator;
	int				k;

	*quit = 0;
	operator = NULL;
	if ((*line)[i] == '<' && (*line)[i + 1] == '<' && !var.quote && !var.dquote)
	{
		if (!check_for_syntax(line, i))
		{
			*quit = -1;
			return (operator);
		}
		k = fill_redir_content(*line, i, &red, F_HEREDOC);
		operator = and_parser(\
			ft_strjoin_free(remove_unused_parenthesis(ft_substr(*line, 0, i)), \
			ft_substr(*line, k, ft_strlen(*line + k))));
		operator = redir_constructor(operator, red);
		free (*line);
		*line = NULL;
		*quit = 1;
	}
	return (operator);
}

t_cmd	*check_redirect_outred(char **line, int i, t_var var, int *quit)
{
	t_redir_content	red;
	t_cmd			*operator;
	int				k;

	operator = NULL;
	*quit = 0;
	if ((*line)[i] == '>' && !var.quote && !var.dquote)
	{
		if (!check_for_syntax(line, i))
		{
			*quit = -1;
			return (operator);
		}
		k = fill_redir_content(*line, i, &red, F_OUT_RED);
		operator = and_parser(\
			ft_strjoin_free(remove_unused_parenthesis(ft_substr(*line, 0, i)), \
			ft_substr(*line, k, ft_strlen(*line + k))));
		operator = redir_constructor(operator, red);
		free (*line);
		*line = NULL;
		*quit = 1;
	}
	return (operator);
}

t_cmd	*check_redirect_inred_after(char **line, int i, t_var var, int *quit)
{
	t_redir_content	red;
	t_cmd			*operator;
	int				k;

	operator = NULL;
	*quit = 0;
	if ((*line)[i] == '<' && !var.quote && !var.dquote)
	{
		if (!check_for_syntax(line, i))
		{
			*quit = -1;
			return (operator);
		}
		k = fill_redir_content(*line, i, &red, F_IN_RED);
		operator = and_parser(\
			ft_strjoin_free(remove_unused_parenthesis(ft_substr(*line, 0, i)), \
			ft_substr(*line, k, ft_strlen(*line + k))));
		operator = redir_constructor(operator, red);
		free (*line);
		*line = NULL;
		*quit = 1;
	}
	return (operator);
}
