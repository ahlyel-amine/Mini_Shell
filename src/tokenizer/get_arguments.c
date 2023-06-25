/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_arguments.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 19:31:01 by aahlyel           #+#    #+#             */
/*   Updated: 2023/06/25 14:34:32 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	close_dquote(t_arguments **arguments, char *line, int i)
{
	t_var		var;
	int			j;

	var.dquote = 1;
	var.quote = 0;
	j = 0;
	while (line[i + j])
	{
		check_out_of_quotes(line[i + j], &var);
		if (!var.dquote)
		{
			*arguments = arguments_constructor(*arguments, \
			ft_substr(line, i, j), DQUOTE, 0);
			break ;
		}
		j++;
	}
	return (j);
}

int	close_quote(t_arguments **arguments, char *line, int i)
{
	t_var		var;
	int			j;

	var.dquote = 0;
	var.quote = 1;
	j = 0;
	while (line[i + j])
	{
		check_out_of_quotes(line[i + j], &var);
		if (!var.quote)
		{
			*arguments = arguments_constructor(*arguments, \
			ft_substr(line, i, j), QUOTE, 0);
			break ;
		}
		j++;
	}
	return (j);
}

static t_arguments	*fill_arguments(t_arguments *arguments, \
t_var *var, t_2ptr_int a, char *line)
{
	if (var->dquote && line[*(a.i) + *(a.k)] == '\"')
	{
		if (*(a.k))
			arguments = arguments_constructor(arguments, \
			ft_substr(line, *(a.i), *(a.k)), IS_STR, 0);
		*(a.i) += *(a.k) + 1;
		*(a.i) += close_dquote(&arguments, line, *(a.i)) + 1;
		var->dquote = 0;
		*(a.k) = -1;
	}
	else if (var->quote && line[*(a.i) + *(a.k)] == '\'')
	{
		if (*(a.k))
			arguments = arguments_constructor(arguments, \
			ft_substr(line, *(a.i), *(a.k)), IS_STR, 0);
		*(a.i) += *(a.k) + 1;
		*(a.i) += close_quote(&arguments, line, *(a.i)) + 1;
		var->quote = 0;
		*(a.k) = -1;
	}
	return (arguments);
}

t_arguments	*get_arguments(char *line, int i, int flg)
{
	t_arguments	*arguments;
	t_var		var;
	int			j;

	ft_memset(&var, 0, sizeof(t_var));
	arguments = NULL;
	j = 0;
	while (line[i + j])
	{
		if (flg)
			check_out_of_quotes(line[i + j], &var);
		arguments = fill_arguments(arguments, &var, (t_2ptr_int){&i, &j}, line);
		if (j == -1)
		{
			j = 0;
			continue ;
		}
		j++;
	}
	if (j)
		arguments = arguments_constructor(arguments, \
		ft_substr(line, i, j), IS_STR, 0);
	return (arguments);
}

t_arguments	*get_argument(char *line, int i, int flg)
{
	t_arguments	*arguments;

	arguments = get_arguments(line, i, flg);
	merge_arguments(&arguments, 0);
	tokenize_variables(&arguments);
	return (arguments);
}
