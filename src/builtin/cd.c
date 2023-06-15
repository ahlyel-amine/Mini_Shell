/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbrahm <aelbrahm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 19:19:53 by aelbrahm          #+#    #+#             */
/*   Updated: 2023/06/14 00:20:31 by aelbrahm         ###   ########.fr       */
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

	indx = ft_strlen(path);
	while (indx > 0)
	{
		if (indx > 0 && path[indx - 1] == '/')
			indx--;
		while (indx > 0 && path[indx - 1] == '.')
			indx--;
		if (path[indx - 1] != '/' && path[indx - 1] != '.')
			break ;
	}
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

int		d_point_extend(char  *path, char *cwd)
{
	char	*pwd;
	int		ret;
	int		count;

	pwd = prepare_pwd();
	if (!*cwd && d_point_check(path))
	{
		if (pwd && pwd[ft_strlen(pwd) - 1] != '/')
			pwd = ft_strjoin_free(pwd, ft_strdup("/"));
		count = prev_drictory_count(path);
		if (count >= 3)
			return (free(pwd), printf("cd: %s: No such file or directory\n", path), 1);
		count += prev_drictory_count(pwd);
		ret = d_point_validat(pwd, get_owd("OLDPWD="), count);
		if (ret == -1)
		{
			pwd = ft_strjoin_free(pwd, ft_strdup(path));
			reset_env(pwd, get_owd("PWD="));
			return (free(pwd), printf("cd: error retrieving current directory: \
			getcwd: cannot access parent directories: %s\n", strerror(errno)), 1);
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
		printf("cd: %s: %s\n", path, strerror(errno));
		ret = 1;
	}
	else
	{
		getcwd(cwd2, sizeof(cwd2));
		reset_env(cwd2, cwd);
	}
	glo_exit = ret;
}

char	*args(t_arguments *cmd)
{
	char		*ret;
	t_arguments	*tmp;

	ret = ft_strdup("");
	tmp = cmd;
	if (!tmp)
		return (NULL);
	if (tmp->type == QUOTE || tmp->type == DQUOTE)
	{
		tmp = tmp->down;
		while (tmp && tmp->str)
		{
			ret = ft_strjoin_free(ret, ft_strdup(tmp->str));
			tmp = tmp->next;
		}
	}
	else
	{
		while (tmp && tmp->type != IS_SEPARTOR)
		{
			ret = ft_strjoin_free(ret, ft_strdup(tmp->str));
			tmp = tmp->next;
		}
	}
	return (ret);
}

void	tt_cd(t_cmd *cmd)
{
	t_builtin	*cd;
	char		*path;
	int			ret;
	char		cwd[PATH_MAX];

	ret = 0;
	cd = (t_builtin *)cmd;
	if (!getcwd(cwd, sizeof(cwd)))
		cwd[0] = '\0';
	(transform_args(&cd->arguments));
	path = args(cd->arguments);
	if (!path)
		glo_exit = ft_go_to(0, path, cwd);
	else if (!ft_memcmp(path, "-", 2))
		glo_exit = ft_go_to(1, path, cwd), free(path);   
	else
	{
		if (!ft_memcmp(path, "..", 2) || !ft_memcmp(path, ".", 1))
			glo_exit = d_point_extend(path, cwd);
		else
			nr_cd(path, cwd);
		free(path);
	}
}
