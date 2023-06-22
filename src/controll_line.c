/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controll_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 02:53:32 by aahlyel           #+#    #+#             */
/*   Updated: 2023/06/21 19:01:22 by aahlyel          ###   ########.fr       */
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
	int		i;
	int		j;
	t_var	var;

	i = 0;
	ft_memset(&var, 0, sizeof(t_var));
	while (line[i])
	{
		j = 0;
		check_out_of_quotes(line[i], &var);
		if (line[i] == '\"' || line[i] == '\'')
			skip_untl_chr(line, line[i], &i);
		if (!var.dquote && !var.quote && line[i] == '(')
		{
			j = close_parenthise(line + i + 1);
			if (j == -1)
				return (panic(-1), 0);
			i += j + 1;
			continue ;
		}
		if (!var.dquote && !var.quote && line[i] == ')')
			return (panic(-1), 0);
		i++;
	}
	return (1);
}

void	controll_line(char **line)
{
	int			stop;
	t_lsttoken	*new;

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
	(t_components){STDIN_FILENO, STDOUT_FILENO, -1, 0, NULL});
	free_lsttoken(new);
}
