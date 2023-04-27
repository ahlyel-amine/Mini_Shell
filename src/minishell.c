/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 22:03:39 by aahlyel           #+#    #+#             */
/*   Updated: 2023/04/27 10:32:21 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"


char	*get_homedir(char **env)
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

char	*update_pwd(char *old_pwd, char	*homedir)
{
	char	*pwd;

	pwd = old_pwd;
	if (!ft_strncmp(homedir, pwd,ft_strlen(homedir)))
	{
		pwd = ft_strjoin("~", old_pwd + 14);
		free (old_pwd);
	}
	pwd = ft_strjoin_free(ft_strdup("\n╭─\x1b[43m░▒▓▓▓▓▓\x1b[40m\x1b[44m "), pwd);
	pwd = ft_strjoin_free(pwd, ft_strdup(" \x1b[0m───────────────────────────\x1b[43▓▓▓▓▒░\x1b[0m─\n╰─ "));
	return (pwd);
}
void	*env_variables(char	**env, int ref)
{
	static char	**path;
	int		i;
	int		j;

	j = 0;
	i = 0;
	while (!ref && env[i])
	{
		if (!ft_strncmp(env[i], "PATH=", ft_strlen("PATH=")))
			path = ft_split(ft_substr(env[i], 5, ft_strlen(env[i] + 5)), ':');
		i++;
	}
	if (ref)
		return (path);
	return (NULL);
}

int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	char	*line;
	char	*pwd;
	char	*homedir;

	homedir = get_homedir(env);
	env_variables(env, SET);
	pwd = NULL;
	while (1)
	{
		free(pwd);
		pwd = NULL;

		pwd = getcwd(pwd, 0);
		pwd = update_pwd(pwd, homedir);
		line = readline(pwd);
		if (!line || !ft_strncmp(line, "exit", 5))
			exit(0);
		if (!*line)
			continue ;
		else
			add_history(line);
		parsing_controll(line);
	}
	return (0);
}