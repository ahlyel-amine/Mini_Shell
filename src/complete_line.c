/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complete_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 12:52:14 by aahlyel           #+#    #+#             */
/*   Updated: 2023/04/27 12:54:19 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
