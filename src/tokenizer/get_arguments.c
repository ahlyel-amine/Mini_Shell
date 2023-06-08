/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_arguments.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 19:31:01 by aahlyel           #+#    #+#             */
/*   Updated: 2023/06/08 14:28:36 by aahlyel          ###   ########.fr       */
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
			*arguments = arguments_constructor(*arguments, ft_substr(line, i, j), DQUOTE, 0);
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
			*arguments = arguments_constructor(*arguments, ft_substr(line, i, j), QUOTE, 0);
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

	ft_memset(&var, 0, sizeof(t_var));
	arguments = NULL;
	j = 0;
	while (line[*i + j])
	{
		check_out_of_quotes(line[*i + j], &var);
		if (var.dquote && line[*i + j] == '\"')
		{
			if (j)
				arguments = arguments_constructor(arguments, ft_substr(line, *i, j), IS_STR, 0);
			*i += j + 1;
			*i += close_dquote(&arguments, line, *i) + 1;
			var.dquote = 0;
			j = 0;
			continue ;
		}
		else if (var.quote && line[*i + j] == '\'')
		{
			if (j)
				arguments = arguments_constructor(arguments, ft_substr(line, *i, j), IS_STR, 0);		
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
		arguments = arguments_constructor(arguments, ft_substr(line, *i, j), IS_STR, 0);
		*i += j;
	}
	return (arguments);
}

void	remove_arg(t_arguments **arguments, t_arguments **to_remove)
{
	t_arguments *tmp;
	t_arguments *rem;
	tmp = *arguments;
	// if (!(*arguments)->next)
	// 	*arguments = NULL;
	while (tmp)
	{
		if (!tmp->next && tmp == *to_remove)
		{
			tmp = NULL;
			break;
		}
		else if (tmp->next == *to_remove)
		{
			tmp = tmp->next->next;
			break;	
		}
	}
	free ((*to_remove)->str);
	free (*to_remove);
	*to_remove = tmp;
}

void	merge_arguments(t_arguments **arguments, int is_dquote)
{
	t_arguments	*head;
	t_arguments	*new;
	t_arguments	*tmp;

	if (!*arguments)
		return ;
	new = NULL;
	head = *arguments;
	while (head)
	{
		if (head->type & IS_STR)
		{
			new = ft_split_str_to_args(head->str, is_dquote);
			if (new)
			{
				tmp = head;
				replace_arg(arguments, &head, new);
				free (tmp->str);
				free(tmp);
			}
		}
		else if (head->type & DQUOTE)
			merge_arguments(&head->down, 1);
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
	merge_arguments(&arguments, 0);
	tokenize_variables(&arguments);
	return (arguments);
}
