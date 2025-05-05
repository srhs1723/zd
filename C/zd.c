
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define TEMP_FILE "output.zd"
#define MAX_FILES 10
#define MAX_PATH 256
#define BUFFER_SIZE 4096

typedef struct {
    char path[MAX_PATH];
    char *content;
} FileData;

void read_file(const char *path, char **buffer) {
    FILE *f = fopen(path, "r");
    if (!f) {
        *buffer = strdup("");
        return;
    }

    fseek(f, 0, SEEK_END);
    long size = ftell(f);
    rewind(f);

    *buffer = malloc(size + 1);
    fread(*buffer, 1, size, f);
    (*buffer)[size] = '\0';
    fclose(f);
}

void write_file(const char *path, const char *content) {
    FILE *f = fopen(path, "w");
    if (!f) return;
    fwrite(content, 1, strlen(content), f);
    fclose(f);
}

void build_temp_file(FileData *files, int count) {
    FILE *temp = fopen(TEMP_FILE, "w");
    for (int i = 0; i < count; i++) {
        fprintf(temp, "file%d:%s\n", i+1, files[i].path);
        fprintf(temp, "%s\n", files[i].content);
    }
    fclose(temp);
}

void parse_temp_and_save(FileData *files, int count) {
    FILE *f = fopen(TEMP_FILE, "r");
    if (!f) return;

    char *file_buffers[MAX_FILES] = {0};
    char line[BUFFER_SIZE];
    int current = -1;
    size_t alloc_size = 0;

    while (fgets(line, sizeof(line), f)) {
        if (strncmp(line, "file", 4) == 0) {
            current++;
            alloc_size = 0;
            file_buffers[current] = malloc(BUFFER_SIZE);
            file_buffers[current][0] = '\0';
        } else if (current >= 0) {
            strcat(file_buffers[current], line);
        }
    }
    fclose(f);

    for (int i = 0; i <= current && i < count; i++) {
        write_file(files[i].path, file_buffers[i]);
        free(file_buffers[i]);
    }

    remove(TEMP_FILE);
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Usage: zd file1.txt link file2.txt [file3.txt ...]\n");
        return 1;
    }

    FileData files[MAX_FILES];
    int file_count = 0;

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "link") != 0) {
            strncpy(files[file_count].path, argv[i], MAX_PATH);
            read_file(argv[i], &files[file_count].content);
            file_count++;
        }
    }

    build_temp_file(files, file_count);

    char command[300];
    snprintf(command, sizeof(command), "nano %s", TEMP_FILE);
    system(command);

    parse_temp_and_save(files, file_count);

    for (int i = 0; i < file_count; i++) {
        free(files[i].content);
    }

    return 0;
}
