/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 21:19:53 by aahlyel           #+#    #+#             */
/*   Updated: 2023/05/14 11:49:12 by aahlyel          ###   ########.fr       */
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
}