#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <ctype.h>

#define MAX_LINE_LENGTH 65
#define NUM_MAP_TO_DIGIT 13

typedef struct {
    const char *str;
    const char *value;
} MapToDegit;

static const MapToDegit mapToDegit[NUM_MAP_TO_DIGIT] = {

    {"oneight", "18"},
    {"twone", "21"},
    {"eightwo", "82"},
    {"zero", "0"},
    {"one", "1"},
    {"two", "2"},
    {"three", "3"},
    {"four", "4"},
    {"five", "5"},
    {"six", "6"},
    {"seven", "7"},
    {"eight", "8"},
    {"nine", "9"}
};

const char *strrstr (const char *haystack, const char *needle) {

    if (!haystack || !needle) return NULL;
    if (!*needle) return haystack;

    const char *q = NULL;
    while (true) {
        const char *p = strstr(haystack, needle);
        if (!p) return q;
        q = p++;
        haystack = p;
    }
}
void insert_value_at_position(char *str, const char *replacement, size_t pos) {

    strncpy(str + pos, replacement, strlen(replacement));
}

void insertDigitsInFront (char *str) {

    for (size_t i = 0; i < NUM_MAP_TO_DIGIT; i++) {
        const char *firstOccurance = strstr(str, mapToDegit[i].str);
        if (!firstOccurance) continue;
        const char *lastOccurance = strrstr(str, mapToDegit[i].str);

        insert_value_at_position(str, mapToDegit[i].value, firstOccurance - str);
        if (firstOccurance != lastOccurance) {
            insert_value_at_position(str, mapToDegit[i].value, lastOccurance - str);
        }
    }
}

int16_t extractFirstAndLastDigit (const char *str) {

    const char *p = str;
    const char *q = str + strlen(str) - 1;

    while (*p && !isdigit(*p)) p++;
    while (q >= p && !isdigit(*q)) q--;

    if (p <= q) {
        int16_t firstDegit = *p - '0';
        int16_t lastDegit = *q - '0';
        printf("\n\033[1;36m   First and last digit of [%s]: [%d, %d]   \033[0m\n", str, firstDegit, lastDegit);
        return (firstDegit * 10) + lastDegit;
    }
    return -1;
}

int main (int argc, char *argv[]) {

    FILE *file;
    char line[MAX_LINE_LENGTH];
    uint16_t sum = 0;

    if (argc > 1) {

        file = fopen(argv[1], "r");
        if (!file) {

            printf("\n\033[1;31m Error opening file\n\033[0m");
            exit(EXIT_FAILURE);
        }
        size_t i = 0;
        while (fgets(line, MAX_LINE_LENGTH, file)) {

            strtok(line, "\n");
            printf("\nline %zu -----------------------------------------------------\n", ++i);
            printf("\n\033[1;30m   Original string: [%s]   \n\033[0m", line);
            insertDigitsInFront(line);
            printf("\n\033[1;30m   String after replacing words with digits: [%s]   \n\033[0m", line);
            int16_t res = extractFirstAndLastDigit(line);
            printf("\n\033[1;30m   First and last digit: [%d]   \n\033[0m", res);
            if (res != -1) sum += res;
        }

        printf("\n\033[1;30m    Sum -> %d   \n\033[0m", sum);
        fclose(file);
        return EXIT_SUCCESS;

    } else {
        printf("\n\033[1;31m    Error: no file specified    \n\033[0m");
        return EXIT_FAILURE;
    }
}