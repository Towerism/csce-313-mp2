#include <unistd.h>
#include <sys/wait.h>
#include "reqchannel.h"

int main(int argc, char* argv[]) {
    pid_t parent = getpid();
    pid_t pid = fork();
    if (pid > 0) {
        execv("simpleclient", argv);
    } else {
        printf("Hi from child\n");
        execv("dataserver", argv);
    }
}
