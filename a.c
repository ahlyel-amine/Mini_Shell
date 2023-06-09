#include <stdio.h>
#include <unistd.h>
int main(int argc, char const *argv[])
{
    printf("%c\n", 'a' + ('z' - 'b'));
    printf("%c\n", 'z' - ('y' - 'a'));
    return 0;
}
