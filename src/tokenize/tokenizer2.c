/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 18:48:36 by aahlyel           #+#    #+#             */
/*   Updated: 2023/06/19 18:50:57 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	red_right_token(t_lsttoken **head, char *line, int *i)
{
	int	j;

	j = 0;
	if (line[*i] == '>' && line[*i + 1] == '>')
	{
		ft_lstokenadd_back(head, new_token((t_token){NULL, line, *i, 2,
				E_APPEND}));
		*i += 2;
		return (1);
	}
	else if (line[*i] == '>')
	{
		ft_lstokenadd_back(head, new_token((t_token){NULL, line, *i, 1,
				E_OUTRED}));
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
		ft_lstokenadd_back(head, new_token((t_token){NULL, line, *i, 2,
				E_HEREDOC}));
		*i += 2;
		return (1);
	}
	else if (line[*i] == '<')
	{
		ft_lstokenadd_back(head, new_token((t_token){NULL, line, *i, 1,
				E_INRED}));
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
		ft_lstokenadd_back(head, new_token((t_token){NULL, line, *i, j,
				E_STR}));
	*i += j;
	j = 0;
	while (line[*i + j] == ' ')
		j++;
	if (j)
		ft_lstokenadd_back(head, new_token((t_token){NULL, 0, 0, 0, E_SPACE}));
	*i += j;
	while (line[*i] == ')')
		(*i)++;
}

int	get_fds_loop_check(t_lsttoken *head)
{
	int			start;
	int			end;
	t_lsttoken	*tmp;

	tmp = head->next;
	if (tmp && tmp->t_.type == E_SPACE)
		tmp = tmp->next;
	if (!tmp)
		return (panic_recursive(ERR_O_SNTX, NULL), 0);
	start = tmp->t_.start;
	end = 0;
	while (tmp)
	{
		if (tmp->t_.type & (E_STR | E_DQUOTE | E_QUOTE))
		{
			tmp->t_.type = E_EMPTY;
			end += tmp->t_.len;
		}
		else
			break ;
		tmp = tmp->next;
	}
	head->t_.down = new_token((t_token){NULL, \
	head->t_.line, start, end, E_FD_NAME});
	return (1);
}

int	get_fds(t_lsttoken	*fds)
{
	t_lsttoken	*head;
	t_lsttoken	*tmp;
	int			start;
	int			end;

	head = fds;
	while (head)
	{
		if (head->t_.type & (E_OUTRED | E_INRED | E_APPEND | E_HEREDOC))
		{
			if (!get_fds_loop_check(head))
				return (0);
		}
		else if (head->t_.type == E_SUBSH)
			get_fds(head->t_.down);
		head = head->next;
	}
	return (1);
}
