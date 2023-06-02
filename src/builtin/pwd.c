/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbrahm <aelbrahm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 21:18:52 by aelbrahm          #+#    #+#             */
/*   Updated: 2023/06/02 04:28:30 by aelbrahm         ###   ########.fr       */
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
		return (ft_putendl_fd(set__get_option_variables(0, GET | GET_PWD), out), 0);
	else if (!getcwd(cwd, sizeof(cwd)) && pwd)
		return (ft_putendl_fd(pwd, out), 0);
	else
		return (ft_putendl_fd(cwd, out), 0);
}