/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbrahm <aelbrahm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 21:18:52 by aelbrahm          #+#    #+#             */
/*   Updated: 2023/05/22 12:39:37 by aelbrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	tt_pwd()
{
	char	cwd[PATH_MAX];
	char	*pwd;
	int		ret;

	ret = 0;
	pwd = get_owd("PWD=");
	if (!getcwd(cwd, sizeof(cwd)) && !pwd)
		return (printf("%s\n", set__get_option_variables(0, GET | GET_PWD)), 0);
	else if (!getcwd(cwd, sizeof(cwd)) && pwd)
		return (printf("%s\n", pwd), 0);
	else
		return (printf("%s\n", cwd), 0);
}