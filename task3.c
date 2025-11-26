#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char keywords[][10] = {
    "int", "float", "char", "if", "else",
    "for", "while", "return", "void"
};

int isKeyword(char *word) {
    for (int i = 0; i < 9; i++) {
        if (strcmp(word, keywords[i]) == 0)
            return 1;
    }
    return 0;
}

int isOperator(char ch) {
    char operators[] = "+-*/=%<>!";
    for (int i = 0; operators[i] != '\0'; i++) {
        if (ch == operators[i])
            return 1;
    }
    return 0;
}

int isSeparator(char ch) {
    char separators[] = "(),;{}[]";
    for (int i = 0; separators[i] != '\0'; i++) {
        if (ch == separators[i])
            return 1;
    }
    return 0;
}

int main() {
    FILE *fp;
    char fileName[50];
    char ch, buffer[50];
    int idx = 0;

    printf("Enter input file name: ");
    scanf("%s", fileName);

    fp = fopen(fileName, "r");
    if (!fp) {
        printf("Error: File not found.\n");
        return 1;
    }

    printf("\n--- TOKENS ---\n");

    while ((ch = fgetc(fp)) != EOF) {

        // Identify identifiers/keywords/numbers
        if (isalnum(ch) || ch == '_') {
            buffer[idx++] = ch;
        } else {
            if (idx != 0) {
                buffer[idx] = '\0';

                if (isKeyword(buffer))
                    printf("<KEYWORD, %s>\n", buffer);
                else if (isdigit(buffer[0]))
                    printf("<NUMBER, %s>\n", buffer);
                else
                    printf("<IDENTIFIER, %s>\n", buffer);

                idx = 0;
            }

            // Check for operators
            if (isOperator(ch)) {
                printf("<OPERATOR, %c>\n", ch);
            }

            // Check for separators
            else if (isSeparator(ch)) {
                printf("<SEPARATOR, %c>\n", ch);
            }
        }
    }

    fclose(fp);

    return 0;
}
