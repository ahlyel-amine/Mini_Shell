/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 15:37:16 by aahlyel           #+#    #+#             */
/*   Updated: 2023/06/25 15:42:26 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_arguments	*get_cmd_arguments(t_arguments *cmd)
{
	t_arguments	*arg;
	t_arguments	*tmp;

	tmp = cmd;
	if (!cmd)
		return (NULL);
	while (tmp->next)
	{
		if (tmp->type & IS_SEPARTOR || \
		(tmp->type & IS_FILE && tmp->next && tmp->next->type & IS_FILE))
			break ;
		tmp = tmp->next;
	}
	if (!tmp)
		return (NULL);
	arg = tmp->next;
	tmp->next = NULL;
	return (arg);
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

int	find_space(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_isspace(str[i]))
			break ;
		i++;
	}
	return (i);
}

char	*get_path(char *cmd)
{
	char	**path;
	char	*tmp_to_free;
	int		i;

	i = 0;
	path = NULL;
	if (cmd == NULL)
		return (NULL);
	if (!*cmd)
		return (pr_custom_err(ERR_CMD, NULL, cmd), NULL);
	if (has_slash(cmd))
		return (is_dir(cmd));
	tmp_to_free = get_owd("PATH=");
	if (tmp_to_free)
		path = ft_split(tmp_to_free, ':');
	while (path && path[i])
	{
		tmp_to_free = ft_strjoin(path[i], "/");
		tmp_to_free = ft_strjoin_free(tmp_to_free, ft_strdup(cmd));
		if (!access(tmp_to_free, F_OK | X_OK))
			return (sp_free(path), tmp_to_free);
		free(tmp_to_free);
		i++;
	}
	return (sp_free(path), set_return_err(cmd), NULL);
}
