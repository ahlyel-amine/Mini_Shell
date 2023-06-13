/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_parser.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 20:14:00 by aahlyel           #+#    #+#             */
/*   Updated: 2023/06/13 00:51:59 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	t_free(char **line, int *i)
{
	free(*line);
	*i = -1;
}

static t_cmd	*get_redirection(char *line, int i, int type)
{
	char			*before;
	char			*after;
	t_cmd			*redirection;
	int				tmp;
	t_redir_content	red;

	redirection = NULL;
	before = NULL;
	after = NULL;
	tmp = i;
	if (i - 1 > 0)
		before = ft_substr(line, 0, i);
	tmp = fill_redir_content(line, i, &red, type);
	if (tmp > i)
		after = ft_substr(line, tmp, ft_strlen(line + tmp));
	if (before || after)
		redirection = redirections_parser(ft_strjoin_free(before, after));
	redirection = redir_constructor(redirection, red);
	return (redirection);
}

static t_cmd	*check_for_redirections(char *line, int i)
{
	int		j;
	t_cmd	*redirection;
	int		space;

	j = 0;
	space = 0;
	redirection = NULL;
	if (line[i] == '<' && line[i + 1] == '<')
		redirection = get_redirection(line, i, F_HEREDOC);
	else if (line[i] == '<')
		redirection = get_redirection(line, i, F_IN_RED);
	else if (line[i] == '>' && line[i + 1] == '>')
		redirection = get_redirection(line, i, F_APPEND);
	else if (line[i] == '>')
		redirection = get_redirection(line, i, F_OUT_RED);
	return (redirection);
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
