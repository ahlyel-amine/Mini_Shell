/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_parser_tools2.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 18:04:15 by aahlyel           #+#    #+#             */
/*   Updated: 2023/06/15 03:54:49 by aahlyel          ###   ########.fr       */
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

static t_arguments	*fill_last_argument(t_arguments *arguments, \
char *line, int *i, int j)
{
	arguments = arguments_constructor(arguments, ft_substr(line, *i, j), \
			IS_STR, 0);
	*i += j;
	return (arguments);
}

t_arguments	*get_names(char *line, int *i)
{
	t_arguments	*arguments;
	t_var		var;
	int			j;

	ft_memset(&var, 0, sizeof(t_var));
	arguments = NULL;
	j = 0;
	while (line[*i + j])
	{
		check_out_of_quotes(line[*i + j], &var);
		arguments = fill_arguments(arguments, &var, (t_2ptr_int){i, &j}, line);
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
		arguments = fill_last_argument(arguments, line, i, j);
	merge_arguments(&arguments, 0);
	tokenize_variables(&arguments);
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
char	*get_filename(char *line, char *endline)
{
	t_arguments	*arguments;
	t_var		var;
	int			j;
	int			i;

	ft_memset(&var, 0, sizeof(t_var));
	arguments = NULL;
	j = 0;
	i = 0;
	while (line[i + j] && line + i + j != endline)
	{
		check_out_of_quotes(line[i + j], &var);
		arguments = fill_arguments(arguments, &var, (t_2ptr_int){&i, &j}, line);
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
		arguments = fill_last_argument(arguments, line, &i, j);
	merge_arguments(&arguments, 0);
	tokenize_variables(&arguments);
	arguments = transform_args_fd_name(&arguments);
	if (!arguments)
		return NULL;
	char *ret = args_to_str(arguments);
	arguments_destructor(&arguments);
	printf("%s\n", ret);
	return (ret);
}
