/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters_setters.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 12:56:39 by aahlyel           #+#    #+#             */
/*   Updated: 2023/04/27 13:17:21 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*set_homedir(char **env)
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
		printf("[%s]\n", env[i]);
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
	return (dir);
}
char	**set_path(char **env)
{
	char	**path;
	int		i;

	i = 0;
	path = NULL;
	while (env[i])
	{
		if (!ft_strncmp(env[i], "PATH=", ft_strlen("PATH=")))
			path = ft_split(ft_substr(env[i], 5, ft_strlen(env[i] + 5)), ':');
		i++;
	}
	return (path);
}


void	*set__get_option_variables(char	**env, int set__get_option)
{
	static char	**path;
	static char	**envs;
	static char	*home_dir;

	if (set__get_option == SET)
	{
		envs = env;
		path = set_path(env);
		home_dir = set_homedir(env);
	}
	if (set__get_option == (GET | GET_PATH))
		return (path);
	else if (set__get_option == (GET | GET_ENV))
		return (env);
	else if (set__get_option == (GET | GET_HOME))
		return (home_dir);
	return (NULL);
}

char	*get_prompt_line(char *old_pwd)
{
	char	*pwd;
	char	*homedir;

	
	homedir = set__get_option_variables(0, GET | GET_HOME);
	pwd = old_pwd;
	if (!ft_strncmp(homedir, pwd,ft_strlen(homedir)))
	{
		pwd = ft_strjoin("~", old_pwd + 14);
		free (old_pwd);
	}
	pwd = ft_strjoin_free(ft_strdup("\n╭─\x1b[43m░▒▓▓▓▓▓\x1b[40m\x1b[44m "), pwd);
	pwd = ft_strjoin_free(pwd, ft_strdup(" \x1b[43m minishell \x1b[0m───────────────────────────\x1b[43▓▓▓▓▒░\x1b[0m─\n╰─ "));
	return (pwd);
}