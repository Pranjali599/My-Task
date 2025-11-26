
#include <stdio.h>
#include <stdlib.h>

void createFile();
void writeFile();
void appendFile();
void readFile();

int main() {
    int choice;

    while (1) {
        printf("\n===== FILE HANDLING PROGRAM =====\n");
        printf("1. Create a File\n");
        printf("2. Write to File\n");
        printf("3. Append to File\n");
        printf("4. Read File\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();  // clear newline from input buffer

        switch (choice) {
            case 1: createFile(); break;
            case 2: writeFile(); break;
            case 3: appendFile(); break;
            case 4: readFile(); break;
            case 5: exit(0);
            default: printf("Invalid choice! Try again.\n");
        }
    }

    return 0;
}

void createFile() {
    FILE *fp;
    char filename[50];

    printf("Enter filename to create: ");
    scanf("%s", filename);

    fp = fopen(filename, "w");  // creates an empty file
    if (fp == NULL) {
        printf("Error creating file!\n");
        return;
    }

    printf("File '%s' created successfully.\n", filename);
    fclose(fp);
}

void writeFile() {
    FILE *fp;
    char filename[50];
    char text[200];

    printf("Enter filename to write: ");
    scanf("%s", filename);
    getchar(); 

    fp = fopen(filename, "w");  // overwrite file
    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    printf("Enter text to write (end with ENTER):\n");
    fgets(text, sizeof(text), stdin);

    fprintf(fp, "%s", text);
    printf("Data written successfully.\n");

    fclose(fp);
}

void appendFile() {
    FILE *fp;
    char filename[50];
    char text[200];

    printf("Enter filename to append: ");
    scanf("%s", filename);
    getchar();

    fp = fopen(filename, "a");  // append mode
    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    printf("Enter text to append (end with ENTER):\n");
    fgets(text, sizeof(text), stdin);

    fprintf(fp, "%s", text);
    printf("Data appended successfully.\n");

    fclose(fp);
}

void readFile() {
    FILE *fp;
    char filename[50];
    char buffer[200];

    printf("Enter filename to read: ");
    scanf("%s", filename);

    fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Error opening file or file does not exist!\n");
        return;
    }

    printf("\n----- FILE CONTENT -----\n");
    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        printf("%s", buffer);
    }
    printf("\n-------------------------\n");

    fclose(fp);
}
