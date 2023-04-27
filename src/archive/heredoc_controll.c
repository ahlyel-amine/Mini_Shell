/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_controll.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 03:02:24 by aahlyel           #+#    #+#             */
/*   Updated: 2023/04/27 13:43:09 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "archive.h"

char	*get_delimiter(char *word, int j)
{
	int	k;

	k = 0;
	while (word[j + k] && word[j + k] != '<' && word[j + k] != '>' && \
	word[j + k] != '&' && word[j + k] != '|' && word[j + k] != '(' && \
	word[j + k] != ')' && word[j + k] != ';' && word[j + k] != '\"' && \
	word[j + k] != '\'')
		k++;
	return (ft_substr(word, j, k));
}
void	write_herdoc(char *delemiter)
{
	static int	herdoc_ind;
	char		*name;
	char		*reader;
	int			fd;

	name = ft_strjoin("/tmp/.heredoc", ft_itoa(herdoc_ind++));
	fd = open(name, O_RDWR | O_CREAT | O_TRUNC);
	while (1337)
	{
		reader = readline("here_doc> ");
		if (!reader)
		{
			close(fd);
			return ;
		}
		if (!ft_strncmp(reader, delemiter, ft_strlen(delemiter) + 1))
			break ;
		write (fd, reader, ft_strlen(reader));
		write (fd, "\n", 1);
		free (reader);
	}
	return (free(reader), close(fd), free(delemiter));
}

void	check_for_heredoc(t_arg *arg)
{
	char	*delimiter;
	int		j;
	int		k;

	j = 0;
	k = 0;
	if (ft_strnstr(arg->token, "<<", ft_strlen(arg->token)))
	{
		while (arg->token[j] && arg->token[j] != '<')
			j++;
		if (arg->token[j] && arg->token[j] == '<' && arg->token[j + 1] == '<')
		{
			j += 2;
			if (arg->token[j])
				delimiter = get_delimiter(arg->token, j);
			else
				delimiter = get_delimiter(arg->next->token, 0);
			write_herdoc(delimiter);
		}
	}
}

void	heredoc_controll()
{
	t_arg	*arg;
	int	i;
	int	dquote_is_open;
	int	quote_is_open;

	arg = new_arg(0, 0, 1);
	i = 0;
	dquote_is_open = 0;
	quote_is_open = 0;
	while (arg)
	{
		check_for_heredoc(arg);
		arg = arg->next;
	}
}