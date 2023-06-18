/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_checker.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 17:55:40 by aahlyel           #+#    #+#             */
/*   Updated: 2023/06/18 17:37:13 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int only_space_front(t_lsttoken	*new)
{
    t_lsttoken	*head;

    head = new;
    while (head->t_.type == E_SPACE)
        head = head->next;
    if (head->t_.type == E_AND || head->t_.type == E_OR || head->t_.type == E_PIPE)
		return (panic_recursive(ERR_O_SNTX, NULL), 1);
    return (0);
}

int	check_redirections_followed_by_subsh(t_lsttoken *new)
{
	t_lsttoken	*check;
	t_lsttoken	*check_2;

	check = new;
	while (check)
	{
		if (check->t_.type == E_OUTRED || check->t_.type == E_INRED || check->t_.type & (E_DQUOTE | E_QUOTE) ||\
		check->t_.type == E_APPEND || check->t_.type == E_HEREDOC || check->t_.type == E_STR)
		{
			check_2 = check->next;
			while (check_2)
			{
				if (check_2->t_.type == E_PIPE || check_2->t_.type == E_AND || \
				check_2->t_.type == E_OR || check_2->t_.type == E_OUTRED || \
				check_2->t_.type == E_INRED || check_2->t_.type == E_APPEND || \
				check_2->t_.type == E_HEREDOC)
					break ;
				else if (check_2->t_.type == E_SUBSH)
					return (panic_recursive(ERR_O_SNTX, NULL), 0);
				check_2 = check_2->next;
			}
		}
		check = check->next;
	}
	return (1);
}

int	check_redirections_names(t_lsttoken *check)
{
	if (check->t_.type == E_OUTRED || check->t_.type == E_INRED || \
	check->t_.type == E_APPEND || check->t_.type == E_HEREDOC)
	{
		// if (check->next && check->next->t_.type == E_EMPTY)
		// {
		// 	printf("%s[%d]\n", check->next->t_.line + check->next->t_.start, check->next->t_.len);

		if (!check->next)
			return (panic_recursive(ERR_O_SNTX, NULL), 0);
		else if (check->next && check->next->next && check->next->t_.type == E_SPACE && \
		check->next->next->t_.type != E_STR && check->next->next->t_.type != E_QUOTE && \
		check->next->next->t_.type != E_DQUOTE)
			return (panic_recursive(ERR_O_SNTX, NULL), 0);
		else if (check->next && check->next->t_.type != E_SPACE && \
		check->next->t_.type != E_STR  && \
		check->next->t_.type != E_QUOTE && check->next->t_.type != E_DQUOTE)
			return (panic_recursive(ERR_O_SNTX, NULL), 0);
		
	}
	return (1);
}
//   && check->next->t_.type != E_PIPE  &&\
// 		check->next->t_.type != E_AND  && check->next->t_.type != E_OR  &&
int	a_check(t_lsttoken *new)
{
	t_lsttoken	*check;

	if (!new)
		return (0);
	check = new;
	if (only_space_front(new))
        return (0);
	while (check)
	{
		if (!check_redirections_names(check))
			return (0);
		else if (check->t_.type == E_AND && (check->next->t_.type == E_OR || \
		check->next->t_.type == E_PIPE))
				return (panic_recursive(ERR_O_SNTX, NULL), 0);
		else if (check->t_.type == E_OR && (check->next->t_.type == E_AND || \
		check->next->t_.type == E_PIPE))
				return (panic_recursive(ERR_O_SNTX, NULL), 0);
		else if (check->t_.type == E_PIPE && (check->next->t_.type == E_OR || \
		check->next->t_.type == E_AND))
				return (panic_recursive(ERR_O_SNTX, NULL), 0);
		check = check->next;
	}
	return (check_redirections_followed_by_subsh(new));
}

int	get_fds_loop_check(t_lsttoken *head)
{
	int			start;
	int			end;
	t_lsttoken	*tmp;

	tmp = head->next;
	if (tmp && tmp->t_.type == E_SPACE)
	{
		tmp->t_.type = E_EMPTY;
		tmp = tmp->next;
	}
	if (!tmp)
		return (panic_recursive(ERR_O_SNTX, NULL), 0);
	start = tmp->t_.start;
	end = 0;
	while (tmp)
	{
		if (tmp->t_.type == E_STR || tmp->t_.type == E_DQUOTE || tmp->t_.type == E_QUOTE)
		{
			tmp->t_.type = E_EMPTY;
			end += tmp->t_.len;
		}
		else
			break ;
		tmp = tmp->next;
	}
	head->t_.down = new_token((t_token){E_FD_NAME, head->t_.line, start, end, NULL});
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
		if (head->t_.type == E_OUTRED || head->t_.type == E_INRED || \
		head->t_.type == E_APPEND || head->t_.type == E_HEREDOC)
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

t_lsttoken	*check_tokenize(t_lsttoken *new)
{
	t_lsttoken	*subs;
	t_lsttoken	*new_sub;

	if (!a_check(new))
		return (free_lsttoken(new), NULL);
	subs = new;
	while (subs)
	{
		if (subs->t_.type == E_SUBSH)
		{
			new_sub = tokenize(subs->t_.line, subs->t_.line + subs->t_.start + subs->t_.len, subs->t_.start);
			if (!check_tokenize(new_sub))
				return (free_lsttoken(new), NULL);
			subs->t_.down = new_sub;
		}
		subs = subs->next;
	}
	return (new);
}
