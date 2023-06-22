/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complete_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 12:52:14 by aahlyel           #+#    #+#             */
/*   Updated: 2023/06/20 16:14:57 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

typedef struct s_oper
{
	int		and;
	int		or;
	int		pipe;
}	t_oper;

static char	*read_until_chr(char *line, char c, int *brea)
{
	char	*dquote;
	int		quote_pos;

	*brea = 0;
	while (1337)
	{
		if (c == '\'')
			dquote = readline(CMPLTQUOTE);
		else
			dquote = readline(CMPLTDQUOTE);
		if (!dquote)
		{
			ft_putstr_fd(ERR_UNXPTD_EOF, 2);
			ft_putstr_fd(ERR_FOUND_EOF, 2);
			*brea = 1;
			return (line);
		}
		line = ft_strjoin_free(line, ft_strdup("\n"));
		line = ft_strjoin_free(line, dquote);
		quote_pos = ft_chrpos(line, c);
		if (quote_pos != -1)
			break ;
	}
	return (line);
}

static char	*read_until_oper(char *line, t_oper oper, int *brea)
{
	char	*operator;

	*brea = 0;
	operator = NULL;
	if (oper.and)
		operator = readline(CMDAND);
	else if (oper.or)
		operator = readline(CMDOR);
	else if (oper.pipe)
		operator = readline(CMDPIPE);
	if (!operator)
	{
		ft_putstr_fd(ERR_FOUND_EOF, 2);
		*brea = 1;
		return (line);
	}
	line = ft_strjoin_free(line, ft_strdup(" "));
	line = ft_strjoin_free(line, operator);
	return (line);
}

static int	only_spaces_left(char *line)
{
	int	i;

	i = 0;
	while (ft_isspace(line[i]))
		i++;
	if (!line[i])
		return (1);
	return (0);
}

static void	get_is_complete(char *line, t_var *q, t_oper *oper)
{
	int		i;
	t_var	var;

	i = 0;
	ft_memset(&var, 0, sizeof(t_var));
	while (line[i])
	{
		check_out_of_quotes(line[i], &var);
		if (line[i] == '\"' && !(q->quote))
			(q->dquote) = !(q->dquote);
		if (line[i] == '\'' && !(q->dquote))
			(q->quote) = !(q->quote);
		if (!var.quote && !var.dquote && line[i] == '&' && line[i + 1] == '&'
			&& only_spaces_left(line + i + 2))
			oper->and = 1;
		else if (!var.quote && !var.dquote && line[i] == '|' && \
		line[i + 1] == '|' && only_spaces_left(line + i + 2))
			oper->or = 1;
		else if (!var.quote && !var.dquote && line[i] == '|'
			&& only_spaces_left(line + i + 1))
			oper->pipe = 1;
		i++;
	}
}

void	complete_line(char **line, int *brea)
{
	t_var	q;
	t_oper	oper;
	int		bre;

	ft_memset(&q, 0, sizeof(t_var));
	ft_memset(&oper, 0, sizeof(t_oper));
	if (!line || !*line)
		return ;
	get_is_complete(*line, &q, &oper);
	if (q.dquote)
		*line = read_until_chr(*line, '\"', &bre);
	else if (q.quote)
		*line = read_until_chr(*line, '\'', &bre);
	else if (oper.and || oper.or || oper.pipe)
		*line = read_until_oper(*line, oper, &bre);
	else
		return ;
	if (bre)
	{
		*brea = 1;
		return ;
	}
	complete_line(line, brea);
}
