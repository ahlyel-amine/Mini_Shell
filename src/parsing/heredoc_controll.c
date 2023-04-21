/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_controll.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 03:02:24 by aahlyel           #+#    #+#             */
/*   Updated: 2023/04/20 14:11:09 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
char	*write_herdoc(char *delemiter)
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
			return (close(fd), name) ;
		if (!ft_strncmp(reader, delemiter, ft_strlen(delemiter) + 1))
			break ;
		write (fd, reader, ft_strlen(reader));
		write (fd, "\n", 1);
		free (reader);
	}
	return (free(reader), close(fd), free(delemiter), name);
}

char	**check_for_heredoc(char **words, int i)
{
	char	*delimiter;
	int		j;
	int		k;

	j = 0;
	k = 0;
	while (ft_strnstr(words[i] + j, "<<", ft_strlen(words[i])))
	{
		while (words[i][j] && words[i][j] != '<')
			j++;
		if (words[i][j] && words[i][j] == '<' && words[i][j + 1] == '<')
		{
			j += 2;
			if (words[i][j])
				delimiter = get_delimiter(words[i], j);
			else
				delimiter = get_delimiter(words[i + 1], 0);
			delimiter = write_herdoc(delimiter);
		}
	}
	return (words);
}

char	**heredoc_controll(char **words)
{
	int	i;
	int	dquote_is_open;
	int	quote_is_open;
	i = 0;
	dquote_is_open = 0;
	quote_is_open = 0;
	while (words[i])
		words = check_for_heredoc(words, i++);
	return (words);
}