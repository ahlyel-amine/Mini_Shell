/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbrahm <aelbrahm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 21:18:52 by aelbrahm          #+#    #+#             */
/*   Updated: 2023/05/13 21:54:31 by aelbrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	tt_pwd()
{
	char	cwd[PATH_MAX];
	int		ret;

	ret = 0;
	if (!getcwd(cwd, sizeof(cwd)))
		return (printf("Minishell : %s\n", strerror(errno)),(1));
	ret = chdir(cwd);
	if (ret == -1)
		printf("pwd: error:  %s\n", strerror(errno));
	return ret;
}