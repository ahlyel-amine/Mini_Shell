/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_checker.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 17:55:40 by aahlyel           #+#    #+#             */
/*   Updated: 2023/06/22 22:22:07 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	only_space_front(t_lsttoken	*new)
{
	t_lsttoken	*head;

	head = new;
	while (head->t_.type == E_SPACE)
		head = head->next;
	if (head->t_.type & (E_AND | E_OR | E_PIPE))
		return (panic(head->t_.type), 1);
	return (0);
}

int	check_redirections_followed_by_subsh(t_lsttoken *new)
{
	t_lsttoken	*check;
	t_lsttoken	*check_2;

	check = new;
	while (check)
	{
		if (check->t_.type & (E_OUTRED | E_INRED | E_DQUOTE \
		| E_QUOTE | E_APPEND | E_HEREDOC | E_STR))
		{
			check_2 = check->next;
			while (check_2)
			{
				if (check_2->t_.type & (E_PIPE | E_AND \
				| E_OR | E_OUTRED | E_INRED | E_APPEND | E_HEREDOC))
					break ;
				else if (check_2->t_.type == E_SUBSH)
					return (panic(-1), 0);
				check_2 = check_2->next;
			}
		}
		check = check->next;
	}
	return (1);
}

int	check_redirections_names(t_lsttoken *check)
{
	if (check->t_.type & (E_OUTRED | E_INRED | E_APPEND | E_HEREDOC))
	{
		if (!check->next)
			return (panic(5), 0);
		else if (check->next && check->next->next && \
		check->next->t_.type & E_SPACE && \
		!(check->next->next->t_.type & (E_STR | E_QUOTE | E_DQUOTE)))
			return (panic(check->next->next->t_.type), 0);
		else if (check->next && !(check->next->t_.type & \
		(E_SPACE | E_STR | E_QUOTE | E_DQUOTE)))
			return (panic(check->next->t_.type), 0);
	}
	return (1);
}

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
		else if (check->t_.type == E_AND && \
		(check->next->t_.type & (E_OR | E_PIPE)))
			return (panic(check->next->t_.type), 0);
		else if (check->t_.type == E_OR && \
		(check->next->t_.type & (E_AND | E_PIPE)))
			return (panic(check->next->t_.type), 0);
		else if (check->t_.type == E_PIPE && \
		(check->next->t_.type & (E_OR | E_AND)))
			return (panic(check->next->t_.type), 0);
		check = check->next;
	}
	return (check_redirections_followed_by_subsh(new));
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
			new_sub = tokenize(subs->t_.line, subs->t_.line + \
			subs->t_.start + subs->t_.len, subs->t_.start);
			if (!check_tokenize(new_sub))
				return (free_lsttoken(new), NULL);
			subs->t_.down = new_sub;
		}
		subs = subs->next;
	}
	return (new);
}
