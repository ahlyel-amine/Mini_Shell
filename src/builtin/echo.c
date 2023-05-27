/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbrahm <aelbrahm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 21:19:53 by aahlyel           #+#    #+#             */
/*   Updated: 2023/05/26 20:08:51 by aelbrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	echo(t_cmd *cmd)
{
	t_builtin	*echo;
	char		*arg;

	echo = (t_builtin *)cmd;
	transform_args(&echo->arguments);
	arg = args_to_str(echo->arguments);
	if (!echo->has_option)
		ft_putendl_fd(arg, STDOUT_FILENO);
	else
		ft_putstr_fd(arg, STDOUT_FILENO);
	glo_exit = 0;	
}
//echo $PWD "$1PLO '$USER'"