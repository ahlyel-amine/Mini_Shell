/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_token.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 12:31:49 by aahlyel           #+#    #+#             */
/*   Updated: 2023/04/28 19:20:49 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
static int	fill_is_quote_content(char *line, t_redir_content *red, int quote, int dquote)
{
	int	i;
	int	j;

	j = 0;
	i = red->fd;
	i++;
	red->file_name = ft_strdup(line + i);
	check_out_of_quotes(red->file_name[j], &quote, &dquote);
	while (red->file_name[j] && (quote || dquote))
	{
		// if (red->file_name[j] == '\\')
		// 	something_wrong("asyntax error near unexpected token `newline'\\", red->file_name);
		j++;
		check_out_of_quotes(red->file_name[j], &quote, &dquote);
	}
	i += j + 1;
	red->efile_name = red->file_name;
	red->file_name = ft_substr(red->file_name, 0, j);
	free (red->efile_name);
	return (i);
}
int	fill_redir_content(char *line, int i, t_redir_content *red, int ref)
{
	int	j;
	int	quote;
	int	dquote;

	quote = 0;
	dquote = 0;
	j = 0;
	i = i + (ref >> 1);
	red->file_name = NULL;
	while (ft_isspace(line[i]))
		i++;
	check_out_of_quotes(line[i], &quote, &dquote);
	if (quote || dquote)
	{
		red->fd = i;
		fill_is_quote_content(line, red, quote, dquote);
	}
	else
	{
		red->file_name = ft_strdup(line + i);
		while (red->file_name[j] && !ft_isspace(red->file_name[j]))
			j++;
		if (red->file_name[j] && !ft_isspace(red->file_name[j]))
			something_wrong("syntax error near unexpected token", red->file_name);
		i += j;
		red->efile_name = red->file_name;
		red->file_name = ft_substr(red->file_name, 0, j);
		free (red->efile_name);
	}
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
				i = fill_redir_content(line, i, &red, F_HEREDOC);
				redirection = redir_constructor(\
				get_token_order(ft_strjoin_free(ft_substr(line, 0, quote), ft_substr(line, i, ft_strlen(line + i)))), red);
				free (line);
				i = -1;
				break ;
			}
			else if (line[i] == '<')
			{
				quote = i;
				i = fill_redir_content(line, i, &red, F_IN_RED);
				// i = fill_redir_content_inredir(line, i, &red);
				redirection = redir_constructor(\
				get_token_order(ft_strjoin_free(ft_substr(line, 0, quote), ft_substr(line, i, ft_strlen(line + i)))), red);
				free (line);
				i = -1;
				break ;
			}
			else if (line[i] == '>' && line[i + 1] == '>')
			{
				quote = i;
				i = fill_redir_content(line, i, &red, F_APPEND);
				// i = fill_redir_content_append(line, i, &red);
				redirection = redir_constructor(\
				get_token_order(ft_strjoin_free(ft_substr(line, 0, quote), ft_substr(line, i, ft_strlen(line + i)))), red);
				free (line);
				i = -1;
				break ;
			}
			else if (line[i] == '>')
			{
				quote = i;
				i = fill_redir_content(line, i, &red, F_OUT_RED);
				// i = fill_redir_content_outredir(line, i, &red);
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