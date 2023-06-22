/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_t2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 21:10:53 by aelbrahm          #+#    #+#             */
/*   Updated: 2023/06/21 18:41:37 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	d_point_pwd(char *path, char *pwd)
{
	int		ret;
	char	cwd2[PATH_MAX];

	if (!stat_check(path))
		return (1);
	ret = chdir(path);
	if (ret == -1)
		return (err_print(path, " : cd :  ", strerror(errno)), 0);
	getcwd(cwd2, sizeof(cwd2));
	reset_env(cwd2, pwd);
	return (ret);
}

int	go_to_oldpwd(char *cwd, char *path)
{
	char	*env_path;
	int		ret;

	env_path = get_owd("OLDPWD=");
	if (!stat_check(env_path))
		return (1);
	if (!env_path)
		return (err_print("minishell : cd: OLDPWD not set", "", NULL));
	if (access(env_path, R_OK) != 0)
		return (err_print("cd: ", path, ": No such file or directory"));
	if (get_owd("PWD=") && !*cwd)
		reset_env(env_path, get_owd("PWD="));
	else
		reset_env(env_path, cwd);
	ft_putendl_fd(get_owd("PWD="), g_glb.out);
	ret = chdir(get_owd("PWD="));
	return (ret);
}

int	stat_check(char *path)
{
	struct stat	file_info;

	if (stat(path, &file_info) == 0)
	{
		if (!(file_info.st_mode & S_IRUSR))
			return (err_print("cd: permission denied: ", path, NULL), 0);
		else
			return (1);
	}
	else
		return (1);
}

char	*get_owd(char *env_var)
{
	t_hold	*env;
	t_list	*lst_tmp;
	size_t	size;

	size = ft_strlen(env_var);
	env = set__get_option_variables(0, GET | GET_ENV);
	lst_tmp = env->lst;
	while (lst_tmp)
	{
		if (!ft_strncmp(env_var, lst_tmp->content, size))
			return ((char *)lst_tmp->content + size);
		lst_tmp = lst_tmp->next;
	}
	return (NULL);
}

short	valid_var(char *var)
{
	if (!(ft_isalpha(*var) || *var == '_'))
		return (1);
	while (*var)
	{
		if (!(ft_isalnum(*var) || *var == '_'))
			return (1);
		var++;
	}
	return (0);
}
