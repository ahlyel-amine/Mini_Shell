/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_arguments.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 19:31:01 by aahlyel           #+#    #+#             */
/*   Updated: 2023/05/20 20:44:48 by aahlyel          ###   ########.fr       */
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
			*arguments = arguments_constructor(*arguments, ft_substr(line, i, j), DQUOTE);
			break;
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
			*arguments = arguments_constructor(*arguments, ft_substr(line, i, j), QUOTE);
			break;
		}
		j++;
	}
	return (j);
}

t_arguments	*get_arguments(char *line, int *i, int is_word)
{
	t_arguments	*arguments;
	t_var		var;
	int			j;

	set_zero_var(&var);
	arguments = NULL;
	j = 0;
	while (line[*i + j])
	{
		check_out_of_quotes(line[*i + j], &var);
		if (var.dquote && line[*i + j] == '\"')
		{
			if (j)
				arguments = arguments_constructor(arguments, ft_substr(line, *i, j), IS_STR);
			*i += j + 1;
			*i += close_dquote(&arguments, line, *i) + 1;
			var.dquote = 0;
			j = 0;
			continue ;
		}
		else if (var.quote && line[*i + j] == '\'')
		{
			if (j)
				arguments = arguments_constructor(arguments, ft_substr(line, *i, j), IS_STR);
			*i += j + 1;
			*i += close_quote(&arguments, line, *i) + 1;
			var.quote = 0;
			j = 0;
			continue ;
		}
		else if (ft_isspace(line[*i + j]) && is_word)
			break;
		j++;
	}
	if (j)
	{
		arguments = arguments_constructor(arguments, ft_substr(line, *i, j), IS_STR);
		*i += j;
	}
	return (arguments);
}

void	merge_arguments(t_arguments **arguments, int is_dquote)
{
	t_arguments	*head;
	t_arguments	*new = NULL;
	t_arguments	*tmp;
	t_arguments	*prev = NULL;
	char		**splited;
	int			i;

	if (!*arguments)
		return ;
	head = *arguments;
	prev = head;
	while (head)
	{
		i = 0;
		if (head->type & IS_STR)
		{
			tmp = head->next;
			new = ft_split_str_to_args(head->str, is_dquote);
			if (head == prev)
				*arguments = new;
			else
				prev->next = new;
			prev = new;
			while (new && new->next)
				new = new->next;
			if (new)
			new->next = tmp;
			head = prev;
		}
		else if (head->type & DQUOTE)
			merge_arguments(&head->down, 1);
		prev = head;
		head = head->next;
	}
}

t_arguments	*get_argument(char *line, int *j, int i, int is_word)
{
	t_arguments	*arguments;
	
	arguments = NULL;

	if (is_word)
		arguments = get_arguments(line, j, is_word);
	else
		arguments = get_arguments(line, &i, is_word);
	static int call;
	call++;
	
	merge_arguments(&arguments, 0);
	// if (call == 2)
	// 	exit(1);
	// print_arguments(arguments);
		print_arguments(arguments);
	tokenize_variables(&arguments);
		print_arguments(arguments);
	// print_arguments(arguments);
	return (arguments);
}