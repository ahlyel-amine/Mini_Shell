/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 12:50:27 by aahlyel           #+#    #+#             */
/*   Updated: 2023/06/24 23:43:45 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct s_lsttoken	t_lsttoken;

typedef struct s_arguments
{
	char					*str;
	unsigned short			q:1;
	unsigned short			type:6;
	struct s_arguments		*down;
	struct s_arguments		*next;
}	t_arguments;

typedef struct s_token
{
	int						type;
	char					*line;
	int						start;
	int						len;
	t_lsttoken				*down;
}	t_token;

typedef struct s_components
{
	int						infile;
	int						outfile;
	int						close_red;
	int						stuck;
	unsigned int			is_pipe:1;
	int						*fd;
}	t_components;

typedef struct s_lsttoken
{
	t_token				t_;
	struct s_lsttoken	*next;
}	t_lsttoken;

typedef struct s_hold
{
	t_list	*lst;
	int		size:16;
}	t_hold;

typedef struct s_globe
{
	char	**backup;
	t_hold	*s_env;
	int		exit_val;
	int		in_cmd;
	int		out;
	int		ctrl_c;
	int		is_sig;
	int		is_pipe;
}	t_globe;

typedef struct s_two_ptr
{
	int	*i;
	int	*k;
}	t_2ptr_int;

typedef struct s_2ptr_t_lsttoken
{
	t_lsttoken	*front;
	t_lsttoken	*back;
}	t_2ptr_t_lsttoken;

typedef struct s_var
{
	unsigned int	quote:1;
	unsigned int	dquote:1;
}	t_var;

t_globe						g_glb;

#endif