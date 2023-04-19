/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   not_complete_line_checker.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 00:21:54 by aahlyel           #+#    #+#             */
/*   Updated: 2023/04/19 23:19:55 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	**check_last_pipe(char **words)
{
	char	**new_words;
	char	*reader;
	int		dlen;
	int		len;
	
	dlen = ft_double_strlen(words);
	len = ft_strlen(words[dlen - 1]);
	if (!ft_strncmp(words[dlen - 1] + len - 1, "|", 3))
	{
		reader = readline("pipe> ");
		new_words = spliter(reader, 0);
		new_words = heredoc_controll(new_words);
		words = ft_joindstrs(words, new_words);
		words = check_last(words);
		words = check_last_pipe(words);
	}
	return (words);
}

char	**check_last(char **words)
{
	char	**new_words;
	char	*reader;
	int		dlen;
	int		len;
	
	dlen = ft_double_strlen(words);
	len = ft_strlen(words[dlen - 1]);
	if (!ft_strncmp(words[dlen - 1] + len - 2, "&&", 3))
	{
		reader = readline("cmdand> ");
		new_words = spliter(reader, 0);
		new_words = heredoc_controll(new_words);
		words = ft_joindstrs(words, new_words);
		words = check_last(words);
	}
	else if (!ft_strncmp(words[dlen - 1] + len - 2, "||", 3))
	{
		reader = readline("cmdor> ");
		new_words = spliter(reader, 0);
		new_words = heredoc_controll(new_words);
		words = ft_joindstrs(words, new_words);
		words = check_last(words);
	}
	return (words);
}

void	count_parenthesis(char **words, int *open_prnths, int *close_prnths)
{
	int		i;


	i = 0;
	*open_prnths = 0;
	*close_prnths = 0;
	while (words[i])
	{
		if (*words[i] == '\'' || *words[i] == '\"')
		{
			i++;
			continue ;
		}
		if (ft_chrpos(words[i], '(') != -1)
			(*open_prnths)++;
		if (ft_chrpos(words[i], ')') != -1)
			(*close_prnths)++;
		i++;
	}
}

char	**parenthesis_checker(char **words)
{
	int		open_prnths;
	int		close_prnths;
	char	**new_words;
	char	*reader;

	count_parenthesis(words, &open_prnths, &close_prnths);
	if (close_prnths < open_prnths)
	{
		while (close_prnths < open_prnths)
		{
			reader = readline("parenthesis> ");
			new_words = spliter(reader, 0);
			new_words = heredoc_controll(new_words);
			words = ft_joindstrs(words, new_words);
			words = check_last(words);
			close_prnths++;
		}
		words = parenthesis_checker(words);
	}
	return (words);
}
