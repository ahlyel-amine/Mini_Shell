/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_arguments.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 22:02:05 by aahlyel           #+#    #+#             */
/*   Updated: 2023/06/24 23:06:30 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	fill_str(t_arguments *tmp, char **str, size_t *len)
{
	int	i;

	i = 0;
	if ((tmp->type & IS_FILE) && (tmp->next) && (tmp->next->type & IS_FILE))
	{
		while (tmp->str[i])
			(*str)[(*len)++] = tmp->str[i++];
		(*str)[(*len)++] = ' ';
	}
	else if ((tmp->type & IS_STR) || (tmp->type & IS_VARIABLE) || \
	(tmp->type & IS_SEPARTOR) || (tmp->type & IS_FILE))
	{
		if (tmp->type & IS_SEPARTOR && !tmp->next)
			return (1);
		while (tmp->str[i])
			(*str)[(*len)++] = tmp->str[i++];
	}
	else if (tmp->type & QUOTE || tmp->type & DQUOTE)
		down_to_str(tmp->down, str, len);
	return (0);
}

char	*args_to_str(t_arguments *args)
{
	t_arguments	*tmp;
	char		*str;
	size_t		len;

	tmp = args;
	len = args_strslen(args);
	str = ft_calloc(sizeof(char), (len + 1));
	if (!str)
		return (perror(""), NULL);
	len = 0;
	while (tmp)
	{
		if (fill_str(tmp, &str, &len))
			break ;
		tmp = tmp->next;
	}
	return (str);
}

static void	fill_dstr(t_arguments *tmp, char ***str, size_t *len)
{
	if ((tmp->type & IS_STR || tmp->type & IS_VARIABLE))
		(*str)[(*len)++] = ft_strdup(tmp->str);
	else if ((tmp->type & QUOTE || tmp->type & DQUOTE))
		(*str)[(*len)++] = args_to_str(tmp->down);
}

char	**args_to_cmd_dstr(t_arguments *args, char *cmd)
{
	t_arguments	*tmp;
	char		**str;
	size_t		len;

	tmp = args;
	len = args_len(args);
	str = malloc(sizeof(char *) * (len + 2));
	if (!str)
		return (perror(""), NULL);
	str[0] = ft_strdup(cmd);
	if (!len)
		return (str[1] = NULL, str);
	len = 1;
	while (tmp)
	{
		fill_dstr(tmp, &str, &len);
		tmp = tmp->next;
	}
	str[len] = NULL;
	return (str);
}

char	**args_to_dblstr(t_arguments *args)
{
	t_arguments	*tmp;
	char		**str;
	size_t		len;

	tmp = args;
	len = args_len(args);
	if (!len)
		return (NULL);
	str = malloc(sizeof(char *) * (len + 1));
	if (!str)
		return (perror(""), NULL);
	len = 0;
	while (tmp)
	{
		if (tmp->type & IS_STR || tmp->type & IS_VARIABLE)
			str[len++] = ft_strdup(tmp->str);
		else if ((tmp->type & QUOTE || tmp->type & DQUOTE))
			str[len++] = args_to_str(tmp->down);
		tmp = tmp->next;
	}
	str[len] = NULL;
	return (str);
}
