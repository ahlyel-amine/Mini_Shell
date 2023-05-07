/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbrahm <aelbrahm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 19:19:53 by aelbrahm          #+#    #+#             */
/*   Updated: 2023/05/07 21:38:18 by aelbrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void    cd(t_cmd *cmd)
{
    t_builtin   *cd;
    // t_list        *path;
    // char        *home = getenv("HOME");
    // char        *oldpwd = getenv("OLDPWD");
    cd = (t_builtin *)cmd;
    // path = expander(cd->cmd);
    printf("%s\n", cd->cmd);
    // if (!*path || !ft_strncmp(path, "~", 2))
    // {
    //     chdir(home);
        
    // }
    // else if (!ft_strncmp(path, "-", 2))
    // {
    //     if (!oldpwd)
    //         printf("cd: OLDPWD not set\n");
    //     else
    //     {
    //         chdir(oldpwd);
    //         printf("<%s>\n", getenv("OLDPWD"));
    //     }   
    // }
    // else
    // {
    //     if (chdir(path) == -1)
    //         printf("cd: %s: %s\n", path, strerror(errno));
    // }
}