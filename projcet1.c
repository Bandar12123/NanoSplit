#include <stdio.h>
#include <stdlib.h>

long get_size(FILE *f) {
    fseek(f, 0, SEEK_END);
    long size = ftell(f);
    rewind(f);
    return size;
}

int main(int argc, char **argv) {
    if (argc != 3) return 1;

    int n = atoi(argv[2]);
    if (n <= 0 || n > 8) return 1;

    FILE *src = fopen(argv[1], "rb");
    if (!src) return 1;

    long total = get_size(src);
    long chunk = total / n;
    char *buf = malloc(chunk + (total % n));

    for (int i = 0; i < n; i++) {
        long current_chunk = chunk + (i == n - 1 ? total % n : 0);
        size_t read = fread(buf, 1, current_chunk, src);

        char name[256];
        sprintf(name, "%s.%d", argv[1], i);

        FILE *dest = fopen(name, "wb");
        if (dest) {
            fwrite(buf, 1, read, dest);
            fclose(dest);
        }
    }

    free(buf);
    fclose(src);
    return 0;
}