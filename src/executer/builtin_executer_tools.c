/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_call_tools.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 15:36:18 by aahlyel           #+#    #+#             */
/*   Updated: 2023/06/25 15:49:17 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_option(char *line, char *endline)
{
	int	i;
	int	is_op;

	i = 0;
	if (line[i] == '\'' || line[i] == '\"')
		i++;
	if (line[i] == '-')
		i++;
	else
		return (0);
	is_op = i;
	while (line[i] == 'n' && line + i != endline)
		i++;
	if (is_op == i)
		return (0);
	if (line + i == endline || ((line[i] == '\'' || line[i] == '\"') && \
	line + i + 1 == endline))
		return (1);
	return (0);
}

int	skip_echo_option_down_up(t_arguments *front, int *has_option)
{
	char	*str;

	if (front->type & (IS_STR) && is_option(front->str, \
	front->str + ft_strlen(front->str)))
	{
		*has_option |= ECHO_OPTION;
		return (1);
	}
	if (front->type & (QUOTE | DQUOTE))
	{
		str = args_to_str(front->down);
		if (!is_option(str, str + ft_strlen(str)))
		{
			free(str);
			return (0);
		}
		free(str);
		*has_option |= ECHO_OPTION;
		return (1);
	}
	return (-1);
}

t_arguments	*skip_echo_option(t_arguments *front, int *has_option)
{
	int		ret;

	while (front)
	{
		if (front->type & IS_SEPARTOR)
		{
			front = front->next;
			continue ;
		}
		ret = skip_echo_option_down_up(front, has_option);
		if (!ret)
			break ;
		else if (ret == 1)
		{
			front = front->next;
			continue ;
		}
		break ;
	}
	return (front);
}

int	is_builtin(char *word)
{
	int		i;
	int		j;
	char	*tmp;

	j = skip_spaces_front(word);
	i = find_space(word + j);
	tmp = ft_strdup(word);
	if (i)
		tmp[j + i] = 0;
	if (!ft_strncmp(tmp + j, "cd", 3))
		return (free(word), free(tmp), CD);
	else if (!ft_builtin_strncmp(tmp + j, "echo", 5))
		return (free(word), free(tmp), ECHO);
	else if (!ft_builtin_strncmp(tmp + j, "env", 4))
		return (free(word), free(tmp), ENV);
	else if (!ft_strncmp(tmp + j, "exit", 5))
		return (free(word), free(tmp), EXIT);
	else if (!ft_strncmp(tmp + j, "export", 7))
		return (free(word), free(tmp), EXPORT);
	else if (!ft_builtin_strncmp(tmp + j, "pwd", 4))
		return (free(word), free(tmp), PWD);
	else if (!ft_strncmp(tmp + j, "unset", 6))
		return (free(word), free(tmp), UNSET);
	return (free(word), free(tmp), 0);
}
