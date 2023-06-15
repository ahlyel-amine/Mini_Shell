#ifndef BUILTIN_H
#define BUILTIN_H

# include "minishell.h"

void	do_cmp(char	*val, char **lst_cnt, short opt, size_t len);
short	is_export_var(char *str);

#endif