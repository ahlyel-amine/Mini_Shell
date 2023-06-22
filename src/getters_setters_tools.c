/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters_setters_tools.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 17:07:43 by aahlyel           #+#    #+#             */
/*   Updated: 2023/06/20 23:50:03 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*set_pwd(char *o_pwd)
{
	char	*pwd;
	char	cwd[PATH_MAX];

	if (!getcwd(cwd, sizeof(cwd)) && o_pwd)
		pwd = ft_strdup(o_pwd);
	else if (!getcwd(cwd, sizeof(cwd)) && !o_pwd && get_owd("PWD="))
		return (ft_strdup(get_owd("PWD=")));
	else
		pwd = ft_strdup(cwd);
	return (free(o_pwd), pwd);
}

void	unset(t_hold *env, char ***path, char **pwd, char **homedir)
{
	int	i;

	i = 0;
	free(*homedir);
	*homedir = NULL;
	free(*pwd);
	*pwd = NULL;
	while (*path && (*path)[i])
		free((*path)[i++]);
	free(*path);
	*path = NULL;
	ft_lstclear(&(env->lst), free);
}

char	**set_env(char **env)
{
	char	**envp;

	envp = ft_dstrdup(env);
	return (envp);
}
