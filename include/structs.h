/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 12:50:27 by aahlyel           #+#    #+#             */
/*   Updated: 2023/06/19 18:49:10 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct s_lsttoken	t_lsttoken;

typedef struct s_arguments
{
	struct s_arguments		*next;
	struct s_arguments		*down;
	char					*str;
	unsigned short			type:6;
	unsigned short			q:1;
}	t_arguments;

typedef struct s_token
{
	t_lsttoken				*down;
	char					*line;
	int						start;
	int						len;
	int						type;
}	t_token;

typedef struct s_components
{
	int						*fd;
	int						infile;
	int						outfile;
	unsigned int			is_pipe:1;
}	t_components;

typedef struct s_lsttoken
{
	struct s_lsttoken	*next;
	t_token				t_;
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