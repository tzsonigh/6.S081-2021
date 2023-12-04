#include "kernel/types.h"
#include "user/user.h"
#include "kernel/param.h"

int main(int argc, char *argv[]) {
    char *newArgv[MAXARG];
    for (int i = 0; i < argc - 1; i++) {
        newArgv[i] = malloc(strlen(argv[i + 1]));
        strcpy(newArgv[i], argv[i + 1]);
    }

    char ch;
    char str[512];
    int cur = argc - 1;
    int cnt = 0;

    while (read(0, &ch, 1) != 0) {
        if (ch != ' ' && ch != '\n') {
            str[cnt++] = ch;
            continue;
        }

        newArgv[cur] = malloc(cnt + 1);
        strcpy(newArgv[cur], str);
        newArgv[cur++][cnt] = '\0';
        cnt = 0;

        if (ch == '\n') {
            newArgv[cur] = 0;
            cur = argc - 1;
            if (fork() == 0) {
                exec(newArgv[0], newArgv);
                exit(0);
            }
            wait(0);
        }
    }
    exit(0);
}