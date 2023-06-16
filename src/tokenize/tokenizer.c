/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 17:54:06 by aahlyel           #+#    #+#             */
/*   Updated: 2023/06/16 19:20:21 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_lsttoken	*new_token(t_token t_)
{
	t_lsttoken	*node;

	node = (t_lsttoken *)malloc(sizeof(t_lsttoken));
	if (node)
	{
		node->t_ = t_;
		node->next = NULL;
	}
	return (node);
}

t_lsttoken	*ft_lstokenlast(t_lsttoken *lst)
{
	if (lst)
	{
		while (lst->next)
			lst = lst->next;
	}
	return (lst);
}

void	ft_lstokenadd_back(t_lsttoken **lst, t_lsttoken *new)
{
	t_lsttoken	*tmp;

	tmp = NULL;
	if (!new || !lst)
		return ;
	if (!*lst)
		*lst = new;
	else
	{
		tmp = ft_lstokenlast(*lst);
		tmp->next = new;
	}
}

int	subsh_token(t_lsttoken **head, char *line, int *i)
{
	int	j;

	j = 0;
	if (line[*i] == '(')
	{
		j = close_parenthise(line + *i + 1);
		if (j == -1)
			return (panic_recursive(ERR_UNCLSDP, NULL), -1);
		ft_lstokenadd_back(head, new_token((t_token){E_SUBSH, line, *i + 1, j
				- 1, NULL}));
		*i += j + 1;
		return (1);
	}
	return (0);
}

int	quote_token(t_lsttoken **head, char *line, int *i)
{
	int	j;

	j = 0;
	if (line[*i] == '\"')
	{
		j = 1;
		while (line[*i + j] && line[*i + j] != '\"')
			j++;
		ft_lstokenadd_back(head, new_token((t_token){E_DQUOTE, line, *i, j + 1,
				NULL}));
		*i += j + 1;
		return (1);
	}
	else if (line[*i] == '\'')
	{
		j = 1;
		while (line[*i + j] && line[*i + j] != '\'')
			j++;
		ft_lstokenadd_back(head, new_token((t_token){E_QUOTE, line, *i, j + 1,
				NULL}));
		*i += j + 1;
		return (1);
	}
	return (0);
}

int	operator_token(t_lsttoken **head, char *line, int *i)
{
	int	j;

	j = 0;
	if (line[*i] == '&')
	{
		if (line[*i + 1] != '&')
			return (panic_recursive(ERR_1AND, NULL), -1);
		ft_lstokenadd_back(head, new_token((t_token){E_AND, line, *i, 2,
				NULL}));
		*i += 2;
		return (1);
	}
	else if (line[*i] == '|' && line[*i + 1] == '|')
	{
		ft_lstokenadd_back(head, new_token((t_token){E_OR, line, *i, 2, NULL}));
		*i += 2;
		return (1);
	}
	return (0);
}

int	pipe_token(t_lsttoken **head, char *line, int *i)
{
	int	j;

	j = 0;
	if (line[*i] == '|')
	{
		ft_lstokenadd_back(head, new_token((t_token){E_PIPE, line, *i, 1,
				NULL}));
		*i += 1;
		return (1);
	}
	return (0);
}

int	red_right_token(t_lsttoken **head, char *line, int *i)
{
	int	j;

	j = 0;
	if (line[*i] == '>' && line[*i + 1] == '>')
	{
		ft_lstokenadd_back(head, new_token((t_token){E_APPEND, line, *i, 2,
				NULL}));
		*i += 2;
		return (1);
	}
	else if (line[*i] == '>')
	{
		ft_lstokenadd_back(head, new_token((t_token){E_OUTRED, line, *i, 1,
				NULL}));
		*i += 1;
		return (1);
	}
	return (0);
}

int	red_left_token(t_lsttoken **head, char *line, int *i)
{
	int	j;

	j = 0;
	if (line[*i] == '<' && line[*i + 1] == '<')
	{
		ft_lstokenadd_back(head, new_token((t_token){E_HEREDOC, line, *i, 2,
				NULL}));
		*i += 2;
		return (1);
	}
	else if (line[*i] == '<')
	{
		ft_lstokenadd_back(head, new_token((t_token){E_INRED, line, *i, 1,
				NULL}));
		*i += 1;
		return (1);
	}
	return (0);
}

void	str_token(t_lsttoken **head, char *line, int *i)
{
	int	j;

	j = 0;
	while (line[*i + j] && line[*i + j] != '<' && line[*i + j] != '>' && \
	line[*i + j] != '|' && line[*i + j] != '&' && line[*i + j] != '\'' && \
	line[*i + j] != '\"' && line[*i + j] != ')' && line[*i + j] != '(' && \
	line[*i + j] != ' ')
		j++;
	if (j)
		ft_lstokenadd_back(head, new_token((t_token){E_STR, line, *i, j,
				NULL}));
	*i += j;
	j = 0;
	while (line[*i + j] == ' ')
		j++;
	if (j)
		ft_lstokenadd_back(head, new_token((t_token){E_SPACE, 0, 0, 0, NULL}));
	*i += j;
	while (line[*i] == ')')
		(*i)++;
}

t_lsttoken	*tokenize(char *line)
{
	t_lsttoken	*new;
	int			i;

	new = NULL;
	i = 0;
	while (line[i])
	{
		if (subsh_token(&new, line, &i))
			continue ;
		else if (quote_token(&new, line, &i))
			continue ;
		else if (operator_token(&new, line, &i))
			continue ;
		else if (pipe_token(&new, line, &i))
			continue ;
		else if (red_right_token(&new, line, &i))
			continue ;
		else if (red_left_token(&new, line, &i))
			continue ;
		else
			str_token(&new, line, &i);
	}
	return (check_tokenize(new));
}
