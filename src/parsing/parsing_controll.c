/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_controll.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 02:53:32 by aahlyel           #+#    #+#             */
/*   Updated: 2023/04/23 19:04:48 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	parsing_controll(t_tree **tree, char *line)
{
	char	**words;
	(void)tree;
	words = spliter(line);
	t_arg *a = new_arg(0, 0, 1);
	int	i = 0;
	while (a)
	{
		printf("%d: [%s][%d]\n",i++, a->token, a->x_token);
		a = a->next;
	}
	new_arg(0, 0, -1);
	// words = heredoc_controll(words);
	// words = check_last(words);
	// words = check_last_pipe(words);
	// words = parenthesis_checker(words);
	// words = parser(words);
	// tokenizer(words);
		i = 0;
	while (words && words[i])
	{
		printf(" [%s] ", words[i]);
		free(words[i++]);
	}
	free(words);
	printf("\n");
}