/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters_setters.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbrahm <aelbrahm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 12:56:39 by aahlyel           #+#    #+#             */
/*   Updated: 2023/05/17 01:31:50 by aelbrahm         ###   ########.fr       */
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
	free (home);
	return (dir);
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
			free (tmp);
		}
		tmp_e = tmp_e->next;
	}

	while (old_path && old_path[i])
		free (old_path[i++]);
	free (old_path);
	return (path);
}

char	*set_pwd(char *old_pwd)
{
	char	*ipwd;
	char	*pwd;
	char	*homedir;

	ipwd = NULL;
	ipwd = getcwd(ipwd, 0);
		
	homedir = set__get_option_variables(0, GET | GET_HOME);
	if (!ipwd)
		pwd = homedir;
	else	
		pwd = ipwd;
	if (homedir && !ft_strncmp(homedir, pwd, ft_strlen(homedir)))
	{
		pwd = ft_strjoin("~", ipwd);
		free (ipwd);
	}
	free (old_pwd);
	return (pwd);
}
void	unset(t_hold *env, char ***path, char **pwd, char **homedir)
{
	int	i;

	i = 0;
	free (*homedir);
	*homedir = NULL;
	free (*pwd);
	*pwd = NULL;
	while (*path && (*path)[i])
		free ((*path)[i++]);
	free (*path);
	*path = NULL;
	ft_lstclear(&(env->lst), free);
	
}

char	**ft_dstrdup(char **ds1)
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
		words[j] = ds1[j];
	words[j] = NULL;
	return (words);
}
// char	**set_env(char **env)
// {
// 	char **envp;

// 	envp = ft_dstrdup(env);
// 	return (envp);
// }

char **env_str(t_hold *env_var)
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

void	*set__get_option_variables(t_hold *env, int set__get_option)
{
	static char	**path;
	static char	**envs;
	static char	*home_dir;
	static char	*pwd;

	if (set__get_option == SET)
	{
		envs = (char **)env;
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

char	*get_prompt_line()
{
	char	*pwd;
	pwd = NULL;
	set__get_option_variables(0, SET | SET_PWD);
	pwd = set__get_option_variables(0, GET | GET_PWD);
	// pwd = get_owd("PWD=");
	if (pwd)
	{
		pwd = ft_strjoin_free(ft_strdup("\n╭─\x1b[43m░▒▓▓▓▓▓\x1b[40m\x1b[44m "), ft_strdup(pwd));
		pwd = ft_strjoin_free(pwd, ft_strdup(" \x1b[43m minishell \x1b[0m───────────────────────────\x1b[43▓▓▓▓▒░\x1b[0m─\n╰─ "));
	}
	return (pwd);
}