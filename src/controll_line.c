/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controll_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 02:53:32 by aahlyel           #+#    #+#             */
/*   Updated: 2023/06/17 19:22:53 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	controll_line(char **line)
{
	int			len;
	int			stop;
	t_lsttoken	*new;
	t_lsttoken	*subs;
	stop = 0;
	complete_line(line, &stop);
	if (stop)
		return ;
	new = tokenize(*line);
	if (!new)
		return ;
	operator(new, ft_lstokenlast(new), \
	(t_components){STDIN_FILENO, STDOUT_FILENO, 0, NULL});
}



	// 		while (new)
	// {
	// 	if (new->t_.type != E_SPACE && new->t_.type != E_EMPTY)
	// 	{
	// 		if (new->t_.down)
	// 		{
	// 			if (new->t_.type != E_SUBSH)
	// 			printf("[%d][%s]\n", new->t_.type, ft_substr(new->t_.line, new->t_.start, new->t_.len));
	// 			else if (new->t_.type == E_SUBSH)
	// 			printf("[%d]\n", new->t_.type);
	// 			printf("-----down_start------\n");
	// 			t_lsttoken	*tmp = new->t_.down;
	// 			while (tmp)
	// 			{
	// 				if (tmp->t_.type != E_SPACE && tmp->t_.type != E_EMPTY)
	// 					printf("[%d][%s]\n", tmp->t_.type, ft_substr(tmp->t_.line, tmp->t_.start, tmp->t_.len));
	// 				else if (tmp->t_.type == E_SPACE)
	// 					printf("[%d][ ]\n", tmp->t_.type);
	// 				tmp = tmp->next;
	// 			}
	// 			printf("-----down_end------\n");
	// 		}
	// 		else
	// 			printf("[%d][%s]\n", new->t_.type, ft_substr(new->t_.line, new->t_.start, new->t_.len));
	// 	}
	// 	else if (new->t_.type == E_SPACE)
	// 		printf("[%d][ ]\n", new->t_.type);
	// 	new = new->next;
	// }
	// exit(1);
