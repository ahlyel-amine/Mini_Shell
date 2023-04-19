/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_controll.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 03:02:24 by aahlyel           #+#    #+#             */
/*   Updated: 2023/04/19 06:50:30 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*get_delimiter(char *word, int j)
{
	int	k;

	k = 0;
	while (word[j + k] && word[j + k] != '<' && word[j + k] != '>' && 
	word[j + k] != '&' && word[j + k] != '|' && word[j + k] != '|' && 
	word[j + k] != ';' && word[j + k] != '\"' && word[j + k] != '\'')
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
	fd = open(name, O_RDWR | O_CREAT | O_TRUNC, 0666);
	while (1337)
	{
		reader = readline("here_doc> ");
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
	char	**new_words;
	char	*delimiter;
	int		j;
	int		k;

	j = 0;
	k = 0;
	if (ft_strnstr(words[i], "<<", ft_strlen(words[i])))
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
			printf("%s\n", delimiter);
		}
	}
	return (words);
}

char	*heredoc_controll(char *line)
{
	int	i;
	int	dquote_is_open
	int	quote_is_open
	i = 0;
	dquote_is_open = 0;
	quote_is_open = 0;
	while (line[i])
	{
		if (line[i] == '\'')
		
			quote_is_open = 1;
		if (line[i] == '\"')
			dquote_is_open = 1;
		
		line = check_for_heredoc(line, i);
		i++;
	}
	return (line);
}