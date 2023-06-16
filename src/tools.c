/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbrahm <aelbrahm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 16:32:35 by aelbrahm          #+#    #+#             */
/*   Updated: 2023/06/16 04:35:55 by aelbrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	sp_free(char **splt)
{
	int	iter;

	iter = -1;
	while (splt[++iter])
		free(splt[iter]);
	free(splt);
}

char	*app_dup(char *arg)
{
	char	*buf;
	int		iter;

	buf = (char *)malloc((ft_strlen(arg)) * sizeof(char));
	iter = 0;
	while (*arg)
	{
		if (*arg == '+')
			arg++;
		buf[iter] = *arg;
		iter++;
		arg++;
	}
	buf[iter] = '\0';
	return (buf);
}

int	valid_id(char *var)
{
	if (!(ft_isalpha(*var) || *var == '_'))
		return (1);
	while (*var && *var != '=' && *var != '+')
	{
		if (!(ft_isalnum(*var) || *var == '_'))
			return (1);
		var++;
	}
	if (*var && *var == '+' && !*(var + 1))
		return (1);
	else if (*var && *var == '+' && *(var + 1) != '=')
		return (1);
	return (0);
}

char	*ft_strndup(const char *s, size_t n)
{
	char	*dst;
	char	*ret;

	if (!n)
		return (ft_strdup(""));
	dst = (char *)malloc(sizeof(char) * (n + 1));
	if (!dst)
		return (NULL);
	ret = dst;
	while (n-- >= 1)
		*(dst++) = *(s++);
	*dst = '\0';
	return (ret);
}
void	adjust_shlvl(t_hold *env)
{
	t_list	*lst;
	int		num;
	short	flg;

	flg = 0;
	lst = env->lst;
	while (lst)
	{
		if (!ft_memcmp(lst->content, "SHLVL=", 6))
		{
			num = ft_atoi((lst->content + 6));
			free(lst->content);
			lst->content = ft_strjoin_free(ft_strdup("SHLVL="), ft_itoa(++num));
			flg = 1;
		}
		lst = lst->next;
	}
	if (!flg)
	{
		ft_lstadd_back(&(env->lst), ft_lstnew(ft_strdup("SHLVL=1")));
		env->size++;
	}	
}
