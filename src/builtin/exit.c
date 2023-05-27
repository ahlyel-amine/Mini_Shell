/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbrahm <aelbrahm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 16:28:10 by aelbrahm          #+#    #+#             */
/*   Updated: 2023/05/26 20:24:52 by aelbrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

short	valid_ExecVal(char *val)
{
	short	idex;
	idex = 0;
	while (val[idex] && ft_isdigit(val[idex]))
		idex++;
	if (!val[idex] && idex)
		return (1);
	else
		return (0);
}

unsigned char	exit_val(char *str)
{
	unsigned long	res;
	short			sign;
	char			*hold;

	sign = 1;
	res = 0;
	while (*str == 0x20)
		str++;
	hold = str;
	if (*str == 0x2d || *str == 0x2b)
		if (*(str++) == 0x2d)
			sign = -1;
	if (!valid_ExecVal(str))
		return (printf("Minishell: exit: %s: numeric argument required\n", hold), 255);
	while (*str)
		res = res * 0xA + (*(str++) - 0x30);
	if (res > LONG_MAX && sign > 0)
		return (printf("Minishell: exit: %s: numeric argument required\n", hold), 255);
	else if (res > (9223372036854775808UL) && sign < 0)
		return (printf("Minishell: exit: %s: numeric argument required\n", hold), 255);
	else
		return ((unsigned char)(res) * sign);
}

void	ft_atexit(int val, t_cmd *cmd)
{
	ft_putendl_fd("exit", 2);	
	set__get_option_variables(0, FREE);
	builtin_destructor(cmd);
	glo_exit = val;
	exit(val);
}

void	ft_exit(t_cmd *cmd)
{
	t_builtin	*_exit;
	char		**args;
	int			val;
	val = 0;
	_exit = (t_builtin *)cmd;
	transform_args(&_exit->arguments);
	args = args_to_dblstr(_exit->arguments);
	while (args && args[val])
		val++;
	if (val > 1)
	{
		ft_putendl_fd("Minishell: exit: too many arguments", STDERR_FILENO);
		glo_exit = 1;
	}	
	else if (val == 1)
		glo_exit = (int)exit_val(_exit->arguments->str);
	if (args)
		sp_free(args);
	printf("%d\n", glo_exit);
}