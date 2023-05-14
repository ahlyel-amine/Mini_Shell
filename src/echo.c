/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbrahm <aelbrahm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 21:19:53 by aahlyel           #+#    #+#             */
/*   Updated: 2023/05/14 05:55:57 by aelbrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	echo(t_cmd *cmd)
{
	t_builtin	*echo;

	echo = (t_builtin *)cmd;
	// if (echo->arguments)
	// {
		// printf(" === %s === \n", echo->arguments->str);
		expand_line(echo->arguments);
		// printf(" --- %s --- \n", echo->arguments->str);
	// }	
		
	puts("alo");
}