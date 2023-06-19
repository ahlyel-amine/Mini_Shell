/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbrahm <aelbrahm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 21:19:53 by aahlyel           #+#    #+#             */
/*   Updated: 2023/06/19 03:10:09 by aelbrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*ft_dstr_to_str(char **clone)
{
	char	*r_str;
	int		indx;

	indx = 0;
	r_str = ft_strdup("");
	while (clone && *clone)
	{
		r_str = ft_strjoin_free(r_str, clone[indx++]);
	}
	if (indx)
		free(clone);
	return (r_str);
}

void	tt_echo(t_arguments *cmd_args, int echo_has_option)
{
	char		*arg;

	transform_args(&cmd_args);
	arg = args_to_str(cmd_args);
	if (!echo_has_option)
		ft_putendl_fd(arg, out);
	else
		ft_putstr_fd(arg, out);
	glo_exit = 0;
	free(arg);
}
