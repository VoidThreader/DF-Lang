#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv) {
    int debug = 0;
    long pos = 0;
    const char *ext = ".df";
    const char* fname = NULL;
    unsigned char *program = NULL;
    unsigned char accumulator = 0;
    size_t flen = 0;
    size_t ext_len = strlen(ext);
    size_t read_size = 0;
    size_t file_size = 0;
    FILE *fptr = NULL;

    if (argc < 2) {
        fprintf(stderr, "Error: Missing an input file.\n");
        return 1;
    }

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-d") == 0) {
            debug = 1;
        } else {
            fname = argv[i];
        }
    }

    if (!fname) {
        fprintf(stderr, "Error: Missing an input file.\n");
        return 1;
    }

    flen = strlen(fname);
    if (flen < ext_len || strcmp(fname + flen - ext_len, ext) != 0) {
        fprintf(stderr, "Error: File must have a .df extension.\n");
        return 1;
    }

    fptr = fopen(fname, "r");
    if (!fptr) {
        fprintf(stderr, "Error: file not found or could not be accessed.\n");
        return 1;
    }

    if (fseek(fptr, 0, SEEK_END) != 0) {
        fprintf(stderr, "Error: Failed to seek file.\n");
        fclose(fptr);
        fptr = NULL;
        return 1;
    }
    
    pos = ftell(fptr);
    if (pos < 0) {
        fprintf(stderr, "Error: File size could not be determined.\n");
        fclose(fptr);
        fptr = NULL;
        return 1;
    }

    file_size = (size_t)pos;
    rewind(fptr);

    if (file_size == 0) {
        fprintf(stderr, "Error: File is empty.\n");
        fclose(fptr);
        fptr = NULL;
        return 1;
    }

    program = malloc(file_size + 1);
    if (!program) {
        fprintf(stderr, "Error: Memory allocation failed.\n");
        fclose(fptr);
        fptr = NULL;
        return 1;
    }

    read_size = fread(program, 1, file_size, fptr);
    if (read_size < file_size && ferror(fptr)) {
        fprintf(stderr, "Error: Failed to read file completely.\n");
        free(program);
        fclose(fptr);
        program = NULL;
        fptr = NULL;
        return 1;
    }
    
    program[read_size] = '\0';
    fclose(fptr);
    fptr = NULL;

    for (size_t i = 0; i < read_size; i++) {
        unsigned char instruction = program[i];
        switch (instruction) {
            case '.':
                if (debug) printf("%u ", (unsigned)accumulator);
                else putchar(accumulator);                
                break;
            case '+': accumulator += 1; break;
            case '-': accumulator -= 1; break;
            case '*': accumulator *= accumulator; break;
            case '<': accumulator <<= 1; break;
            case '>': accumulator >>= 1; break;
            case '!': accumulator = 0; break;
            default: break;
        }
    }
    free(program);
    program = NULL;
    return 0;
}