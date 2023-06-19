/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbrahm <aelbrahm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 21:18:52 by aelbrahm          #+#    #+#             */
/*   Updated: 2023/06/19 09:48:09 by aelbrahm         ###   ########.fr       */
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
		ft_putendl_fd(set__get_option_variables(0, GET | GET_PWD), e_glb.out), 0);
	else if (!getcwd(cwd, sizeof(cwd)) && pwd)
		return (ft_putendl_fd(pwd, e_glb.out), 0);
	else
		return (ft_putendl_fd(cwd, e_glb.out), 0);
}
