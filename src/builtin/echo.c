/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbrahm <aelbrahm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 21:19:53 by aahlyel           #+#    #+#             */
/*   Updated: 2023/06/07 15:55:22 by aelbrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	tt_echo(t_cmd *cmd)
{
	t_builtin	*echo;
	char		*arg;

	echo = (t_builtin *)cmd;
	// transform_args(&echo->arguments);
	t_arguments	*nl;

	nl = NULL;
	expand_line(echo->arguments);
	wild_cards(&echo->arguments);
	args_join(&echo->arguments);
	args_move_down(&echo->arguments, &nl);
	arg = args_to_str(echo->arguments);
	if (!echo->has_option)
		ft_putendl_fd(arg, out);
	else
		ft_putstr_fd(arg, out);
	glo_exit = 0;
	free(arg);	
}
//echo $PWD "$1PLO '$USER'"