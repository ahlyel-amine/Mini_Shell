/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destructors2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 00:14:36 by aahlyel           #+#    #+#             */
/*   Updated: 2023/06/13 00:16:23 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	and_destructor(t_cmd *structor)
{
	t_and	*and;

	and = (t_and *)structor;
	free(and);
}

void	or_destructor(t_cmd *structor)
{
	t_or	*or;

	or = (t_or *)structor;
	free(or);
}

void	invalid_destructor(t_cmd *structor)
{
	t_invalid	*invalid;

	invalid = (t_invalid *)structor;
	free(invalid->str);
	free(invalid);
}

void	builtin_destructor(t_cmd *structor)
{
	t_builtin	*builtin;
	t_arguments	*args;
	t_arguments	*tmp;

	builtin = (t_builtin *)structor;
	arguments_destructor(&builtin->arguments);
	free(builtin->builtin);
	free(builtin);
}
