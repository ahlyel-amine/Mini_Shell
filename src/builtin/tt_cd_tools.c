/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tt_cd_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbrahm <aelbrahm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 21:14:50 by aelbrahm          #+#    #+#             */
/*   Updated: 2023/06/21 15:46:40 by aelbrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	push_env_var(short flg, short p_flg, char *o_pwd, char *pwd);

void	reset_env(char *pwd, char *o_pwd)
{
	t_hold	*env;
	t_list	*lst;
	short	flg;
	short	p_flg;

	flg = 0;
	p_flg = 0;
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
	push_env_var(flg, p_flg, o_pwd, pwd);
}

void	push_env_var(short flg, short p_flg, char *o_pwd, char *pwd)
{
	t_hold	*env;

	env = set__get_option_variables(0, (GET | GET_ENV));
	if (!flg)
	{
		ft_lstadd_node(&env->lst, ft_lstnew(ft_strjoin("OLDPWD=", o_pwd)), \
		(env->size >> 1));
		env->size++;
	}
	if (!p_flg)
	{
		ft_lstadd_node(&env->lst, ft_lstnew(ft_strjoin("PWD=", pwd)), \
		(env->size >> 1));
		env->size++;
	}
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
		ret = chdir(env_path);
		if (ret == -1)
			return (err_print("cd: ", env_path, DR_ERR));
		return (0);
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
