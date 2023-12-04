#include "kernel/types.h"
#include "user/user.h"

int main() {
    int fds[2];
    int pid;
    char buf = 'a';

    pipe(fds);
    pid = fork();
    if (pid == 0) {
        read(fds[0], &buf, 1);
        close(fds[0]);
        printf("%d: received ping\n", pid);
        write(fds[1], &buf, 1);
        close(fds[1]);
        exit(0);
    } else {
        write(fds[1], &buf, 1);
        close(fds[1]);
        read(fds[0], &buf, 1);
        close(fds[0]);
        printf("%d: received pong\n", pid);
        exit(0);
    }
}