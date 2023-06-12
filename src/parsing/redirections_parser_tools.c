/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_parser_tools.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 15:39:50 by aahlyel           #+#    #+#             */
/*   Updated: 2023/06/11 13:37:33 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*skip_quote_redir_names(char *line, int *j, int i, int *q)
{
	int		k;
	char	*tmp;
	t_var	var;

	ft_memset(&var, 0, sizeof(t_var));
	tmp = ft_calloc(1, ft_strlen(line + i) + 1);
	k = 0;
	*q = 0;
	if (line[i] == '$' && line[i + 1] == '\'' && line[i + 1] == '\'')
		i++;
	while (line[i])
	{
		check_out_of_quotes(line[i], &var);
		if (var.dquote || var.quote)
			*q = 1;
		if (ft_isspace(line[i]) && !var.quote && !var.dquote)
			break ;
		if ((var.quote || var.dquote) && ft_isspace(line[i]))
			tmp[k++] = line[i];
		else if ((line[i] == '\"' && var.quote) || (line[i] == '\''\
				&& var.dquote))
			tmp[k++] = line[i];
		else if (!var.quote && !var.dquote && !ft_isvariable(line[i])
			&& line[i] != '\"' && line[i] != '\'')
			break ;
		else if (line[i] != '\'' && line[i] != '\"')
			tmp[k++] = line[i];
		i++;
	}
	*j = i;
	return (tmp);
}
/*----------*/

int	ft_isname(char c)
{
	return (c != '&' && c != '|' && c != '<' && c != '>' && c != ' ');
}

t_arguments	*get_names(char *line, int *i)
{
	t_arguments	*arguments;
	t_var		var;
	int			j;

	ft_memset(&var, 0, sizeof(t_var));
	arguments = NULL;
	j = 0;
	while (line[*i + j])
	{
		check_out_of_quotes(line[*i + j], &var);
		if (var.dquote && line[*i + j] == '\"')
		{
			if (j)
				arguments = arguments_constructor(arguments, ft_substr(line, *i,\
						j), IS_STR, 0);
			*i += j + 1;
			*i += close_dquote(&arguments, line, *i) + 1;
			var.dquote = 0;
			j = 0;
			continue ;
		}
		else if (var.quote && line[*i + j] == '\'')
		{
			if (j)
				arguments = arguments_constructor(arguments, ft_substr(line, *i,\
						j), IS_STR, 0);
			*i += j + 1;
			*i += close_quote(&arguments, line, *i) + 1;
			var.quote = 0;
			j = 0;
			continue ;
		}
		else if (!var.dquote && !var.quote && !ft_isname(line[*i + j]))
			break ;
		j++;
	}
	if (j)
	{
		arguments = arguments_constructor(arguments, ft_substr(line, *i, j),
			IS_STR, 0);
		*i += j;
	}
	merge_arguments(&arguments, 0);
	tokenize_variables(&arguments);
	return (arguments);
}

char	*get_herdoc_name(void)
{
	static int	call;

	return (ft_strjoin_free(ft_strdup("/tmp/.heredoc_"), ft_itoa(call++)));
}
/*-----------*/
void	read_heredoc(t_redir_content *red, t_arguments *args)
{
	char	*name;
	char	*line;
	int		fd;

	in_cmd = 1;
	sig_here();
	name = get_herdoc_name();
	fd = open(name, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (fd < 0)
		return (pr_custom_err(ERR_FILE, red->delimiter, name));
	line = readline(HERDOC);
	while (line && !Ctrl_c)
	{
		if (!strncmp(line, red->delimiter, ft_strlen(red->delimiter) + 1))
		{
			free(line);
			break ;
		}
		if (!red->file_name->q)
			line = data_analyse(line);
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
		line = readline(HERDOC);
	}
	Ctrl_c = 0;
	in_cmd = 0;
	free(red->delimiter);
	red->delimiter = name;
	close(fd);
}

int	get_name(char *line, t_redir_content *red, int type)
{
	t_arguments	*args;
	int			k;
	int			q;

	args = NULL;
	k = red->fd;
	if (type == F_HEREDOC)
	{
		red->file_name = arguments_constructor(args,
		skip_quote_redir_names(line, &k, red->fd, &q), IS_STR, q);
		print_arguments(red->file_name, "yo");
		red->delimiter = args_to_str(red->file_name);
		read_heredoc(red, args);
	}
	else
		red->file_name = get_names(line, &k);
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
			return (panic_recursive("minishell : syntax error near unexpected token\n",
					line), 0);
	}
	return (1);
}
