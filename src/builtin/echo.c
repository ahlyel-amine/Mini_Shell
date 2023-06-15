/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbrahm <aelbrahm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 21:19:53 by aahlyel           #+#    #+#             */
/*   Updated: 2023/06/14 00:06:35 by aelbrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	tt_echo(t_cmd *cmd)
{
	t_builtin	*echo;
	char		*arg;

	echo = (t_builtin *)cmd;
	transform_args(&echo->arguments);
	arg = args_to_str(echo->arguments);
	if (!echo->has_option)
		ft_putendl_fd(arg, out);
	else
		ft_putstr_fd(arg, out);
	glo_exit = 0;
	free(arg);
}
//echo $PWD "$1PLO '$USER'"