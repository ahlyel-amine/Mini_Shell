/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controll_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 02:53:32 by aahlyel           #+#    #+#             */
/*   Updated: 2023/06/18 17:33:12 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_lsttoken(t_lsttoken *new)
{
	t_lsttoken *tmp;

	while (new)
	{
		tmp = new;
		if (new->t_.type == E_EMPTY && tmp->t_.down)
			free_lsttoken(tmp->t_.down);
		else if (new->t_.type == E_SUBSH)
			free_lsttoken(new->t_.down);
		new = new->next;
		free (tmp);
	}
}

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
	new = tokenize(*line, *line + ft_strlen(*line), 0);
	new = check_tokenize(new);
	if (!get_fds(new))
		return (free_lsttoken(new));
	if (!new)
		return ;
	operator(new, ft_lstokenlast(new), \
	(t_components){STDIN_FILENO, STDOUT_FILENO, 0, NULL});
	free_lsttoken(new);
}


void	print_tokens(t_lsttoken *head)
{
	t_lsttoken *new = head, *tmp;
	while (new)
	{
		if (new->t_.type != E_SPACE && new->t_.type != E_EMPTY)
		{
			if (new->t_.down)
			{
				if (new->t_.type == E_SUBSH)
				{
					printf("-----down_start------\n");
					printf("[%d]\n", new->t_.type);
					print_tokens(new->t_.down);
					printf("-----down_end------\n");
				}
				else
				{
					printf("[%d][%s]\n", new->t_.type, ft_substr(new->t_.line, new->t_.start, new->t_.len));
					printf("-----down_start------\n");
					t_lsttoken	*tmp = new->t_.down;
					while (tmp)
					{
						if (tmp->t_.type != E_SPACE && tmp->t_.type != E_EMPTY)
							printf("[%d][%s]\n", tmp->t_.type, ft_substr(tmp->t_.line, tmp->t_.start, tmp->t_.len));
						else if (tmp->t_.type == E_SPACE)
							printf("[%d][ ]\n", tmp->t_.type);
						tmp = tmp->next;
					}
					printf("-----down_end------\n");
				}
			}
			else
				printf("[%d][%s]\n", new->t_.type, ft_substr(new->t_.line, new->t_.start, new->t_.len));
		}
		else if (new->t_.type == E_SPACE)
			printf("[%d][ ]\n", new->t_.type);
		new = new->next;
	}
}

	// exit(1);
