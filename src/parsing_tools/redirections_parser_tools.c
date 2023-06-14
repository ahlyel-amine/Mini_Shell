/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_parser_tools.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 15:39:50 by aahlyel           #+#    #+#             */
/*   Updated: 2023/06/14 22:34:31 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	skip_quote_heredoc_delimiter_conditions(char *line, \
char **tmp, t_2ptr_int a, t_var var)
{
	if (ft_isspace(line[*(a.i)]) && !var.quote && !var.dquote)
		return (1);
	if ((var.quote || var.dquote) && ft_isspace(line[*(a.i)]))
		(*tmp)[(*(a.k))++] = line[*(a.i)];
	else if ((line[*(a.i)] == '\"' && var.quote) || (line[*(a.i)] == '\''\
			&& var.dquote))
		(*tmp)[(*(a.k))++] = line[*(a.i)];
	else if (!var.quote && !var.dquote && !ft_isvariable(line[*(a.i)])
		&& line[*(a.i)] != '\"' && line[*(a.i)] != '\'')
		return (1);
	else if (line[*(a.i)] != '\'' && line[*(a.i)] != '\"')
		(*tmp)[(*(a.k))++] = line[*(a.i)];
	return (0);
}

char	*skip_quote_heredoc_delimiter(char *line, int *j, int i, int *q)
{
	int		k;
	char	*tmp;
	t_var	var;

	ft_memset(&var, 0, sizeof(t_var));
	tmp = ft_calloc(1, ft_strlen(line + i) + 1);
	k = 0;
	*q = 0;
	if (line[i] == '$' && (line[i + 1] == '\'' || line[i + 1] == '\"'))
		i++;
	while (line[i])
	{
		check_out_of_quotes(line[i], &var);
		if (var.dquote || var.quote)
			*q = 1;
		if (skip_quote_heredoc_delimiter_conditions(line, &tmp, \
		(t_2ptr_int){&i, &k}, var))
			break ;
		i++;
	}
	*j = i;
	return (tmp);
}

char	*skip_quote_heredoc_delimiters(char *line, char *end_line, int *q)
{
	int		i;
	int		k;
	char	*tmp;
	t_var	var;
	i = 0;
	ft_memset(&var, 0, sizeof(t_var));
	tmp = ft_calloc(1, (end_line - line) + 1);
	k = 0;
	*q = 0;
	if (line[i] == '$' && (line[i + 1] == '\'' || line[i + 1] == '\"'))
		i++;
	while (line[i] && line + i != end_line)
	{
		check_out_of_quotes(line[i], &var);
		if (var.dquote || var.quote)
			*q = 1;
		if (skip_quote_heredoc_delimiter_conditions(line, &tmp, \
		(t_2ptr_int){&i, &k}, var))
			break ;
		i++;
	}
	return (tmp);
}