/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controll_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 02:53:32 by aahlyel           #+#    #+#             */
/*   Updated: 2023/06/19 10:20:54 by aahlyel          ###   ########.fr       */
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
	if (!(*line)[skip_spaces_front(*line)])
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
