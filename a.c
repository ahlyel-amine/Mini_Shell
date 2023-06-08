#include <stdio.h>
#include <unistd.h>
int main(int argc, char const *argv[])
{
    printf("%d\n", STDIN_FILENO);
    printf("%d\n", isatty(STDIN_FILENO));
    return 0;
}
