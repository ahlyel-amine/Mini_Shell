/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters_setters.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 12:56:39 by aahlyel           #+#    #+#             */
/*   Updated: 2023/04/27 18:11:03 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	*set_homedir(char **env, char *home)
{
	char	*dir;
	int		i;
	int		j;

	j = 0;
	i = 0;
	dir = NULL;
	while (env[i])
	{
		if (!ft_strncmp(env[i], "HOME=", ft_strlen("HOME=")))
		{
			dir = env[i];
			break ;
		}
		i++;
	}
	if (dir)
	{
		while (env[i][j] != '=')
			j++;
		dir = ft_strdup(env[i] + j + 1);
	}
	free (home);
	return (dir);
}

static char	**set_path(char **env, char **old_path)
{
	char	**path;
	char	*tmp;
	int		i;

	i = 0;
	path = NULL;
	while (env[i])
	{
		if (!ft_strncmp(env[i], "PATH=", ft_strlen("PATH=")))
		{
			tmp = ft_substr(env[i], 5, ft_strlen(env[i] + 5));
			path = ft_split(tmp, ':');
			free (tmp);
		}
		i++;
	}
	i = 0;
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
	pwd = ipwd;
	if (homedir && !ft_strncmp(homedir, pwd, ft_strlen(homedir)))
	{
		pwd = ft_strjoin("~", ipwd + 14);
		free (ipwd);
	}
	free (old_pwd);
	return (pwd);
}
void	unset(char ***path, char **pwd, char **homedir)
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
}

size_t ft_double_strlen(char **str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
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
char	**set_env(char **env)
{
	char **envp;

	envp = ft_dstrdup(env);
	return (envp);
}
void	*set__get_option_variables(char	**env, int set__get_option)
{
	static char	**path;
	static char	**envs;
	static char	*home_dir;
	static char	*pwd;

	if (set__get_option == SET)
	{
		envs = env;
		path = set_path(env, path);
		home_dir = set_homedir(env, home_dir);
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
		unset(&path, &home_dir, &pwd);
	return (NULL);
}

char	*get_prompt_line()
{
	char	*pwd;

	set__get_option_variables(0, SET | SET_PWD);
	pwd = set__get_option_variables(0, GET | GET_PWD);
	pwd = ft_strjoin_free(ft_strdup("\n╭─\x1b[43m░▒▓▓▓▓▓\x1b[40m\x1b[44m "), ft_strdup(pwd));
	pwd = ft_strjoin_free(pwd, ft_strdup(" \x1b[43m minishell \x1b[0m───────────────────────────\x1b[43▓▓▓▓▒░\x1b[0m─\n╰─ "));
	return (pwd);
}