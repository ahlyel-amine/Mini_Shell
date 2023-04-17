/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_controll.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 02:53:32 by aahlyel           #+#    #+#             */
/*   Updated: 2023/04/17 21:21:29 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	parsing_controll(t_tree **tree, char *line)
{
	char	**words;
	(void)tree;
	words = spliter(line, 0);
	// if (is_quote)
	// 	return ;
	// words = ft_split(line, ' ');

	while (words && *words)
		printf(" [%s] ",*words++);
	printf("\n");
}