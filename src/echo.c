/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbrahm <aelbrahm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 21:19:53 by aahlyel           #+#    #+#             */
/*   Updated: 2023/05/18 19:03:17 by aelbrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	echo(t_cmd *cmd)
{
	t_builtin	*echo;

	echo = (t_builtin *)cmd;
	t_arguments *arg = echo->arguments;
	printf("arg = %d\n", arg->type);
	while (arg)
	{
		if (arg->type == IS_STR || arg->type == IS_VARIABLE)
			printf(" type = %d --- %s ---\n", arg->type, arg->str);
		else
		{	
			while (arg->down)
			{
				printf(" type = %d --- %s ---\n", arg->down->type, arg->down->str);
				arg->down = arg->down->next;
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