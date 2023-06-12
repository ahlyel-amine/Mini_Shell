/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_parser_tools3.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 18:04:58 by aahlyel           #+#    #+#             */
/*   Updated: 2023/06/12 18:17:20 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	fill_red_content(t_redir_content *red, int ref)
{
	red->fd = 0;
	red->mode = 0;
	if (ref == F_HEREDOC)
		red->type = HEREDOC;
	else if (ref == F_IN_RED)
		red->type = IN_REDIR;
	else if (ref == F_APPEND)
	{
		red->fd = 1;
		red->mode = (O_APPEND | O_WRONLY | O_CREAT);
		red->type = APPEND;
	}
	else if (ref == F_OUT_RED)
	{
		red->fd = 1;
		red->mode = O_TRUNC | O_WRONLY | O_CREAT;
		red->type = OUT_REDIR;
	}
}

int	fill_redir_content(char *line, int i, t_redir_content *red, int ref)
{
	int		j;
	t_var	var;

	ft_memset(&var, 0, sizeof(t_var));
	j = 0;
	i = i + (ref >> 1);
	red->file_name = NULL;
	while (ft_isspace(line[i]))
		i++;
	red->fd = i;
	i = get_name(line, red, ref);
	fill_red_content(red, ref);
	return (i);
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

t_cmd	*check_for_redirections(char *line, int i)
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

int	check_for_syntax(char **line, int i)
{
	int	j;
	int	space;

	j = 0;
	space = 0;
	if (((*line)[i] == '<' && (*line)[i + 1] == '>'))
			return (panic_recursive(ERR_O_SNTX, line), 0);
	if (((*line)[i] == '<' && (*line)[i + 1] == '<') || ((*line)[i] == '>'
			&& (*line)[i + 1] == '>') || ((*line)[i] == '<')
		|| ((*line)[i] == '>'))
	{
		j++;
		if ((*line)[i + 1] == '<' || (*line)[i + 1] == '>')
			j++;
		while (ft_isspace((*line)[i + j + space]))
			space++;
		if (!(*line)[i + j + space] || (*line)[i + j + space] == '<'
			|| (*line)[i + j + space] == '>')
			return (panic_recursive(ERR_O_SNTX, line), 0);
	}
	return (1);
}
