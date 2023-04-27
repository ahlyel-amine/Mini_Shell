/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_controll.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 02:53:32 by aahlyel           #+#    #+#             */
/*   Updated: 2023/04/27 10:40:56 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	read_until_chr(char **line, char c)
{
	char	*dquote;
	int		quote_pos;

	while (1337)
	{
		if (c == '\'')
			dquote = readline("quote> ");
		else
			dquote = readline("dquote> ");
		if (!dquote)
		{
			new_arg(0, 0, -1);
			ft_putendl_fd("unexpected EOF while looking for matching \"\'", 2);
			ft_putendl_fd("minishell: syntax error: unexpected end of file", 2);
			return ;
		}
		*line = ft_strjoin(*line, ft_strdup("\n"));
		*line = ft_strjoin(*line, dquote);
		quote_pos = ft_chrpos(*line, c);
		if (quote_pos != -1)
			break ;
	}
}
void	get_is_complete(char *line, int *quote, int *dquote, int *operator)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\"' && !(*quote))
			(*dquote) = !(*dquote);
		if (line[i] == '\'' && !(*dquote))
			(*quote) = !(*quote);
		if (!line[i + 1])
		{
			if (i - 2 >= 0)
			{
				if ((!ft_isspace(line[i - 2]) && line[i - 1] == '&' && line[i] == '&')
				|| (!ft_isspace(line[i - 2]) && line[i - 1] == '|' && line[i] == '|'))
					*operator = 1;
			}
			if (i - 1 >= 0)
			{
				if (line[i] == '|' || (line[i - 1] == '&' && line[i] == '&') || (line[i - 1] == '|' && line[i] == '|'))
					*operator = 1;
			}
		}
		i++;
	}
} 

void	complete_line(char **line)
{
	int		quote;
	int		dquote;
	int		operator;
	char	*tmp;
	char	*tmp2;

	quote = 0;
	operator = 0;
	dquote = 0;
	get_is_complete(*line, &quote, &dquote, &operator);
	if (dquote)
		read_until_chr(line, '\"');
	else if (quote)
		read_until_chr(line, '\'');
	else if (operator)
	{
		tmp = readline("> ");
		tmp2 = *line;
		*line = ft_strjoin(*line, tmp);
		free(tmp2);
		free(tmp);
	}
	else
		return ;
	complete_line(line);
}
void	something_wrong(char *error)
{
	ft_putendl_fd(error, 2);
	exit(1);
}
int	fill_redir_content_herdoc(char *line, int i, t_redir_content *red)
{
	i += 2;
	while (ft_isspace(line[i]))
		i++;
	if (!line[i])
		something_wrong("syntax error near unexpected token `newline'");
	red->file_name = line + i;
	while (ft_isalnum(line[i]) || line[i] == '_')
		i++;
	red->efile_name = line + i;
	if (red->file_name == red->efile_name)
		something_wrong("syntax error near unexpected token `newline'");
	red->fd = 0;
	red->mode = 0;
	red->type = HEREDOC;
	return (i);
}

int	fill_redir_content_inredir(char *line, int i, t_redir_content *red)
{
	i++;
	while (ft_isspace(line[i]))
		i++;
	if (!line[i])
		something_wrong("syntax error near unexpected token `newline'");
	red->file_name = line + i;
	while (!ft_isspace(line[i]) && !ft_strchr("|&$<>", line[i]))
		i++;
	red->efile_name = line + i;
	if (red->file_name == red->efile_name)
		something_wrong("syntax error near unexpected token `newline'");
	red->fd = 0;
	red->mode = O_RDONLY;
	red->type = IN_REDIR;
	return (i);
}

int	fill_redir_content_append(char *line, int i, t_redir_content *red)
{
	i += 2;
	while (ft_isspace(line[i]))
		i++;
	if (!line[i])
		something_wrong("syntax error near unexpected token `newline'");
	red->file_name = line + i;
	while (!ft_isspace(line[i]) && !ft_strchr("|&$<>", line[i]))
		i++;
	red->efile_name = line + i;
	if (red->file_name == red->efile_name)
		something_wrong("syntax error near unexpected token `newline'");
	red->fd = 1;
	red->mode = O_APPEND | O_WRONLY | O_CREAT;
	red->type = APPEND;
	return (i);
}

int	fill_redir_content_outredir(char *line, int i, t_redir_content *red)
{
	i++;
	while (ft_isspace(line[i]))
		i++;
	if (!line[i])
		something_wrong("syntax error near unexpected token `newline'");
	red->file_name = line + i;
	while (!ft_isspace(line[i]) && !ft_strchr("|&$<>", line[i]))
		i++;
	red->efile_name = line + i;
	if (red->file_name == red->efile_name)
		something_wrong("syntax error near unexpected token `newline'");
	red->fd = 1;
	red->mode = O_TRUNC | O_WRONLY | O_CREAT;
	red->type = APPEND;
	return (i);
}

void	check_out_of_quotes(char c, int *quote, int *dquote)
{
	if (c == '\"' && !(*quote))
			(*dquote) = !(*dquote);
	if (c == '\'' && !(*dquote))
		(*quote) = !(*quote);
}
char	*nul_terminate_at(char *line, int nul)
{
	line[nul] = 0;
	return (line);
}

int	echo_has_option(char *line, int *i)
{
	int	has_option;
	int	j;

	*i = 0;
	has_option = 0;
	while (line[*i])
	{
		while (ft_isspace(line[*i]))
			(*i)++;
		j = 0;
		if (line[*i + j] == '-' && line[*i + j + 1] == 'n')
		{
			j++;
			while (line[*i + j] == 'n')
				j++;
		}
		else if (line[*i + j] == '\"' && line[*i + j + 1] == '-' && line[*i + j + 2] == 'n')
		{
			j += 2;
			while (line[*i + j] == 'n')
				j++;
			if (line[*i + j] == '\"')
				j++;
		}
		else if (line[*i + j] == '\'' && line[*i + j + 1] == '-' && line[*i + j + 2] == 'n')
		{
			j += 2;
			while (line[*i + j] == 'n')
				j++;
			if (line[*i + j] == '\'')
				j++;
		}
		if (ft_isspace(line[*i + j]) || !line[*i + j])
		{
			has_option = 1;
			*i += j;
		}
		else
			break ;
	}
	return (has_option);
}

int	count_arguments(char *line)
{
	int	i;
	int	quote;
	int	dquote;
	int counter;

	counter = 0;
	dquote = 0;
	quote = 0;
	i = 0;
	while (line[i])
	{
		while (ft_isspace(line[i]))
			i++;
		check_out_of_quotes(line[i], &quote, &dquote);
		while (line[i] && !quote && !dquote && !ft_isspace(line[i]))
		{
			check_out_of_quotes(line[i], &quote, &dquote);
			i++;
		}
		if (ft_isspace(line[i]) || !line[i])
				counter++;
		else if (quote)
		{
			while (line[i] != '\'')
				i++;
			if (ft_isspace(line[i]) || !line[i])
				counter++;
		}
		else if (dquote)
		{
			while (line[i] != '\"')
				i++;
			if (line[i] == '\"')
				i++;
			if (ft_isspace(line[i]) || !line[i])
				counter++;
		}
	}
	return (counter);
}

char	**select_arguments(char *line, int count)
{
	int		i;
	int		quote;
	int		dquote;
	int 	j;
	char	**cmd;

	cmd = malloc(sizeof (char *) * (count + 1));
	cmd[count] = NULL;
	count = 0;
	quote = 0;
	dquote = 0;
	i = 0;
	j = 0;

	while (line[i + j])
	{
		while (ft_isspace(line[i + j]))
			j++;
		check_out_of_quotes(line[i + j], &quote, &dquote);
		while (line[i + j] && !quote && !dquote && !ft_isspace(line[i + j]))
		{
			check_out_of_quotes(line[i + j], &quote, &dquote);
			j++;
		}
		if (ft_isspace(line[i + j]) || !line[i + j])
		{
			cmd[count++] = ft_substr(line, i, j);
			i += j;
		}
		else if (quote)
		{
			while (line[i + j] != '\'')
				j++;
			if (ft_isspace(line[i + j]) || !line[i + j])
			{
				cmd[count++] = ft_substr(line, i, j);
				i += j;
			}
		}
		else if (dquote)
		{
			while (line[i + j] != '\"')
				j++;
			if (line[i + j] == '\"')
				j++;
			if (ft_isspace(line[i + j]) || !line[i + j])
			{
				cmd[count++] = ft_substr(line, i, j - 1);
				i += j;
			}
		}
		j = 0;
	}
	j = 0;
	while (cmd[j])
		printf("|%s|\n", cmd[j++]);
	return (cmd);
}

char	*quotes(char *line, int i)
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
		while (ft_isspace(line[i]) && ft_isspace(line[i + 1]) && !quote && !dquote)
			i++;
		if (ft_isspace(line[i]) && !line[i + 1])
		{
			i++;
			continue ;
		}
		if (!quote && !dquote && ft_isspace(line[i]))
			tmp[k++] = line[i];
		else if ((line[i] == '\"' && quote) || (line[i] == '\'' && dquote))
			tmp[k++] = line[i];
		else if (line[i] == '$' && (dquote || (!dquote && !quote)))
		{
			if (ft_isdigit(line[i + 1]))
				i += 2;
			else if (line[i] == '$' && !line[i + 1])
				i++;
			else if (line[i] == '$')
			{
				i++;
				tmp[k++] = '\"';
				while (ft_isalnum(line[i]) || line[i] == '_')
					tmp[k++] = line[i++];
			}
			continue ;
		}
		else if (line[i] != '\'' && line[i] != '\"')
			tmp[k++] = line[i];
		i++;
	}
	tmp[k] = 0;
	return (tmp);
}

t_cmd	*get_token_builtins(char *line, int i, int j)
{
	t_cmd *cmd= NULL;
	int has_option = 0;
	if (!ft_strncmp(nul_terminate_at(ft_strdup(line + i), j), "echo", 5))
	{
		has_option = echo_has_option(line + i + j, &i);
		cmd = builtin_constructor(ft_strdup("echo"), \
		has_option, quotes(line, i + j));
		echo(cmd);
	}
	else if (!ft_strncmp(nul_terminate_at(ft_strdup(line + i), j), "cd", 3))
	{
		cmd = builtin_constructor(ft_strdup("cd"), \
		has_option, quotes(line, i + j));
	}
	else if (!ft_strncmp(nul_terminate_at(ft_strdup(line + i), j), "pwd", 4))
	{
		cmd = builtin_constructor(ft_strdup("pwd"), \
		has_option, quotes(line, i + j));
	}
	else if (!ft_strncmp(nul_terminate_at(ft_strdup(line + i), j), "unset", 6))
	{
		cmd = builtin_constructor(ft_strdup("unset"), \
		has_option, quotes(line, i + j));
	}
	else if (!ft_strncmp(nul_terminate_at(ft_strdup(line + i), j), "env", 4))
	{
		cmd = builtin_constructor(ft_strdup("env"), \
		has_option, quotes(line, i + j));
	}
	else if (!ft_strncmp(nul_terminate_at(ft_strdup(line + i), j), "export", 7))
	{
		cmd = builtin_constructor(ft_strdup("export"), \
		has_option, quotes(line, i + j));
	}
	else if (!ft_strncmp(nul_terminate_at(ft_strdup(line + i), j), "exit", 5))
	{
		cmd = builtin_constructor(ft_strdup("exit"), \
		has_option, quotes(line, i + j));
	}
	return (cmd);
}

int	check_cmd(char **path, char *cmd, int j)
{
	char	*new_cmd;
	char	*tmp_path;
	int		i;

	i = 0;
	new_cmd = quotes(ft_substr(cmd, 0, j), 0);
	if (!access(new_cmd, F_OK | X_OK))
		return (1);
	while (path[i])
	{
		tmp_path = NULL;
		tmp_path = ft_strjoin(path[i], "/");
		tmp_path = ft_strjoin_free(tmp_path, ft_strdup(new_cmd));
		if (!access(tmp_path, F_OK | X_OK))
			return (1);
		i++;
	}
	return (0);
}

t_cmd	*get_token_cmd(char *line, int j)
{
	t_cmd	*cmd;
	int		has_option;
	cmd = NULL;
	has_option = 0;
	if (!check_cmd((char **)env_variables(0, GET), line, j))
		return (NULL);
	cmd = execcmd_constructor(ft_split_char(line, ' '));
	return (free(line), cmd);
}

t_cmd	*get_token_variable_assignement(char *line, int j)
{
	t_cmd	*cmd;
	int		has_option;
	cmd = NULL;
	has_option = 0;
	if (!check_cmd((char **)env_variables(0, GET), line, j))
		return (NULL);
	cmd = execcmd_constructor(ft_split_char(line, ' '));
	return (free(line), cmd);
}

/*	cmd / built-in /arguments / options	*/
t_cmd	*get_token_order(char *line)
{
	t_cmd	*cmd;
	int		i;
	int		j;
	int		has_option;

	i = 0;
	j = 0;
	has_option = 0;
	cmd = NULL;

	while (ft_isspace(line[i]))
		i++;
	while (line[i + j] && !ft_isspace(line[i + j]))
		j++;
	cmd = get_token_builtins(ft_strdup(line + i), i, j);
	if (!cmd)
		cmd = get_token_cmd(ft_strdup(line + i), j);
	else
		cmd = get_token_variable_assignement(ft_strdup(line + i), j);
	return (cmd);
}

t_cmd	*get_token_redir(char *line)
{
	t_cmd			*redirection;
	int				i;
	int				quote;
	int				dquote;
	t_redir_content	red;

	quote = 0;
	dquote = 0;
	i = 0;
	while (line[i])
	{
		check_out_of_quotes(line[i], &quote, &dquote);
		if (!quote && !dquote)
		{
			if (line[i] == '<' && line[i + 1] == '<')
			{
				quote = i;
				i = fill_redir_content_herdoc(line, i, &red);
				redirection = redir_constructor(\
				get_token_order(ft_strjoin_free(ft_substr(line, 0, quote), ft_substr(line, i, ft_strlen(line + i)))), red);
				i = -1;
				break ;
			}
			else if (line[i] == '<')
			{
				quote = i;
				i = fill_redir_content_inredir(line, i, &red);
				redirection = redir_constructor(\
				get_token_order(ft_strjoin_free(ft_substr(line, 0, quote), ft_substr(line, i, ft_strlen(line + i)))), red);
				i = -1;
				break ;
			}
			else if (line[i] == '>' && line[i + 1] == '>')
			{
				quote = i;
				i = fill_redir_content_append(line, i, &red);
				redirection = redir_constructor(\
				get_token_order(ft_strjoin_free(ft_substr(line, 0, quote), ft_substr(line, i, ft_strlen(line + i)))), red);
				i = -1;
				break ;
			}
			else if (line[i] == '>')
			{
				quote = i;
				i = fill_redir_content_outredir(line, i, &red);
				redirection = redir_constructor(\
				get_token_order(ft_strjoin_free(ft_substr(line, 0, quote), ft_substr(line, i, ft_strlen(line + i)))), red);
				i = -1;
				break ;
			}
		}
		i++;
	}
	if (i != -1)
		redirection = get_token_order(line);
	return (redirection);
}

t_cmd	*get_token_operator_pipe(char *line)
{
	t_cmd	*pipe_line;
	int	i;
	int	operator_pipe;
	int		quote;
	int		dquote;

	quote = 0;
	dquote = 0;
	i = 0;
	operator_pipe = 0;
	while (line[i])
	{
		check_out_of_quotes(line[i], &quote, &dquote);
		if (i - 1 >= 0 && !quote && !dquote)
		{
			if (line[i] == '|')
			{
				operator_pipe = 1;
				pipe_line = pipe_constructor(get_token_operator_pipe(ft_substr(line, 0, i)),
				get_token_operator_pipe(ft_substr(line, i + 1, ft_strlen(line + i + 1))));
				break ;
			}
		}
		i++;
	}
	if (!operator_pipe)
		pipe_line = get_token_redir(line);
	return (pipe_line);
}
t_cmd	*get_token_operator(char *line)
{
	t_cmd	*operator;
	int		i;
	int		operator_and;
	int		operator_or;
	int		quote;
	int		dquote;
	

	quote = 0;
	dquote = 0;
	i = 0;
	operator_and = 0;
	operator_or = 0;
	while (line[i])
	{
		check_out_of_quotes(line[i], &quote, &dquote);
		if (i - 2 >= 0 && !quote && !dquote)
		{
			if (line[i - 1] == '&' && line[i] == '&')
			{
				operator_and = 1;
				operator = and_constructor(get_token_operator(ft_substr(line, 0, i - 1)), 
				get_token_operator(ft_substr(line, i + 1, ft_strlen(line + i + 1))));
				break ;
			}
			else if (line[i - 1] == '|' && line[i] == '|')
			{
				operator_or = 1;
				operator = or_constructor(get_token_operator(ft_substr(line, 0, i - 1)), 
				get_token_operator(ft_substr(line, i + 1, ft_strlen(line + i + 1))));
				break ;
			}
		}
		if (i - 1 >= 0)
		{
			if (line[i - 1] == '&' && line[i] == '&')
			{
				operator_and = 1;
				operator = and_constructor(get_token_operator(ft_substr(line, 0, i - 1)), 
				get_token_operator(ft_substr(line, i + 1, ft_strlen(line + i + 1))));
				break ;
			}
			else if (line[i - 1] == '|' && line[i] == '|')
			{
				operator_or = 1;
				operator = or_constructor(get_token_operator(ft_substr(line, 0, i - 1)), 
				get_token_operator(ft_substr(line, i + 1, ft_strlen(line + i + 1))));
				break ;
			}
		}
		i++;
	}
	if (!operator_and && ! operator_or)
		operator = get_token_operator_pipe(line);
	return (operator);
}

void parsing_controll(char *line)
{
	t_cmd	*cmd;

	complete_line(&line);
	cmd = get_token_operator(ft_strdup(line));
}