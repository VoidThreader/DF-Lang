#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int main(int argc, char **argv) {
	// The great wall of variables
	bool debug = false; // default is false, determines if the output is numeric or characters.
	const char *ext = ".df";
	const char *fname = NULL;
	int ext_len = strlen(ext);
	int exit_code = EXIT_SUCCESS; // default exit code

	// Wait, it's all file reading?
	if (argc < 2) {
		fprintf(stderr, "Error: Missing an input file. Usage: ./dumbfuck file.df\n");
		exit_code = EXIT_FAILURE;
		goto exit_program;
	}

	for (int i = 1; i < argc; i++) {
		if (strcmp(argv[i], "-d") == 0) {
			debug = true;
		} else {
			fname = argv[i];
		}
	}

	if (!fname) {
		fprintf(stderr, "Error: Missing an input file.\n");
		exit_code = EXIT_FAILURE;
		goto exit_program;
	}

	size_t flen = strlen(fname);
	if (flen < ext_len || strcmp(fname + flen - ext_len, ext) != 0) {
		fprintf(stderr, "Error: File must have a .df extension.\n");
		exit_code = EXIT_FAILURE;
		goto exit_program;
	}

	FILE *file = fopen(fname, "r");
	if (!file) {
		fprintf(stderr, "Error: file not found or could not be accessed.\n");
		exit_code = EXIT_FAILURE;
		goto exit_program;
	}

	if (fseek(file, 0, SEEK_END) != 0) {
		fprintf(stderr, "Error: Failed to seek file.\n");
		exit_code = EXIT_FAILURE;
		goto close_file;
	}

	long pos = ftell(file);
	if (pos < 0) {
		fprintf(stderr, "Error: File size could not be determined.\n");
		exit_code = EXIT_FAILURE;
		goto close_file;
	}

	size_t file_size = (size_t)pos;
	rewind(file);

	if (file_size == 0) {
		fprintf(stderr, "Error: File is empty.\n");
		exit_code = EXIT_FAILURE;
		goto close_file;
	}

	unsigned char *program = malloc(file_size + 1);
	if (!program) {
		fprintf(stderr, "Error: Memory allocation failed.\n");
		exit_code = EXIT_FAILURE;
		goto close_file;
	}

	size_t read_size = fread(program, 1, file_size, file);
	if (read_size < file_size && ferror(file)) {
		fprintf(stderr, "Error: Failed to read file completely.\n");
		exit_code = EXIT_FAILURE;
		goto free_program;
	}

	unsigned char accumulator = 0;
	program[read_size] = '\0';

	// The part that actually outputs something.
	for (size_t i = 0; i < read_size; i++) {
		unsigned char instruction = program[i];
		switch (instruction) {
			case '.':
				if (debug) printf("%u ", (unsigned)accumulator);
				else putchar(accumulator);
				break;
			case '+': accumulator++; break;
			case '-': accumulator--; break;
			case '*': accumulator *= accumulator; break;
			case '<': accumulator <<= 1; break;
			case '>': accumulator >>= 1; break;
			default: break;
		}
	}


	free_program:
	free(program);
	program = NULL;

	close_file:
	fclose(file);
	file = NULL;

	exit_program:
	exit(exit_code);
}