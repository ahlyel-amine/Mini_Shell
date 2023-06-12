/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_before_parenthesis.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 17:32:12 by aahlyel           #+#    #+#             */
/*   Updated: 2023/06/12 17:34:57 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_cmd	*check_redirect_herdoc(char **line, int i, int *quit)
{
	t_cmd			*operator;
	t_redir_content	red;
	int				k;

	*quit = 0;
	operator = NULL;
	if ((*line)[i] == '<' && (*line)[i + 1] == '<')
	{
		k = i;
		i += 2;
		i += skip_spaces_front((*line) + i);
		while (isalnum((*line)[i]) || (*line)[i] == '_')
			i++;
		i += skip_spaces_front((*line) + i);
		if ((*line)[i] == '(')
		{
			i = k;
			k = fill_redir_content((*line), k, &red, F_HEREDOC);
			operator = redir_constructor(invalid_constructor(ft_substr((*line), \
			k, ft_strlen((*line) + k))), red);
			return (free ((*line)), (*line) = NULL, *quit = -1, NULL);
		}
		*quit = 1;
	}
	return (operator);
}

void	check_redirect_inred(char **line, int i, int *quit)
{
	*quit = 0;
	if ((*line)[i] == '<')
	{
		i++;
		i += skip_spaces_front((*line) + i);
		while (isalnum((*line)[i]) || (*line)[i] == '_')
			i++;
		i += skip_spaces_front((*line) + i);
		if ((*line)[i] == '(')
		{
			pr_custom_err(ERR_SNTX, (*line), (*line) + i);
			(*line) = NULL;
			*quit = -1;
			return ;
		}
		*quit = 1;
	}
}
