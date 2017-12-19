//
// Created by Charl THERON on 2017/12/12.
//
#include <sys/mman.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

void *map_file(char *argv) {
    int fd;
    void *mapped_data;
    size_t size;
    fd = open(argv, O_RDONLY);

    if ((size = (size_t) lseek(fd, 0, SEEK_END)) < 0) {
        perror("lseek");
    }
    mapped_data = mmap((void *)0, size, PROT_READ | PROT_WRITE | PROT_EXEC, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);

    if (mapped_data == MAP_FAILED) {
        perror("mmap");
        exit(EXIT_FAILURE);
    }
    memcpy(mapped_data, argv,size);
    close(fd);
    return mapped_data;
}

int main(int argc, char **argv) {

    void *mapped_data;

    if (argc == 2) {
        mapped_data = map_file(argv[1]);

        return 0;
    }
    perror("ARGC");
}