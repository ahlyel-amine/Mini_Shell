/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_parser.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 20:14:00 by aahlyel           #+#    #+#             */
/*   Updated: 2023/06/12 17:34:19 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	t_free(char **line, int *i)
{
	free(*line);
	*i = -1;
}

t_cmd	*redirections_parser(char *line)
{
	t_cmd			*redirection;
	int				i;
	t_var			var;

	if (!line)
		return (NULL);
	ft_memset(&var, 0, sizeof(t_var));
	redirection = NULL;
	i = -1;
	while (line[++i])
	{
		check_out_of_quotes(line[i], &var);
		if (!check_for_syntax(&line, i))
			return (NULL);
		if (!var.quote && !var.dquote)
			redirection = check_for_redirections(line, i);
		if (redirection)
		{
			t_free(&line, &i);
			break ;
		}
	}
	if (i != -1)
		redirection = executable_parser(line);
	return (redirection);
}
