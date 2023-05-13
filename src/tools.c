/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbrahm <aelbrahm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 16:32:35 by aelbrahm          #+#    #+#             */
/*   Updated: 2023/05/12 16:34:39 by aelbrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	sp_free(char **splt)
{
	int	iter;

	iter = -1;
	while (splt[++iter])
		free(splt[iter]);
	free(splt);
}

char    *app_dup(char *arg)
{
    char    *buf;
    int     iter;
    buf = (char *)malloc((ft_strlen(arg)) * sizeof(char));
    iter = 0;
    while (*arg)
    {
        if (*arg == '+')
            arg++;
        buf[iter] = *arg;
        iter++;
        arg++;
    }
    return (buf);
}

int valid_id(char *var)
{
    if (!(ft_isalpha(*var) || *var == '_'))
        return (1);
    while (*var && *var != '=' && *var != '+')
    {    
        if (!(ft_isalnum(*var) || *var == '_'))
            return (1);
        var++;
    }
    if (*var && *var == '+' && !*(var + 1))
        return (1);
    else if (*var && *var == '+' && *(var + 1) != '=')
        return (1);
    return (0);
}