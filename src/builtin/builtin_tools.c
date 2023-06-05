/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbrahm <aelbrahm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 23:42:38 by aelbrahm          #+#    #+#             */
/*   Updated: 2023/06/05 08:36:30 by aelbrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
// void	pre_
char	**ft_dstrdup2(char **ds1)
{
	char	**words;
	int		ds1_len;	
	int		j;
	
	ds1_len = ft_double_strlen(ds1);
	j = -1;
	words = malloc(sizeof(char *) * (ds1_len + 1));
	if (!words)
		return (NULL);
	while (ds1[++j])
		words[j] = ft_strdup(ds1[j]);
	words[j] = NULL;
	return (words);
}
// env | awk -F= '{print $1}' | while read -r line; do unset "$line"; done