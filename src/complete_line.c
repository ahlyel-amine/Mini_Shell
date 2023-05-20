/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complete_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 12:52:14 by aahlyel           #+#    #+#             */
/*   Updated: 2023/05/20 19:36:23 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*read_until_chr(char *line, char c)
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
			free (line);
			ft_putendl_fd("unexpected EOF while looking for matching \"\'", 2);
			ft_putendl_fd("minishell: syntax error: unexpected end of file", 2);
			return (NULL);
		}
		line = ft_strjoin_free(line, ft_strdup("\n"));
		line = ft_strjoin_free(line, dquote);
		quote_pos = ft_chrpos(line, c);
		if (quote_pos != -1)
			break ;
	}
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

char	*get_is_complete(char *line, int *quote, int *dquote)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\"' && !(*quote))
			(*dquote) = !(*dquote);
		if (line[i] == '\'' && !(*dquote))
			(*quote) = !(*quote);
		i++;
	}
	return (line);
} 

void	complete_line(char **line)
{
	int		quote;
	int		dquote;
	char	*tmp;

	quote = 0;
	dquote = 0;
	if (!line || !*line)
		return ;
	*line = get_is_complete(*line, &quote, &dquote);
	if (!*line)
		return ;
	if (dquote)
		*line = read_until_chr(ft_strdup(*line), '\"');
	else if (quote)
		*line = read_until_chr(ft_strdup(*line), '\'');
	else
		return ;
	complete_line(line);
}
