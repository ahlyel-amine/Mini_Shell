/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_str_to_args.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 21:48:07 by aahlyel           #+#    #+#             */
/*   Updated: 2023/05/18 23:14:33 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	arguments_add_back(t_arguments **head, t_arguments *new)
{
	t_arguments	*tmp;

	tmp = *head;
	if (!*head)
	{
		*head = new;
		return ;
	}
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

t_arguments	*still_args(char *str, int *j, int *i, t_arguments *args)
{
	if (ft_isspace(str[*i + *j - 1]))
		args = arguments_constructor(args, ft_strdup(" "), IS_STR);
	else
		args = arguments_constructor(args, ft_substr(str, *i, *j), IS_STR);
	*i += *j;
	return (args);
}

t_arguments	*space_break(char *str, int *j, int *i)
{
	t_arguments	*args;

	args = NULL;
	if(!ft_isspace(str[*i + *j]) && str[*i + *j])
	{
		if (*j)
			args = arguments_constructor(args, ft_strdup(" "), IS_STR);
		*i += *j;
		*j = 0;
	}
	return (args);
}

void	space_break_loop(char *str, int *i, int *j, t_arguments **args)
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

t_arguments	*no_space_break(char *str, int *j, int *i)
{
	t_arguments	*args;

	args = NULL;
	if(ft_isspace(str[*i + *j]) && str[*i + *j])
	{
		if (*j)
			args = arguments_constructor(args, ft_substr(str, *i, *j), IS_STR);
		*i += *j;
		*j = 0;
	}
	return (args);
}

void	no_space_break_loop(char *str, int *i, int *j, t_arguments **args)
{
	t_arguments	*tmp;

	while (str[*i + *j])
	{
		tmp = no_space_break(str, j, i);
		if (tmp)
		{
			arguments_add_back(args, tmp);
			break ;
		}
		(*j)++;
	}
}

t_arguments	*ft_split_str_to_args(char *str)
{
	t_arguments	*args;
	int			i;
	int			j;

	i = 0;
	args = NULL;
	while (str[i])
	{
		j = 0;
		space_break_loop(str, &i, &j, &args);
		no_space_break_loop(str, &i, &j, &args);
		if (j)
			args = still_args(str, &j, &i, args);
	}
	t_arguments *a;
	a = args;
	while (a)
	{
		printf("%s\n", a->str);
		a = a->next;
	}
	return (args);
}

