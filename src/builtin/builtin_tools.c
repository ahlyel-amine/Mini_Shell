/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 23:42:38 by aelbrahm          #+#    #+#             */
/*   Updated: 2023/06/20 19:36:27 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_lstadd_node(t_list **lst, t_list *new, int pos)
{
	t_list	*tmp;
	int		count;

	count = 0;
	tmp = NULL;
	if (!new || !lst)
		return ;
	if (!*lst)
		*lst = new;
	else
	{
		tmp = *lst;
		while (tmp->next && count < pos)
		{
			tmp = tmp->next;
			count++;
		}	
		new->next = tmp->next;
		tmp->next = new;
	}	
}

void	env_key_cmp(char *pwd, char *to_replace, void **lst_content, short *flg)
{
	char	*tmp;
	char	*tmp2;

	tmp2 = NULL;
	if (pwd)
		tmp2 = ft_strdup(pwd);
	tmp = *((char **)lst_content);
	*flg = 1;
	*lst_content = ft_strjoin_free(ft_strdup(to_replace), tmp2);
	free(tmp);
}

char	*prepare_pwd(void)
{
	char	*pwd;

	pwd = get_owd("PWD=");
	if (!pwd)
	{
		set__get_option_variables(0, SET | SET_PWD);
		pwd = ft_strdup(set__get_option_variables(0, GET | GET_PWD));
	}
	else
		pwd = ft_strdup(pwd);
	return (pwd);
}

int	err_print(char *s1, char *s2, char *s3)
{
	ft_putstr_fd(s1, STDERR_FILENO);
	ft_putstr_fd(s2, STDERR_FILENO);
	if (!s3)
		write(STDERR_FILENO, "\n", 1);
	else
		ft_putendl_fd(s3, STDERR_FILENO);
	return (1);
}

void	critical_err(void)
{
	ft_putendl_fd(strerror(errno), STDERR_FILENO);
	exit(errno);
}
