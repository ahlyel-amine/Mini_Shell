#include <unistd.h>
#include <string.h>
#include <stdio.h>
 #include <fcntl.h>
void	mydup2(int fd1, int fd2)
{
	close(fd2);
	open("amine", O_CREAT | O_APPEND | O_RDWR, 511);
}
int main(int argc, char const *argv[])
{
	// int fd = open ("amine", O_CREAT | O_APPEND | O_RDWR, 511);
	// mydup2(fd, STDOUT_FILENO);
	// write (STDOUT_FILENO, "wach wsselt l stdout ?", strlen("wach wsselt l stdout ?"));
	// write (fd, "allo ?", strlen("allo ?"));
	int a = 1;
	a = !a;
	printf("0 ^ 0 = %d\n ", a);
	a = !a;
	printf("0 ^ 0 = %d\n ", a);
	a = !a;
	printf("0 ^ 0 = %d\n ", a);
	a = !a;
	printf("0 ^ 0 = %d\n ", a);

	return 0;
}
