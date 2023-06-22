/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 19:19:53 by aelbrahm          #+#    #+#             */
/*   Updated: 2023/06/21 18:42:44 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	d_point_check(char *path)
{
	int		is_valid;
	int		indx;
	char	**splited;

	is_valid = 1;
	indx = 0;
	splited = ft_split(path, '/');
	while (splited && splited[indx])
	{
		if (ft_memcmp(splited[indx], ".", 1) \
		&& ft_memcmp(splited[indx], "..", 2))
			is_valid = 0;
		indx++;
	}
	sp_free(splited);
	return (is_valid);
}

int	d_point_validat(char *path, char *o_pwd, int count)
{
	char	*dir;
	int		indx;
	int		ret;

	indx = dp_point_skip(path);
	while (count)
	{
		if (indx > 0 && path[indx - 1] == '/')
			indx--;
		while (indx > 0 && path[indx - 1] != '/')
			indx--;
		count--;
	}
	dir = ft_substr(path, 0, indx);
	ret = chdir(dir);
	if (!ret)
		reset_env(dir, o_pwd);
	return (free(dir), ret);
}

int	d_point_extend(char *path, char *cwd)
{
	char	*pwd;
	int		ret;
	int		count;

	pwd = prepare_pwd();
	ret = 0;
	if (!*cwd && d_point_check(path))
	{
		if (pwd && pwd[ft_strlen(pwd) - 1] != '/')
			pwd = ft_strjoin_free(pwd, ft_strdup("/"));
		count = prev_drictory_count(path);
		if (count >= 3)
			return (free(pwd), err_print("cd: ", path, DR_ERR));
		count += prev_drictory_count(pwd);
		ret = d_point_validat(pwd, get_owd("OLDPWD="), count);
		if (ret == -1)
		{
			pwd = ft_strjoin_free(pwd, ft_strdup(path));
			reset_env(pwd, get_owd("PWD="));
			return (free(pwd), err_print(CWD_ERR, strerror(errno), NULL));
		}
	}
	else if (cwd)
		ret = d_point_pwd(path, pwd);
	return (free(pwd), ret);
}

void	nr_cd(char *path, char *cwd)
{
	int		ret;
	char	cwd2[PATH_MAX];

	ret = 0;
	if (!stat_check(path))
		ret = 1;
	ret = chdir(path);
	if (ret == -1)
	{
		err_print(path, " : cd :  ", strerror(errno));
		ret = 1;
	}
	else
	{
		getcwd(cwd2, sizeof(cwd2));
		reset_env(cwd2, cwd);
	}
	g_glb.exit_val = ret;
}

void	tt_cd(t_arguments **cd_args)
{
	char		**path;
	int			ret;
	char		cwd[PATH_MAX];

	ret = 0;
	if (!getcwd(cwd, sizeof(cwd)))
		cwd[0] = '\0';
	(transform_args(cd_args));
	path = args_to_dblstr_(*cd_args);
	if (!path)
		g_glb.exit_val = ft_go_to(0, path, cwd);
	else if (!**path)
		g_glb.exit_val = ft_go_to(2, path, cwd);
	else if (!ft_memcmp(*path, "-", 2))
		g_glb.exit_val = ft_go_to(1, path, cwd);
	else
	{
		if (!ft_memcmp(*path, "..", 2) || !ft_memcmp(*path, ".", 1))
			g_glb.exit_val = d_point_extend(*path, cwd);
		else
			nr_cd(*path, cwd);
		sp_free(path);
	}
}
