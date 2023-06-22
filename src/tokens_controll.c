/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_controll.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 18:47:21 by aahlyel           #+#    #+#             */
/*   Updated: 2023/06/20 16:27:12 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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

void	free_lsttoken(t_lsttoken *new)
{
	t_lsttoken	*tmp;

	while (new)
	{
		tmp = new;
		if (new->t_.type == E_EMPTY && tmp->t_.down)
			free_lsttoken(tmp->t_.down);
		else if (new->t_.type == E_SUBSH)
			free_lsttoken(new->t_.down);
		else if (new->t_.type != E_EMPTY && tmp->t_.down)
			free_lsttoken(new->t_.down);
		new = new->next;
		free (tmp);
	}
}
