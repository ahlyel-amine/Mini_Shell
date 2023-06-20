/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters_setters.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 12:56:39 by aahlyel           #+#    #+#             */
/*   Updated: 2023/06/20 23:49:52 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	*set_homedir(t_hold *env, char *home)
{
	t_list	*tmp_e;
	char	*dir;
	int		i;
	int		j;

	j = 0;
	i = 0;
	dir = NULL;
	tmp_e = env->lst;
	while (tmp_e)
	{
		if (!ft_strncmp(tmp_e->content, "HOME=", ft_strlen("HOME=")))
		{
			dir = tmp_e->content;
			break ;
		}
		tmp_e = tmp_e->next;
	}
	if (dir)
	{
		while (ft_strncmp(&(tmp_e->content[j]), "=", 1))
			j++;
		dir = ft_strdup(tmp_e->content + j + 1);
	}
	return (free(home), dir);
}

static char	**set_path(t_hold *env, char **old_path)
{
	char	**path;
	t_list	*tmp_e;
	char	*tmp;
	int		i;

	i = 0;
	path = NULL;
	tmp_e = env->lst;
	while (tmp_e)
	{
		if (!ft_strncmp(tmp_e->content, "PATH=", ft_strlen("PATH=")))
		{
			tmp = ft_substr(tmp_e->content, 5, ft_strlen(tmp_e->content + 5));
			path = ft_split(tmp, ':');
			free(tmp);
		}
		tmp_e = tmp_e->next;
	}
	while (old_path && old_path[i])
		free(old_path[i++]);
	free(old_path);
	return (path);
}

char	**env_str(t_hold *env_var)
{
	char	**env;
	short	iter;

	iter = 0;
	env = (char **)malloc(sizeof(char *) * env_var->size + 1);
	while (env_var->lst)
	{
		env[iter++] = ft_strdup(env_var->lst->content);
		env_var->lst = env_var->lst->next;
	}
	env[iter] = NULL;
	return (env);
}

void	free_env(char **env)
{
	int	iter;

	iter = 0;
	while (env && env[iter])
		free(env[iter++]);
	free(env);
}

void	*set__get_option_variables(void *env, int set__get_option)
{
	static char	**path;
	static void	*envs;
	static char	*home_dir;
	static char	*pwd;

	if (set__get_option == SET)
	{
		envs = env;
		path = set_path((t_hold *)envs, path);
		home_dir = set_homedir((t_hold *)envs, home_dir);
	}
	else if (set__get_option == (SET | SET_PWD))
		pwd = set_pwd(pwd);
	else if (set__get_option == (GET | GET_PATH))
		return (path);
	else if (set__get_option == (GET | GET_ENV))
		return (envs);
	else if (set__get_option == (GET | GET_HOME))
		return (home_dir);
	else if (set__get_option == (GET | GET_PWD))
		return (pwd);
	else if (set__get_option == FREE)
		unset((t_hold *)envs, &path, &home_dir, &pwd);
	return (NULL);
}
