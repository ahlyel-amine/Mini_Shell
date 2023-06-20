/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   priorities_call_tools.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 19:54:15 by aahlyel           #+#    #+#             */
/*   Updated: 2023/06/20 23:58:06 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	**child_vars(void)
{
	char	**backup_env;
	t_hold	*env;
	t_list	*lst;
	int		size;
	int		iter;

	g_glb.is_sig = 0;
	env = set__get_option_variables(0, GET | GET_ENV);
	lst = env->lst;
	size = env->size;
	backup_env = ft_calloc(sizeof(char *), (size + 1));
	iter = 0;
	while (size--)
	{
		backup_env[iter] = ft_strdup(lst->content);
		lst = lst->next;
		iter++;
	}
	return (backup_env);
}

size_t	get_lenght(t_lsttoken *front)
{
	t_lsttoken	*head;
	size_t		len;

	head = front;
	len = 0;
	while (head)
	{
		if (head->t_.type & (E_AND | E_OR | E_PIPE))
			break ;
		else if (head->t_.type == E_SPACE)
			len++;
		else if (!(head->t_.type & (E_EMPTY | E_SPACE)))
			len += head->t_.len;
		head = head->next;
	}
	return (len);
}

char	*get_line(t_lsttoken *front, size_t len)
{
	t_lsttoken	*head;
	char		*line;
	size_t		i;
	int			j;

	i = 0;
	head = front;
	line = ft_calloc(1, len + 1);
	if (!line)
		return (NULL);
	while (head)
	{
		if (head->t_.type & (E_AND | E_OR | E_PIPE))
			break ;
		else if (head->t_.type == E_SPACE)
			line[i++] = ' ';
		else if (!(head->t_.type & (E_EMPTY | E_SPACE)))
		{
			j = 0;
			while (head->t_.start + j < head->t_.start + head->t_.len)
				line[i++] = head->t_.line[head->t_.start + j++];
		}
		head = head->next;
	}
	return (line);
}

int	is_builtin(char *word)
{
	if (!ft_strncmp(word, "cd", 3))
		return (1);
	else if (!ft_strncmp(word, "echo", 5))
		return (1);
	else if (!ft_strncmp(word, "env", 4))
		return (1);
	else if (!ft_strncmp(word, "exit", 5))
		return (1);
	else if (!ft_strncmp(word, "export", 7))
		return (1);
	else if (!ft_strncmp(word, "pwd", 4))
		return (1);
	else if (!ft_strncmp(word, "unset", 6))
		return (1);
	return (0);
}

int	pipe_left(t_lsttoken *head, t_lsttoken *back)
{
	t_lsttoken	*tmp;

	tmp = head;
	while (tmp && tmp != back)
	{
		if (tmp->t_.type == E_PIPE)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}
