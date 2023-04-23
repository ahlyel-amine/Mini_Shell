#include <stdio.h>

typedef struct s_cmd
{
	char	**cmd;
	int 	infile;
	int		outfile;
	int		errorfile;
}	t_cmd;

int main(int argc, char const *argv[])
{
	static t_cmd *a;

	if (a)
		puts("true");
	else
		puts("false");
	return 0;
}
