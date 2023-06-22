/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 21:18:52 by aelbrahm          #+#    #+#             */
/*   Updated: 2023/06/19 12:53:55 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	tt_pwd(void)
{
	char	cwd[PATH_MAX];
	char	*pwd;
	int		ret;

	ret = 0;
	pwd = get_owd("PWD=");
	if (!getcwd(cwd, sizeof(cwd)) && !pwd)
		return (\
		ft_putendl_fd(set__get_option_variables(0, \
		GET | GET_PWD), g_glb.out), 0);
	else if (!getcwd(cwd, sizeof(cwd)) && pwd)
		return (ft_putendl_fd(pwd, g_glb.out), 0);
	else
		return (ft_putendl_fd(cwd, g_glb.out), 0);
}
