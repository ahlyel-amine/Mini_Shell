/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_controll.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 02:53:32 by aahlyel           #+#    #+#             */
/*   Updated: 2023/04/26 12:11:21 by aahlyel          ###   ########.fr       */
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
		something_wrong("parse error near `\n'");
	red->file_name = line + i;
	while (ft_isalnum(line[i]) || line[i] == '_')
		i++;
	red->efile_name = line + i;
	if (ref->file_name == ref->efile_name)
		something_wrong("parse error near `\n'");
	red->fd = 0;
	red->mode = O_CREAT | O_TRUNC | O_RDWR;
	red->type = HEREDOC;
	return (i);
}

int	fill_redir_content_inredir(char *line, int i, t_redir_content *red)
{
	i++;
	while (ft_isspace(line[i]))
		i++;
	if (!line[i])
		something_wrong("parse error near `\n'");
	red->file_name = line + i;
	while (!ft_isspace(line[i]) && !ft_strchr("|&$<>", line[i]))
		i++;
	red->efile_name = line + i;
	if (ref->file_name == ref->efile_name)
		something_wrong("parse error near `\n'");
	red->fd = 0;
	red->mode = O_CREAT | O_TRUNC | O_RDWR;
	red->type = IN_REDIR;
	return (i);
}


t_cmd	*get_redir(char *line)
{
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
				 i = fill_redir_content_herdoc(line, i, &red);
			else if (line[i] == '<')
				 i = fill_redir_content_inredir(line, i, &red);
		}
		i++;
	}
}

void	check_out_of_quotes(char c, int *quote, int *dquote)
{
	if (c == '\"' && !(*quote))
			(*dquote) = !(*dquote);
	if (c == '\'' && !(*dquote))
		(*quote) = !(*quote);
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
		pipe_line = get_redir(line);
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
	if (cmd->type == AND)
	{
		cmd = ((t_and *)cmd)->right;

		if (cmd->type == AND)
		{
			cmd = ((t_and *)cmd)->left;
			if (cmd->type == PIPE)
			{
				cmd = ((t_pipe *)cmd)->left;
				if (cmd->type == WORD)
					printf("%s\n", ((t_word *)cmd)->word);
			}
			else if (cmd->type == WORD)
				printf("%s\n", ((t_word *)cmd)->word);
		}
		else if (cmd->type == PIPE)
		{
			cmd = ((t_pipe *)cmd)->left;
			if (cmd->type == WORD)
				printf("%s\n", ((t_word *)cmd)->word);
		}
	}
}