/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 12:40:17 by aahlyel           #+#    #+#             */
/*   Updated: 2023/06/08 12:13:27 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../include/minishell.h"

static int	parhenthises_closed(char *line, int *k, int *i)
{
	int		is_closed;
	int		is_open;
	t_var	var;

	ft_memset(&var, 0, sizeof(t_var));
	*i = -1;
	is_open = 1;
	is_closed = 0;
	while (line[++(*i)])
	{
		check_out_of_quotes(line[*i], &var);
		if (line[*i] == '(' && !var.quote && \
		!var.dquote && is_open != is_closed)
			is_open++;
		else if (line[*i] == ')' && !var.quote && \
		!var.dquote && is_open != is_closed)
		{
			is_closed++;
			*k = *i;
			continue ;
		}
		if (is_open == is_closed)
			return (1);
	}
	return (0);
}

int	close_parenthise(char *line)
{
	int	i;
	int	open;
	int	close;
	t_var	var;

	i = 0;
	ft_memset(&var, 0, sizeof(t_var));
	open = 1;
	close = 0;
	while (line[i])
	{
		check_out_of_quotes(line[i], &var);
		if (line[i] == '(' && !var.dquote && !var.quote)
			open++;
		else if (line[i] == ')' && !var.dquote && !var.quote)
			close++;
		i++;
		if (close == open)
		{
			i++;
			break ;
		}
	}
	if (close != open)
		return (-1);
	return (i);
}

void	something_wrong(char *error, void *to_free)
{
	free(to_free);
	ft_putstr_fd(error, 2);
	set__get_option_variables(0, FREE);
	exit(1);
}

void	check_out_of_quotes(char c, t_var *var)
{
	if (c == '\"' && !(var->quote))
			(var->dquote) = !(var->dquote);
	if (c == '\'' && !(var->dquote))
		(var->quote) = !(var->quote);
}
void	transform_dollar(char *line, int *i, int *k, char **tmp)
{
	if (ft_isdigit(line[*i + 1]))
		*i += 2;
	else if (line[*i] == '$' && (!line[*i + 1] || ft_isspace(line[*i + 1])))
		(*tmp)[(*k)++] = line[(*i)++];
	else if (line[*i] == '$' && line[*i + 1] == '$')
		(*tmp)[(*k)++] = line[(*i)++];
	else if (line[*i] == '$')
	{
		(*i)++;
		(*tmp)[(*k)++] = '\"';
		while (ft_isalnum(line[*i]) || line[*i] == '_')
			(*tmp)[(*k)++] = line[(*i)++];
		(*tmp)[(*k)++] = '\"';
	}
}

int	delete_quotes(char *line, char **tmp, int i, int is_word)
{
	t_var	var;
	int		k;

	k = 0;
	ft_memset(&var, 0, sizeof(t_var));
	while (line[i])
	{
		check_out_of_quotes(line[i], &var);
		if (!var.quote && !var.dquote && ft_isspace(line[i]))
		{
			if (is_word)
				break ;
			(*tmp)[k++] = line[i];
		}
		else if ((line[i] == '\"' && var.quote) || (line[i] == '\'' && var.dquote))
			(*tmp)[k++] = line[i];
		else if (line[i] == '$' && (var.dquote || (!var.dquote && !var.quote)))
		{
			transform_dollar(line, &i, &k, tmp);
			continue ;
		}
		else if (line[i] != '\'' && line[i] != '\"')
			(*tmp)[k++] = line[i];
		i++;
	}
	return (i);
}

int	count_dollars(char *line, int *i, int j)
{
	int begin;
	int dollars;
	
	if (i)
		begin = *i;
	else
		begin = j;
	dollars = 0;
	while (line[begin])
	{
		if (line[begin] == '$')
			dollars++;
		begin++;
	}
	return (begin);
}

// void	get_dollars(t_arguments	**arguments, char *line, int *i, int *j)
// {
// 	int	k;

// 	k = 1;
// 	*i += *j;
// 	*j = 0;
// 	if (ft_isdigit(line[*i + 1]))
// 		*i += 2;
// 	// else if (line[*i] == '$'  && line[*i + k] == '\"')
// 	// 	(*i)++;
// 	else if (line[*i] == '$'  && !(ft_isalnum(line[*i + k]) || line[*i + k] == '_'))
// 		(*j)++;
// 	else if (line[*i] == '$' && line[*i + 1] == '$')
// 		(*j)++;
// 	else if (line[*i] == '$' && (ft_isalnum(line[*i + k]) || line[*i + k] == '_'))
// 	{
// 		while (ft_isalnum(line[*i + k]) || line[*i + k] == '_')
// 			k++;
// 		*arguments = arguments_constructor(*arguments, ft_substr(line, *i, k), IS_VARIABLE);
// 		*i += k;
// 	}
// }

// t_arguments	*get_arguments(char *line, int *i, int is_word)
// {
// 	t_arguments	*arguments;
// 	t_var		var;
// 	int			j;

// 	ft_memset(&var, 0, sizeof(t_var));
// 	arguments = NULL;
// 	j = 0;
// 	while (line[*i + j])
// 	{
// 		check_out_of_quotes(line[*i + j], &var);
// 		if ((var.dquote && line[*i + j] == '\"') || (var.quote && line[*i + j] == '\''))
// 		{
// 			if (j)
// 				arguments = arguments_constructor(arguments, ft_substr(line, *i, j), IS_STR );
// 			*i += j + 1;
// 			j = 0;
// 			continue ;
// 		}
// 		if (!var.quote && !var.dquote && ft_isspace(line[*i + j]))
// 		{
// 			if (is_word)
// 				break;
// 			if (j)
// 				arguments = arguments_constructor(arguments, ft_substr(line, *i, j), IS_STR);
// 			*i += j + 1;
// 			j = 0;
// 			continue ;
// 		}
// 		else if ((line[*i + j] == '\"' && var.quote) || (line[*i + j] == '\'' && var.dquote))
// 			j++;
// 		else if (!var.dquote && !var.quote && (line[*i + j] == '\'' || line[*i + j] == '\"'))
// 		{
// 			if (j)
// 				arguments = arguments_constructor(arguments, ft_substr(line, *i, j), IS_STR | DONT_EXPAND_WILD_CARDS);
// 			*i += j + 1;
// 			j = 0;
// 			continue ;
// 		}
// 		else if (line[*i + j] == '$' && (var.dquote || (!var.dquote && !var.quote)))
// 		{
// 			if (j)
// 				arguments = arguments_constructor(arguments, ft_substr(line, *i, j), IS_STR);
// 			get_dollars(&arguments, line, i, &j);
// 			continue ;
// 		}
// 		else if (line[*i + j] && line[*i + j] != '\'' && line[*i + j] != '\"')
// 			j++;
// 	}
// 	if (j)
// 	{
// 		arguments = arguments_constructor(arguments, ft_substr(line, *i, j), IS_STR);
// 		*i += j;
// 	}
	
// 	return (arguments);
// }




// t_arguments	*split_merged(t_arguments *arguments)
// {
// 	char	**str;
// 	int		len;
// 	int		i;
// 	t_arguments	*head;
// 	t_arguments	*new = NULL;
// 	t_arguments	*tmp;

// 	i = 0;
// 	head = arguments;
// 	if (head->type == 1)
// 	{
// 		str = ft_split(head->str, ' ');
// 		len = ft_double_strlen(str);
// 		tmp = head->next;
// 		free(head->str);
// 		free (head);
// 		while (i < len)
// 				new = arguments_constructor(new, str[i++], IS_STR | MERGED);
// 		free (str);
// 		head = new;
// 		while (new->next)
// 			new = new->next;
// 		new->next = tmp;
// 		arguments = head;
// 	}
// 	while (head->next)
// 	{
// 		new = NULL;
// 		i = 0;
// 		if (head->next->type == 1)
// 		{

// 			str = ft_split(head->next->str, ' ');
// 			len = ft_double_strlen(str);
// 			if (len == 1)
// 			{
// 				free (str[i]);
// 				free (str);
// 				head = head->next;
// 				continue ;
// 			}
// 			while (i < len)
// 				new = arguments_constructor(new, str[i++], IS_STR | MERGED);
// 			free (str);
// 			tmp = (head->next)->next;
// 			free(head->next->str);
// 			free (head->next);
// 			head->next = new;
// 			while (new->next)
// 				new = new->next;
// 			new->next = tmp;
// 		}
// 		head = head->next;
// 	}
// 	return (arguments);
// }

// t_arguments	*merge_arguments(t_arguments *arguments)
// {
// 	t_arguments	*head;
// 	t_arguments	*tmp;

// 	if (!arguments)
// 		return (NULL);
// 	head = arguments;
// 	while (head->next)
// 	{
// 		if (head->type == head->next->type && head->type != 0)
// 		{
// 			tmp = head->next;
// 			head->str = ft_strjoin_free(head->str, ft_strdup(" "));
// 			head->str = ft_strjoin_free(head->str, (head->next)->str);
// 			head->next = (head->next)->next;
// 			free (tmp);
// 		}
// 		else
// 			head = head->next;
// 	}
// 	return (split_merged(arguments));
// }



char	*skip_quotes(char *line, int *i, int j, int is_word)
{
	char		*tmp;
	int			a;
	t_arguments	*arguments;

	a = count_dollars(line, i, j);
	if (is_word)
		tmp = ft_calloc(1, ft_strlen(line + *i) + a + 1);
	else
		tmp = ft_calloc(1, ft_strlen(line + j) + a + 1);
	if (!tmp)
		return (NULL);
	if (is_word)
		*i = delete_quotes(line, &tmp, *i, is_word);
	else
		delete_quotes(line, &tmp, j, is_word);
	return (tmp);
}

int	skip_spaces_front(char *line)
{
	int	i;

	i = 0;
	while (ft_isspace(line[i]))
		i++;
	return (i);
}

void	pr_custom_err(char *error, void *ptr, char *custom)
{
	char	*msg;

	msg = ft_strjoin(error, custom);
	ft_putstr_fd(msg, 2);
	ft_putchar_fd('\n', 2);
	free(msg);
	free (ptr);
}
void	panic_recursive(char *error, char **ptr)
{
	ft_putstr_fd(error, STDERR_FILENO);
	free (*ptr);
	*ptr = NULL;
}

unsigned short	check_wild_cards(char *str, unsigned short type)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '*')
		{
			i = -1;
			break ;
		}
		i++;
	}
	if (type == 3 && i != -1)
		type = 1;
	return (type);
}
// t_arguments *tokenize_variables(t_arguments *arguments, int type)
// {
// 	int		i;
// 	int		j;
// 	int		is_var;
// 	char	*tmp;
	
// 	i = 0;
// 	j = 0;
// 	is_var = 0;
// 	if (!arguments || !arguments->str)
// 		return (NULL);
// 	tmp = arguments->str;
// 	while (tmp[i + j] && !(type & QUOTE))
// 	{
// 		if (tmp[i + j] == '$' && !ft_isdigit(tmp[i + j + 1]) && ft_isvariable(tmp[i + j + 1]))
// 		{
// 			is_var++;
// 			if (is_var == 1)
// 			{
// 				free(arguments);
// 				arguments = NULL;
// 			}
// 			if (j)
// 				arguments = arguments_constructor(arguments, ft_substr(tmp, i, j), IS_STR);
// 			i += j + 1;
// 			j = 0;
// 			while (ft_isvariable(tmp[i + j]))
// 				j++;
// 			arguments = arguments_constructor(arguments, ft_substr(tmp, i, j), IS_VARIABLE);
// 			i += j;
// 			j = -1;
// 		}
// 		else if (tmp[i + j] == '$' && ft_isdigit(tmp[i + j + 1]))
// 		{
// 			is_var++;
// 			if (is_var == 1)
// 			{
// 				free(arguments);
// 				arguments = NULL;
// 			}
// 			if (j)
// 				arguments = arguments_constructor(arguments, ft_substr(tmp, i, j), IS_STR);
// 			i += j + 2;
// 			j = -1;
// 		}
// 		j++;
// 	}
// 	if (j && is_var)
// 		arguments = arguments_constructor(arguments, ft_substr(tmp, i, j), IS_STR);
// 	if (is_var)
// 		free(tmp);

// 	return (arguments);
// }



