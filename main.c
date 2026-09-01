#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

// CONFIG
#define MAX_LENGTH 256
#define CHARS_DIGITS "0123456789"
#define CHARS_LOWER "abcdefghijklmnopqrstuvwxyz"
#define CHARS_UPPER "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
#define CHARS_SPEC "!@#$%^&*()_+-=[]{}|;:,.<>?"

// Struct for CLI options
typedef struct {
    int length;
    char type[20]; // pin, general
    bool show_help;
} Options;

// Default options at init
static void init_options(Options *opts) {
    opts->length = 12;
    strcpy(opts->type, "general");
    opts->show_help = false;
}

// Print Help
static void print_help(const char *program) {
    printf("Format: teapass -l [length] -t [type]\n"
                    "-l -> Length from 4 to 256;\n"
                    "-t -> Type of password\n"
                    "-h -> Display this help message\n"
                    "\n"
                    "Options for [-t]:\n"
                    "\t - general > Usual password. Strong security, random symbols;\n"
                    "\t - pin > Generates a numeric PIN-code with desired length.\n");
}

// Argument parse
void parse_options(int argc, char **argv, Options *opts) {
    int i = 1;

    while (i < argc) {
        if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
            opts->show_help = true;
            i++;
        }
        else if (strcmp(argv[i], "-l") == 0) {
            if (i + 1 < argc) {
                opts->length = atoi(argv[i + 1]);
                if (opts -> length < 4 || opts -> length > MAX_LENGTH) {
                    fprintf(stderr, "Warning: length should be between 4 and %d.\n", MAX_LENGTH);
                    exit(1);
                }
                i += 2;
            } else {
                fprintf(stderr, "Warning: -l requires a value.\n");
                exit(1);
            }
        }
        else if (strcmp(argv[i], "-t") == 0) {
            if (i + 1 < argc) {
                if (strcmp(argv[i + 1], "general") ==0 ||
                    strcmp(argv[i + 1], "pin") == 0) {
                    strcpy(opts->type, argv[i + 1]);
                } else {
                    fprintf(stderr, "Warning: invalid type '%s. Use 'general' or 'pin'.\n", argv[i + 1]);
                    exit(1);
                }
                i += 2;
            } else {
                fprintf(stderr, "Warning: -t requires a value.\n");
                exit(1);
            }
        }
        else {
            fprintf(stderr, "Error: unknown option '%s'. Use -h for help.\n", argv[i]);
            exit(1);
        }
    }
}

// Password generator
void generate_passwd(const Options *opts) {
    const char *pool = NULL;
    char password[MAX_LENGTH+1];
    int pool_size = 0;

    // Selecting char pool based on passwd type
    if (strcmp(opts->type, "pin") == 0) {
        pool = CHARS_DIGITS;
        pool_size = strlen(CHARS_DIGITS);
    } else {
        pool = CHARS_LOWER CHARS_UPPER CHARS_DIGITS CHARS_SPEC;
        pool_size = 26 + 26 + 10 + strlen(CHARS_SPEC);
    }

    // Seeding generator
    srand(time(NULL));
    for (int i = 0; i < opts->length; i++) {
        int index = rand() % pool_size;
        password[i] = pool[index];
    }
    password[opts->length] = '\0';
    // Output
    printf("\nPassword: %s\n"
                    "Length: %d\n"
                    "Type: %s\n", password, opts->length, opts->type);
}

int main(int argc, char *argv[]) {
    Options opts;
    init_options(&opts);

    // Parsing command arguments
    parse_options(argc, argv, &opts);

    // Handle HELP
    if (opts.show_help) {
        print_help(argv[0]);
        exit(0);
    }

    // Generate passwd
    generate_passwd(&opts);
    return 0;
}