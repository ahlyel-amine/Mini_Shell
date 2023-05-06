/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_token.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 12:31:49 by aahlyel           #+#    #+#             */
/*   Updated: 2023/05/06 16:20:44 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*skip_quote_redir_names(char *line, int *j, int i)
{
	int		k;
	int		quote;
	int		dquote;
	char	*tmp;

	tmp = malloc(ft_strlen(line + i) + 1);
	quote = 0;
	dquote = 0;
	k = 0;
	while (line[i])
	{
		if (line[i] == '\"' && !quote)
			dquote++;
		else if (line[i] == '\'' && !dquote)
			quote++;
		if (dquote == 2)
			dquote = 0;
		else if (quote == 2)
			quote = 0;
		if (ft_isspace(line[i]) && !quote && !dquote)
			break ;
		if ((quote || dquote) && ft_isspace(line[i]))
			tmp[k++] = line[i];
		else if ((line[i] == '\"' && quote) || (line[i] == '\'' && dquote))
			tmp[k++] = line[i];
		else if (line[i] != '\'' && line[i] != '\"')
			tmp[k++] = line[i];
		i++;
	}
	*j = i;
	tmp[k] = 0;
	return (tmp);
}

static int	get_is_quote_name(char *line, t_redir_content *red)
{
	int	k;

	red->file_name = skip_quote_redir_names(line, &k, red->fd);
	return (k);
}
static int	get_no_quote_name(char *line, t_redir_content *red)
{
	int	i;
	int	j;

	j = 0;
	i = red->fd;
	red->file_name = ft_strdup(line + i);
	while (red->file_name[j] && !ft_isspace(red->file_name[j]))
		j++;
	if (red->file_name[j] && !ft_isspace(red->file_name[j]))
		something_wrong("syntax error near unexpected token", red->file_name);
	i += j;
	red->efile_name = red->file_name;
	red->file_name = ft_substr(red->file_name, 0, j);
	free (red->efile_name);
	return (i);
}

static void	fill_red_content(t_redir_content *red, int ref)
{
	red->fd = 0;
	red->mode = 0;
	if (ref == F_HEREDOC)
	{
		red->type = HEREDOC;
	}
	else if (ref == F_APPEND)
	{
		red->fd = 1;
		red->mode = O_APPEND | O_WRONLY | O_CREAT;
		red->type = APPEND;
	}
	else if (ref == F_IN_RED)
		red->type = IN_REDIR;
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
	check_out_of_quotes(line[i], &var);
	if (var.quote || var.dquote)
	{
		red->fd = i;
		i = get_is_quote_name(line, red);
	}
	else
	{
		red->fd = i;
		i = get_no_quote_name(line, red);
	}
	fill_red_content(red, ref);
	return (i);
}
t_cmd	*get_herdoc(char *line, int i)
{
	char	*before;
	char	*after;
	t_cmd			*redirection;
	int	tmp;
	t_redir_content	red;
	redirection = NULL;
	before = NULL;
	after = NULL;
	if (i - 1 > 0)
		before = ft_substr(line, 0, i - 1);
	tmp = fill_redir_content(line, i, &red, F_HEREDOC);
	if (tmp > i)
		after = ft_substr(line, tmp, ft_strlen(line + tmp));
	if (before || after)
		redirection = get_token_redir(ft_strjoin_free(before, after));
	redirection = redir_constructor(redirection, red);
	free (line);
	return (redirection);
}

t_cmd	*check_for_redirections(char *line, int i)
{
	int	j;
	t_cmd			*redirection;
	int	space;
	t_redir_content	red;
	int	tmp;

	j = 0;
	space = 0;
	// printf("[%s]\n", line);
		
	redirection = NULL;
	if (line[i] == '<' && line[i + 1] == '<')
	{
		redirection = get_herdoc(line, i);
	}
	else if (line[i] == '<')
	{
		// redirection = get_inredir();
		tmp = i;
		i = fill_redir_content(line, i, &red, F_IN_RED);
		redirection = get_token_redir(ft_strjoin_free(ft_substr(line, 0, tmp), ft_substr(line, i, ft_strlen(line + i))));
		if (redirection)
			redirection = redir_constructor(redirection, red);
		else
		{
			free (line);
			return (NULL);
		}
		free (line);
		i = -1;
		// break ;
	}
	else if (line[i] == '>' && line[i + 1] == '>')
	{
		tmp = i;
		i = fill_redir_content(line, i, &red, F_APPEND);
		redirection = get_token_redir(ft_strjoin_free(ft_substr(line, 0, tmp), ft_substr(line, i, ft_strlen(line + i))));
		if (redirection)
			redirection = redir_constructor(redirection, red);
		else
		{
			free (line);
			return (NULL);
		}
		free (line);
		i = -1;
		// break ;
	}
	else if (line[i] == '>')
	{
		tmp = i;
		i = fill_redir_content(line, i, &red, F_OUT_RED);
		redirection = get_token_redir(ft_strjoin_free(ft_substr(line, 0, tmp), ft_substr(line, i, ft_strlen(line + i))));
		if (redirection)
			redirection = redir_constructor(redirection, red);
		else
		{
			free (line);
			return (NULL);
		}
		free (line);
		i = -1;
		// break ;
	}
	return (redirection);
}
int	check_for_syntax(char *line, int i)
{
	int	j;
	int	space;

	j = 0;
	space = 0;
	if ((line[i] == '<' && line[i + 1] == '<')  || (line[i] == '>' && line[i + 1] == '>') || (line[i] == '<') || (line[i] == '>'))
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
	int				j;
	int				space;
	t_var			var;

	set_zero_var(&var);
	i = 0;
	j = 0;
	space = 0;
	redirection = NULL;
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
	{
		redirection = get_token_order(ft_strdup(line));
		free (line);
	}
	return (redirection);
}
