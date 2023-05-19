/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbrahm <aelbrahm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 21:19:53 by aahlyel           #+#    #+#             */
/*   Updated: 2023/05/19 05:52:28 by aelbrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	echo(t_cmd *cmd)
{
	t_builtin	*echo;

	echo = (t_builtin *)cmd;
	t_arguments *arg = echo->arguments;
	t_arguments *down;
	expand_line(arg);
	while (arg)
	{
		if (arg->type == IS_STR || arg->type == IS_VARIABLE)
			printf(" type = %d --- %s ---\n", arg->type, arg->str);
		else
		{
			down = arg->down;
			while (down)
			{
				printf(" type = %d --- %s ---\n", down->type, down->str);
				down = down->next;
			}
		}
		arg = arg->next;
	}
	// if (echo->arguments)
	// {
		// printf(" === %s === \n", echo->arguments->str);
		// expand_line(echo->arguments);
		// printf(" --- %s --- \n", echo->arguments->str);
	// }	
}
//echo $PWD "$1PLO '$USER'"