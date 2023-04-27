/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_token.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 12:31:49 by aahlyel           #+#    #+#             */
/*   Updated: 2023/04/27 19:43:23 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
		redirection = get_token_order(ft_strdup(line));
	return (redirection);
}