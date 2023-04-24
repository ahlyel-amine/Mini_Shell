/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_controll.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 02:53:32 by aahlyel           #+#    #+#             */
/*   Updated: 2023/04/24 10:00:46 by aahlyel          ###   ########.fr       */
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
	i = 0;
	while (words && words[i])
	{
		printf(" [%s] ", words[i]);
		free(words[i++]);
	}
	free(words);
}