#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

#define EXP_WORD_BEGIN 0
#define EXP_WORD_END 1

void readFile(char* buffer, long long* size) {

    FILE* file;
    errno_t err = fopen_s(&file, "‪C:/Users/danil/Desktop/voyna.txt", "r");

    if (err != 0) {
        printf("File was not opened");
    }
    else {

        int c;
        long long counter = 0;
        while ((c = fgetc(file)) != EOF) {
            buffer[counter++] = (char)c;
        }

        buffer[counter++] = '\0';

        *size = counter;

        fclose(file);

    }
}

bool isDivSymb(char c) {
    if (c == '\n' || c == ' ' || c == '\0' || c == '&' || c == '!'
        || c == '?' || c == ':' || c == ']' || c == '[' || c == '.')
        return true;
    return false;
}

long long countWords(char* buffer, long long size) {

    int status = EXP_WORD_BEGIN;
    long long wordCount = 0;

    for (int i = 0; i < size; i++) {

        switch (status) {

        case EXP_WORD_BEGIN:
            if (isDivSymb(buffer[i])) break;
            if (buffer[i] == '-') break;
            if (buffer[i] == '[') break;
            if (isDivSymb(buffer[i]) && isDivSymb(buffer[i + 1]) && isDivSymb(buffer[i + 2]) && isDivSymb(buffer[i + 3])) {
                status = EXP_WORD_BEGIN;
                break;
            }
            wordCount++;
            status = EXP_WORD_END;
            break;

        case EXP_WORD_END:
            if (isDivSymb(buffer[i])) {
                status = EXP_WORD_BEGIN;
                break;
            }
            break;

        default: break;
        }

    }

    return wordCount;
}

int main() {

    setlocale(LC_ALL, "ru_RU.UTF-8");

    long long size = 0;
    const int N = 10 * 1024 * 1024;
    char* buffer = (char*)malloc(N * sizeof(char));

    readFile(buffer, &size);
    long long count = countWords(buffer, size);

    printf("%lld\n", count);
    printf("%lld\n", size);

    free(buffer);

    return 0;
}