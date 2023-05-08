/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_token.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 12:31:49 by aahlyel           #+#    #+#             */
/*   Updated: 2023/05/09 00:33:52 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*skip_quote_redir_names(char *line, int *j, int i)
{
	int		k;
	char	*tmp;
	t_var	var;

	set_zero_var(&var);
	tmp = ft_calloc(1, ft_strlen(line + i) + 1);
	k = 0;
	while (line[i])
	{
		check_out_of_quotes(line[i], &var);
		if (ft_isspace(line[i]) && !var.quote && !var.dquote)
			break ;
		if ((var.quote || var.dquote) && ft_isspace(line[i]))
			tmp[k++] = line[i];
		else if ((line[i] == '\"' && var.quote) || (line[i] == '\'' && var.dquote))
			tmp[k++] = line[i];
		else if (line[i] != '\'' && line[i] != '\"')
			tmp[k++] = line[i];
		i++;
	}
	*j = i;
	return (tmp);
}

static int	get_name(char *line, t_redir_content *red, int type)
{
	int	k;

	k = red->fd;
	if (type == F_HEREDOC)
		red->file_name = skip_quote_redir_names(line, &k, red->fd);
	else
		red->file_name = skip_quotes(line, &k, 0, 1);
	return (k);
}

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
		red->mode = O_APPEND | O_WRONLY | O_CREAT;
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
	int	j;
	t_var	var;

	set_zero_var(&var);
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
	char	*before;
	char	*after;
	t_cmd			*redirection;
	int	tmp;
	t_redir_content	red;
	redirection = NULL;
	before = NULL;
	after = NULL;
	
	tmp = i;
	if (i - 1 > 0)
		before = ft_substr(line, 0, i - 1);
	tmp = fill_redir_content(line, i, &red, type);
	if (tmp > i)
		after = ft_substr(line, tmp, ft_strlen(line + tmp));
	if (before || after)
		redirection = get_token_redir(ft_strjoin_free(before, after));
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

int	check_for_syntax(char *line, int i)
{
	int	j;
	int	space;

	j = 0;
	space = 0;
	if ((line[i] == '<' && line[i + 1] == '<')  || (line[i] == '>' && \
	line[i + 1] == '>') || (line[i] == '<') || (line[i] == '>'))
	{
		j++;
		if (line[i + 1] == '<' || line[i + 1] == '>')
			j++;
		while (ft_isspace(line[i + j + space]))
			space++;
		if (!line[i + j + space] || line[i + j + space] == '<' || line[i + j + space] == '>')
			return (panic_recursive("minishell : syntax error near unexpected token\n", line), 0);
	}
	return (1);
}

t_cmd	*get_token_redir(char *line)
{
	t_cmd			*redirection;
	int				i;
	t_var			var;

	set_zero_var(&var);
	redirection = NULL;
	i = 0;
	while (line[i])
	{
		check_out_of_quotes(line[i], &var);
		if (!check_for_syntax(line, i))
			return (NULL);
		if (!var.quote && !var.dquote)
			redirection = check_for_redirections(line, i);
		if (redirection)
		{
			i = -1;	
			break ;
		}
		i++;
	}
	if (i != -1)
		redirection = get_token_order(ft_strdup(line));
	free (line);
	return (redirection);
}
