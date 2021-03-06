#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <errno.h>

static int n = 0;
const char message[] = "ctrl_slash\n";
const char message1[] = "ctrl_z\n";
const char message2[] = "ctrl_c\n";


void ctrl_z_handler(int s)
{
    int save_errno = errno;
    signal(SIGTSTP, ctrl_z_handler);

    n++;
    write(1, message1, sizeof(message1)-1);

    errno = save_errno;
}

void ctrl_slash_handler(int s)
{
    int save_errno = errno;
    signal(SIGQUIT, ctrl_slash_handler);

    n++;
    write(1, message, sizeof(message)-1);

    errno = save_errno;
}

void ctrl_c_handler(int s)
{
    int save_errno = errno;
    signal(SIGINT, ctrl_c_handler);

    n++;
    write(1, message2, sizeof(message2)-1);

    errno = save_errno;
}


int main()
{
    signal(SIGQUIT, ctrl_slash_handler);
    signal(SIGTSTP, ctrl_z_handler);
    signal(SIGINT, ctrl_c_handler);

    while(n < 25)
        pause();

    return 0;
}
