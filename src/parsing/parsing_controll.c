/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_controll.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 02:53:32 by aahlyel           #+#    #+#             */
/*   Updated: 2023/04/19 23:31:25 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	parsing_controll(t_tree **tree, char *line)
{
	t_line	*lines;
	char	**words;
	(void)tree;
	words = spliter(line, 0);
	words = heredoc_controll(words);
	words = check_last(words);
	words = check_last_pipe(words);
	words = parenthesis_checker(words);
	words_to_args(words);
	int	i = 0;
	while (words && words[i])
	{
		printf(" [%s] ", words[i]);
		free(words[i++]);
	}
	free(words);
	printf("\n");
}