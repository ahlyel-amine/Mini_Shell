#ifndef EXECUTE_H
# define EXECUTE_H

# include "minishell.h"
int	pipe_executer(t_cmd *cmd, int infile, int outfile);
int	pipe_part_executer(t_cmd *cmd, int infile, int outfile);
int	or_executer(t_cmd *cmd, int infile, int outfile);
int	or_part_executer(t_cmd *cmd, int infile, int outfile);
char	*get_path(char *cmd);
int	cmd_executer(t_cmd *cmd, int infile, int outfile);
int	and_executer(t_cmd *cmd, int infile, int outfile);
int	and_part_executer(t_cmd *cmd, int infile, int outfile);
int	redirect_executer(t_cmd *cmd, int infile, int outfile);
int builtin_executer(t_cmd *cmd, int infile, int outfile);
#endif