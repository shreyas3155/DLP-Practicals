// #include <stdio.h>
// #include <string.h>
#include <stdbool.h>

#define MAX_LEN 100

const char *input;
int pos = 0;  // Position tracker in input string

// Function prototypes
bool S();
bool L();
bool L_();

// Function to match the expected character in input
bool match(char expected) {
    if (input[pos] == expected) {
        pos++;
        return true;
    }
    return false;
}

// Recursive function for S → ( L ) | a
bool S() {
    if (match('a')) {
        return true;
    } else if (match('(')) {
        if (L() && match(')')) {
            return true;
        }
    }
    return false;
}

// Recursive function for L → S L'
bool L() {
    if (S()) {
        return L_();
    }
    return false;
}

// Recursive function for L' → , S L' | ϵ (epsilon)
bool L_() {
    if (match(',')) {
        if (S()) {
            return L_();
        }
        return false; // If `, S` is not valid, return false
    }
    return true; // Epsilon transition (ϵ)
}

// Function to check if input is a valid string
void validate_string(const char *str) {
    input = str;
    pos = 0;
    
    if (S() && input[pos] == '\0') { // Ensure entire string is consumed
        printf("Valid string\n");
    } else {
        printf("Invalid string\n");
    }
}

// Main function to test different cases
int main() {
    const char *test_cases[] = {
        "a", "(a)", "(a,a)", "(a,(a,a),a)", "(a,a),(a,a)", // Valid cases
        "a)", "(a", "a,a", "a, (a,a),a" // Invalid cases
    };

    int num_cases = sizeof(test_cases) / sizeof(test_cases[0]);
    for (int i = 0; i < num_cases; i++) {
        printf("Input: %s -> ", test_cases[i]);
        validate_string(test_cases[i]);
    }

    return 0;
}
