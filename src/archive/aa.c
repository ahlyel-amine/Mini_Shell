#include <unistd.h>
#include <string.h>
#include <stdio.h>
 #include <fcntl.h>
 
void	mydup2(int fd1, int fd2)
{
	close(fd2);
	open("amine", O_CREAT | O_APPEND | O_RDWR, 511);
}

int	ft_isspace(int c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}

int	echo_has_option(char *line)
{
	int	i;
	int	has_option;

	i = 0;
	has_option = 0;
	while (line[i])
	{
		while (ft_isspace(line[i]))
			i++;
		if (line[i] == '-' && line[i + 1] == 'n')
		{
			i++;
			while (line[i] == 'n')
				i++;
		}
		else if (line[i] == '\"' && line[i + 1] == '-' && line[i + 2] == 'n')
		{
			i += 2;
			while (line[i] == 'n')
				i++;
			if (line[i] == '\"')
				i++;
		}
		if (ft_isspace(line[i]) || !line[i])
			has_option = 1;
		else
			break ;
	}
	return (has_option);
}

#include <unistd.h>
#include <stdlib.h>
int main(int argc, char *argv[], char **envp)
{
	// printf("%d\n", echo_has_option("-n  \"   -sn\" -n -n \"-n\""));
	printf("%d\n", access("//", X_OK));
	char	**a;
	a = malloc(sizeof (char *) * 2);
	a[0] = malloc(10);
	a[0][0] = '~';
	a[0][1] = '/';
	a[0][2] = 'D';
	a[0][3] = 'e';
	a[0][4] = 's';
	a[0][5] = 'k';
	a[0][6] = 't';
	a[0][7] = 'o';
	a[0][8] = 'p';
	a[0][9] = 0;
	a[1] = NULL;
	if (execve("~/Desktop", a, envp) == -1)
		perror("");
	return 0;
}
