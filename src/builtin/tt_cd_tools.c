/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tt_cd_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbrahm <aelbrahm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 21:14:50 by aelbrahm          #+#    #+#             */
/*   Updated: 2023/06/16 04:55:47 by aelbrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	reset_env(char *pwd, char *o_pwd)
{
	t_hold	*env;
	t_list	*lst;
	short	flg = 0;
	short	p_flg = 0;
	env = set__get_option_variables(0, (GET | GET_ENV));
	lst = env->lst;
	while (lst)
	{
		if (!ft_strncmp("PWD=", lst->content, 4))
			env_key_cmp(pwd, "PWD=", &(lst->content), &p_flg);
		if (!ft_strncmp("OLDPWD=", lst->content, 7))
			env_key_cmp(o_pwd, "OLDPWD=", &lst->content, &flg);
		lst = lst->next;
	}
	if (!flg)
	{
		ft_lstadd_node(&env->lst, ft_lstnew(ft_strjoin("OLDPWD=", o_pwd)), (env->size >> 1));
		env->size++;
	}
	if (!p_flg)
	{
		ft_lstadd_node(&env->lst, ft_lstnew(ft_strjoin("PWD=", pwd)), (env->size >> 1));
		env->size++;
	}
}

char	*extend_option(char *arg, char *ex_with, int opt)
{
	char	*ret;
	char	*past;
	char	*tmp;

	ret = NULL;
	past = NULL;
	if (!opt)
		tmp = ft_substr(arg, 2, (ft_strlen(arg) - 2));
	else if (opt == 1)
		tmp = ft_substr(arg, 1, (ft_strlen(arg) - 1));
	ret = ft_strjoin_free(ex_with, tmp);
	return (free(arg), ret);
}

char	*get_prev_path(char *path)
{
	int		iter;
	int		len;
	char	*tmp;

	len = ft_strlen(path);
	len--;
	iter = len;
	while (path[iter] != '/' && iter >= 0)
		iter--;
	if (path[iter] == '/' && iter == 0)
		return (ft_strdup("/"));
	else if (iter != len)
		tmp = ft_substr(path, 0, iter);
	return (tmp);
}

int	ft_go_to(int opt, char **path, char *cwd)
{
	char	*env_path;
	int		ret;

	env_path = NULL;
	if (!opt)
	{
		env_path = get_owd("HOME=");
		if (!stat_check(env_path))
			return (1);
		if (!env_path)
			return (err_print("minishell : cd: HOME not set", "", NULL));
		if (!*cwd)
			reset_env(env_path, get_owd("PWD="));
		else
			reset_env(env_path, cwd);
		return (chdir(env_path));
	}
	else if (opt == 1)
		ret = go_to_oldpwd(cwd, *path);
	else
		ret = 0;
	return (sp_free(path), ret);
}

int	prev_drictory_count(char *wd)
{
	int		count;
	int		indx;
	char	**splited;

	count = 0;
	indx = 0;
	splited = ft_split(wd, '/');
	while (splited && splited[indx])
	{
		if (!ft_memcmp(splited[indx], "..", 2))
			count++;
		indx++;
	}
	sp_free(splited);
	return (count);
}
