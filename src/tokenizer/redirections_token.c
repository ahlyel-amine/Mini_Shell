/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_token.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 12:31:49 by aahlyel           #+#    #+#             */
/*   Updated: 2023/04/28 13:54:00 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	fill_redir_content_herdoc(char *line, int i, t_redir_content *red)
{
	int	quote;
	int	dquote;
	int	k;

	i += 2;
	k = 0;
	quote = 0;
	dquote = 0;
	while (ft_isspace(line[i]))
		i++;
	if (!line[i])
		something_wrong("Asyntax error near unexpected token `newline'", line);
	check_out_of_quotes(line[i], &quote, &dquote);
	if (quote || dquote)
		k++;
	red->file_name = ft_strdup(line + i + k);
	while ((ft_isalnum(line[i + k]) || line[i + k] == '_') || (ft_isspace(line[i + k])  && (quote || dquote)))
		check_out_of_quotes(line[i++ + k], &quote, &dquote);
	red->efile_name = line + i + k;
	if (red->file_name == red->efile_name)
		something_wrong("Bsyntax error near unexpected token `newline'", line);
	red->fd = 0;
	red->mode = 0;
	red->type = HEREDOC;
	return (i + k);
}

int	fill_redir_content_inredir(char *line, int i, t_redir_content *red)
{
	int	j;

	j = 0;
	line = quotes(line, i + 1);
	while (ft_isspace(line[j]))
		j++;
	if (!line[j])
		something_wrong("Asyntax error near unexpected token `newline'", line);
	red->file_name = ft_strdup(line + j);
	while (!ft_isspace(line[j]) && !ft_strchr("|&$<>", line[j]))
		j++;
	red->efile_name = line + j;
	if (red->file_name == red->efile_name)
		something_wrong("Bsyntax error near unexpected token `newline'", line);
	red->fd = 0;
	red->mode = O_RDONLY;
	red->type = IN_REDIR;
	return (free(line), i + j + 1);
}

int	fill_redir_content_append(char *line, int i, t_redir_content *red)
{
	int	j;

	j = 0;
	line = quotes(line, i + 2);
	while (ft_isspace(line[j]))
		j++;
	if (!line[j])
		something_wrong("Esyntax error near unexpected token `newline'", line);
	red->file_name = ft_strdup(line + j);
	while (!ft_isspace(line[j]) && !ft_strchr("|&$<>", line[j]))
		j++;
	red->efile_name = line + i;
	if (red->file_name == red->efile_name)
		something_wrong("Fsyntax error near unexpected token `newline'", line);
	red->fd = 1;
	red->mode = O_APPEND | O_WRONLY | O_CREAT;
	red->type = APPEND;
	return (free(line), i + j + 2);
}

int	fill_redir_content_outredir(char *line, int i, t_redir_content *red)
{
	int	j;

	j = 0;
	line = quotes(line, i + 1);
	while (ft_isspace(line[j]))
		j++;
	if (!line[j])
		something_wrong("Esyntax error near unexpected token `newline'", line);
	red->file_name = ft_strdup(line + j);
	while (!ft_isspace(line[j]) && !ft_strchr("|&$<>", line[j]))
		j++;
	red->efile_name = line + j;
	if (red->file_name == red->efile_name)
		something_wrong("Esyntax error near unexpected token `newline'", line);
	red->fd = 1;
	red->mode = O_TRUNC | O_WRONLY | O_CREAT;
	red->type = APPEND;
	return (free(line), i + j + 1);

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
			// if (is_herdoc())
			// 	break ;
			// else if (is_inredir())
			// 	break ;
			// else if (is_append())
			// 	break ;
			// else if (is_outredir())
			// 	break ;
			if (line[i] == '<' && line[i + 1] == '<')
			{
				quote = i;
				i = fill_redir_content_herdoc(line, i, &red);
				redirection = redir_constructor(\
				get_token_order(ft_strjoin_free(ft_substr(line, 0, quote), ft_substr(line, i, ft_strlen(line + i)))), red);
				free (line);
				i = -1;
				break ;
			}
			else if (line[i] == '<')
			{
				quote = i;
				i = fill_redir_content_inredir(line, i, &red);
				redirection = redir_constructor(\
				get_token_order(ft_strjoin_free(ft_substr(line, 0, quote), ft_substr(line, i, ft_strlen(line + i)))), red);
				free (line);
				i = -1;
				break ;
			}
			else if (line[i] == '>' && line[i + 1] == '>')
			{
				quote = i;
				i = fill_redir_content_append(line, i, &red);
				redirection = redir_constructor(\
				get_token_order(ft_strjoin_free(ft_substr(line, 0, quote), ft_substr(line, i, ft_strlen(line + i)))), red);
				free (line);
				i = -1;
				break ;
			}
			else if (line[i] == '>')
			{
				quote = i;
				i = fill_redir_content_outredir(line, i, &red);
				redirection = redir_constructor(\
				get_token_order(ft_strjoin_free(ft_substr(line, 0, quote), ft_substr(line, i, ft_strlen(line + i)))), red);
				free (line);
				i = -1;
				break ;
			}
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