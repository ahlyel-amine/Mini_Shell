/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_t3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbrahm <aelbrahm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 01:08:21 by aelbrahm          #+#    #+#             */
/*   Updated: 2023/06/15 04:55:18 by aelbrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

//norm
void	critical_err(void)
{
	ft_putendl_fd(strerror(errno), STDERR_FILENO);
	exit(errno);
}

short	is_export_var(char *str)
{
	t_hold	*hold;
	t_list	*lst_env;
	size_t	len;
	int		size;

	hold = set__get_option_variables(0, GET | GET_ENV);
	lst_env = hold->lst;
	len = ft_strlen(str);
	size = hold->size;
	while (size--)
	{
		if (!ft_strncmp(str, lst_env->content, len) \
		&& *((char *)lst_env->content + len) == '=')
			return (0);
		lst_env = lst_env->next;
	}
	while (lst_env)
	{
		if (!ft_strncmp(str, lst_env->content, ft_strlen(lst_env->content)))
			return (0);
		lst_env = lst_env->next;
	}
	return (1);
}

void	do_cmp(char	*val, char **lst_cnt, short opt, size_t len)
{
	t_hold	*hold;

	hold = set__get_option_variables(0, GET | GET_ENV);
	if (!*(*lst_cnt + len))
		hold->size++;
	if (!opt)
	{
		free(*lst_cnt);
		*lst_cnt = ft_strdup(val);
	}
	else
		*lst_cnt = ft_strjoin_free(*lst_cnt, ft_strdup(val));
}

size_t	args_len_(t_arguments *args)
{
	t_arguments	*tmp;
	t_arguments	*d_tmp;
	size_t		len;

	len = 0;
	tmp = args;
	while (tmp)
	{
		if (tmp->type & QUOTE || tmp->type & DQUOTE)
			len++;
		else if (!tmp->next || tmp->type & IS_SEPARTOR)
			len++;
		tmp = tmp->next;
	}
	return (len);
}

static char	**args_dstr_alloc(t_arguments *args)
{
	t_arguments	*tmp;
	char		**str;
	size_t		len;

	tmp = args;
	len = args_len_(args);
	printf("len => %zu\n",len);
	if (!len)
		return (NULL);
	str = ft_calloc(sizeof(char *), len + 1);
	if (!str)
		critical_err();
	return (str);
}

static t_arguments	*ft_join_args_dstr(t_arguments *tmp, char **str, size_t *indx)
{
	char	*stack;

	stack = ft_strdup("");
	while ((tmp) && (tmp)->type != IS_SEPARTOR)
	{
		if (tmp->down)
			stack = ft_strjoin_free(stack, args_to_str((tmp)->down));
		else
			stack = ft_strjoin_free(stack, ft_strdup((tmp)->str));
		(tmp) = (tmp)->next;
	}
	str[*indx] = stack;
	*indx += 1;
	return (tmp);
}

char	**args_to_dblstr_(t_arguments *args)
{
	t_arguments	*tmp;
	char		**str;
	char		*tst;
	size_t		len;

	str = args_dstr_alloc(args);
	if (!str)
		return (NULL);
	len = 0;
	tmp = args;
	while (tmp)
	{
		if (tmp->type & IS_STR || tmp->type & IS_VARIABLE)
			tmp = ft_join_args_dstr(tmp, str, &len);
		else if ((tmp->type & QUOTE || tmp->type & DQUOTE))
		{
			str[len++] = args_to_str(tmp->down);
			tmp = tmp->next;
		}
		else
			tmp = tmp->next;
	}
	return (str);
}
