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
int main(int argc, char *argv[])
{
	printf("%d\n", echo_has_option("-n  \"   -sn\" -n -n \"-n\""));
	return 0;
}
