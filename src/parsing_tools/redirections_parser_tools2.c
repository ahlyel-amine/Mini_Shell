/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_parser_tools2.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 18:04:15 by aahlyel           #+#    #+#             */
/*   Updated: 2023/06/19 18:34:29 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_isname(char c)
{
	return (c != '&' && c != '|' && c != '<' && c != '>' && c != ' ');
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
	else if (!var->dquote && !var->quote && !ft_isname(line[*(a.i) + *(a.k)]))
		*(a.k) = -2;
	return (arguments);
}

t_arguments	*transform_args_fd_name(t_arguments **args)
{
	char		*str;
	t_arguments	*nl;

	nl = NULL;
	expand_line(*args);
	args_join(args);
	args_move_down(args, &nl);
	str = args_to_str(*args);
	if (ft_strchr(str, '*'))
	{
		nl = *args;
		while (nl->next)
			nl = nl->next;
		nl->next = arguments_constructor(NULL, str, IS_STR, 0);
		wild_cards(&nl->next);
		if (nl->next->next)
			return (ft_putstr_fd(ERR_AMBGIS, 2), NULL);
		return (nl->next);
	}
	else
		return (free (str), *args);
}

char	*transform_filename(t_arguments *arguments)
{
	char	*filename;

	merge_arguments(&arguments, 0);
	tokenize_variables(&arguments);
	arguments = transform_args_fd_name(&arguments);
	if (!arguments)
		return (NULL);
	filename = args_to_str(arguments);
	arguments_destructor(&arguments);
	return (filename);
}

char	*get_filename(char *line, char *endline)
{
	t_arguments	*arg;
	t_var		var;
	int			j;
	int			i;

	ft_memset(&var, 0, sizeof(t_var));
	arg = NULL;
	j = 0;
	i = 0;
	while (line[i + j] && line + i + j != endline)
	{
		check_out_of_quotes(line[i + j], &var);
		arg = fill_arguments(arg, &var, (t_2ptr_int){&i, &j}, line);
		if (j == -1)
		{
			j = 0;
			continue ;
		}
		else if (j == -2)
			break ;
		j++;
	}
	if (j)
		arg = arguments_constructor(arg, ft_substr(line, i, j), IS_STR, 0);
	return (transform_filename(arg));
}
