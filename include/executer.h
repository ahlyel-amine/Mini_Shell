#ifndef EXECUTER_H
# define EXECUTER_H

# include "minishell.h"

void	execute_line(t_cmd *cmd);
int		and_executer(t_cmd *cmd, int infile, int outfile, int *fd);
int		builtin_executer(t_cmd *cmd, int infile, int outfile, int *fd);
int		cmd_executer(t_cmd *cmd, int infile, int outfile, int *fd);
int		cmd_sig_check(char *path, int status);
int		or_executer(t_cmd *cmd, int infile, int outfile, int *fd);
int		pipe_executer(t_cmd *cmd, int infile, int outfile, int *fd);
int		redirect_executer(t_cmd *cmd, int infile, int outfile, int *fd);



int	builtin_execiter(t_arguments *args, char *cmd, int outfile);
char	**child_vars(void);

#endif