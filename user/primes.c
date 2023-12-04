#include "kernel/types.h"
#include "user/user.h"

void getPrimes(int fds[2]) {
    close(fds[1]);

    int prime;
    if (!read(fds[0], &prime, 4)) return;
    printf("prime %d\n", prime);

    int newFds[2];
    pipe(newFds);

    if (fork() == 0) {
        getPrimes(newFds);
    } else {
        int num;
        while (read(fds[0], &num, 4)) {
            if (num % prime) write(newFds[1], &num, 4);
        }
        // close(fds[0]);
        close(newFds[1]);
        wait(0);
    }
    exit(0);
}

int main() {
    int fds[2];
    pipe(fds);

    if (fork() == 0) {
        getPrimes(fds);
    } else {
        for (int i = 2; i <= 35; i++) write(fds[1], &i, 4);
        close(fds[1]);
        wait(0);
    }
    exit(0);
}