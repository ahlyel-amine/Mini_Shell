/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parenthisise_controll.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 19:38:02 by aahlyel           #+#    #+#             */
/*   Updated: 2023/06/12 20:17:57 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*remove_selected_parenthesis(char *line, int i, int j, int k)
{
	char	*tmp;

	j++;
	while (line[i + j] && ft_isspace(line[i + j]))
		j++;
	if (!line[i + j] && k > i)
	{
		tmp = line;
		line = remove_unused_parenthesis(ft_substr(line, i, k - i));
		free(tmp);
	}
	return (line);
}

char	*select_unused_parenthesis(char *line, int i, t_var var, int is_open)
{
	int		j;
	int		is_closed;
	int		k;

	k = 0;
	is_closed = 0;
	j = -1;
	while (line[i + ++j])
	{
		check_out_of_quotes(line[i + j], &var);
		if (line[i + j] == '(' && !var.quote && !var.dquote)
			is_open++;
		else if (line[i + j] == ')' && !var.quote && !var.dquote)
		{
			is_closed++;
			k = i + j;
		}
		if (is_open == is_closed)
		{
			line = remove_selected_parenthesis(line, i, j, k);
			break ;
		}
	}
	return (line);
}

char	*remove_unused_parenthesis(char *line)
{
	int		i;
	int		is_open;
	int		is_closed;
	t_var	var;
	char	*err;

	ft_memset(&var, 0, sizeof(t_var));
	i = 0;
	is_open = 0;
	is_closed = 0;
	while (line[i] && ft_isspace(line[i]))
		i++;
	if (line[i] && line[i] == '(')
	{
		is_open++;
		i++;
	}
	if (is_open)
		line = select_unused_parenthesis(line, i, var, is_open);
	if (is_open && line && !line[skip_spaces_front(line)])
		return (ft_putendl_fd(ERR_ClSD_PARNETHISE, 2), NULL);
	return (line);
}
