#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_INPUT_SIZE 256

void generate_random_input(char *input, size_t max_length) {
    const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!@#$%^&*()_+";
    const size_t charset_size = sizeof(charset) - 1;

    size_t length = rand() % (max_length + 1);

    for (size_t i = 0; i < length; i++) {
        input[i] = charset[rand() % charset_size];
    }

    input[length] = '\0';
}

int main() {
    srand(time(NULL));
    char input[MAX_INPUT_SIZE];

    // Path to your program binary
    const char *program_path = "./overflow";

    // Number of test cases to generate
    const int num_test_cases = 100;

    for (int i = 0; i < num_test_cases; i++) {
        generate_random_input(input, MAX_INPUT_SIZE);

        // Run your program with the generated input
        char command[MAX_INPUT_SIZE + 50];
        snprintf(command, sizeof(command), "%s \"%s\"", program_path, input);

        int result = system(command);
        if (result != 0) {
            printf("Crash detected with input: %s\n", input);
        }
    }

    printf("Fuzzing complete.\n");

    return 0;
}

