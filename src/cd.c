/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbrahm <aelbrahm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 14:39:32 by aelbrahm          #+#    #+#             */
/*   Updated: 2023/05/03 20:43:49 by aelbrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
// char    *var_expand(char *arg)
// {
//     char    *var;
//     char    buf[1024];
//     short   iter = 0;
//     int i = 0;
//     var = ft_memchr(arg, 0x22, ft_strlen(arg)) + 1;
//     while (*arg)
//     {
//         if (*arg != 0x22 && *arg)
//             buf[iter] = *arg;
//         arg++;
//     }
//     while(var && *(var + (iter)))
//         if (ft_isalnum(*(var + iter)) || *(var + iter) == 0x5f)
//             iter++;
//         else
//             break;
//     t_hold *env = (t_hold *)set__get_option_variables(0, (GET | GET_ENV));
//     var = ft_substr(arg, (var) - (arg), iter);
//     t_list *tmp = env->lst;
//     while (tmp)
//     {
//         if (ft_strncmp(var, tmp->content, ft_strlen(var)))
//             tmp = tmp->next;
//         else
//             while(((char *)(tmp->content)) && ((char *)tmp->content)[i])
//                 buf[iter++] = ((char *)tmp->content)[i++];
//     }
//     return (buf);
//     // if (!var)
//     //     return (NULL);
//     // return (ft_strdup(var + iter));
// }
void    cd(t_cmd *cmd)
{
    t_builtin *cd;
    cd = (t_builtin *)cmd;
    // printf("%s\n", var_expand(cd->cmd));
    // printf("%s\n", cd->cmd);
    // char *old = getenv("OLDPWD");
    // printf("<%s>\n", old);
    // char cwd[1024];
    // if (getcwd(cwd, sizeof(cwd)) != NULL) {
    //     setenv("OLDPWD", getenv("PWD"), 1);
    //     setenv("PWD", cwd, 1);
    // }
    // t_hold *env = (t_hold *)(set__get_option_variables(0, (GET | GET_ENV)));
    // char **path = set__get_
    // t_list *tmp = env->lst;
    // puts("alo\n");
	// while (tmp)
	// {
    //     printf(" «%s« \n", tmp->content);
    //     tmp = tmp->next;
    // }	
}