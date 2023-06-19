/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controll_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 02:53:32 by aahlyel           #+#    #+#             */
/*   Updated: 2023/06/19 18:51:19 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	skip_untl_chr(char *line, char c, int *i)
{
	while (line[*i])
	{
		if (line[*i] == c)
			break ;
		(*i)++;
	}
}

static int	check_line(char *line)
{
	int	i;
	int	j;

	i = 0;
	while (line[i])
	{
		j = 0;
		if (line[i] == '(')
		{
			j = close_parenthise(line + i + 1);
			if (j == -1)
				return (panic_recursive(ERR_UNCLSDP, NULL), 0);
			i += j + 1;
			continue ;
		}
		if (line[i] == '\"')
			skip_untl_chr(line, '\"', &i);
		if (line[i] == '\'')
			skip_untl_chr(line, '\'', &i);
		if (line[i] == ')')
			return (panic_recursive(ERR_CLSD_PARNETHISE, NULL), 0);
		i++;
	}
	return (1);
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
	if (!(*line)[skip_spaces_front(*line)])
		return ;
	if (!check_line(*line))
		return ;
	new = tokenize(*line, *line + ft_strlen(*line), 0);
	new = check_tokenize(new);
	if (!get_fds(new))
		return (free_lsttoken(new));
	if (!new)
		return ;
	operator(new, ft_lstokenlast(new), \
	(t_components){NULL, STDIN_FILENO, STDOUT_FILENO, 0});
	free_lsttoken(new);
}
