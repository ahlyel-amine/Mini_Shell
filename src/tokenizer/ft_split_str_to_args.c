/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_str_to_args.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 21:48:07 by aahlyel           #+#    #+#             */
/*   Updated: 2023/06/13 00:58:31 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static t_arguments	*space_break(char *str, int *j, int *i)
{
	t_arguments	*args;

	args = NULL;
	if (ft_isspace(str[*i + *j]) && str[*i + *j])
	{
		if (*j)
			args = arguments_constructor(args, \
			ft_substr(str, *i, *j), IS_STR, 0);
		*i += *j;
		*j = 0;
	}
	return (args);
}

static void	space_break_loop(char *str, int *i, int *j, t_arguments **args)
{
	t_arguments	*tmp;

	while (str[*i + *j])
	{
		tmp = space_break(str, j, i);
		if (tmp)
		{
			arguments_add_back(args, tmp);
			break ;
		}
		(*j)++;
	}
}

static t_arguments	*no_space_break(char *str, int *j, int *i, int is_dquote)
{
	t_arguments	*args;

	args = NULL;
	if (!ft_isspace(str[*i + *j]) && str[*i + *j])
	{
		if (*j && is_dquote)
			args = arguments_constructor(args, \
			ft_substr(str, *i, *j), IS_STR, 0);
		else if (*j && !is_dquote)
			args = arguments_constructor(args, ft_strdup(" "), IS_SEPARTOR, 0);
		*i += *j;
		*j = 0;
	}
	return (args);
}

static void	no_space_break_loop(char *str, int *i, int *j, t_arguments **args)
{
	t_arguments	*tmp;
	static int	is_dquote;

	if (!str && !j && !args)
	{
		is_dquote = *i;
		return ;
	}
	while (str[*i + *j])
	{
		tmp = no_space_break(str, j, i, is_dquote);
		if (tmp)
		{
			arguments_add_back(args, tmp);
			break ;
		}
		(*j)++;
	}
}

t_arguments	*ft_split_str_to_args(char *str, int is_dquote)
{
	t_arguments	*args;
	int			i;
	int			j;

	i = 0;
	args = NULL;
	no_space_break_loop(NULL, &is_dquote, NULL, NULL);
	still_args(NULL, &is_dquote, NULL, NULL);
	if (ft_isspace(str[i]))
	{
		i += skip_spaces_front(str);
		if (is_dquote)
			args = arguments_constructor(args, ft_substr(str, 0, i), IS_STR, 0);
		else
			args = arguments_constructor(args, ft_strdup(" "), IS_SEPARTOR, 0);
	}
	while (str[i])
	{
		j = 0;
		space_break_loop(str, &i, &j, &args);
		no_space_break_loop(str, &i, &j, &args);
		if (j)
			args = still_args(str, &j, &i, args);
	}
	return (args);
}
