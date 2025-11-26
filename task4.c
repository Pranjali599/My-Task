#include <stdio.h>
#include <stdlib.h>

// Compress function
void compressFile(const char *input, const char *output) {
    FILE *fin = fopen(input, "r");
    FILE *fout = fopen(output, "w");

    if (!fin || !fout) {
        printf("Error opening files.\n");
        return;
    }

    char ch, prev;
    int count = 1;

    prev = fgetc(fin);
    if (prev == EOF) {
        printf("Input file is empty.\n");
        fclose(fin);
        fclose(fout);
        return;
    }

    while ((ch = fgetc(fin)) != EOF) {
        if (ch == prev) {
            count++;
        } else {
            fprintf(fout, "%d%c", count, prev);
            prev = ch;
            count = 1;
        }
    }

    // Write last character group
    fprintf(fout, "%d%c", count, prev);

    fclose(fin);
    fclose(fout);

    printf("Compression completed! Output: %s\n", output);
}

// Decompress function
void decompressFile(const char *input, const char *output) {
    FILE *fin = fopen(input, "r");
    FILE *fout = fopen(output, "w");

    if (!fin || !fout) {
        printf("Error opening files.\n");
        return;
    }

    int count;
    char ch;

    while (fscanf(fin, "%d%c", &count, &ch) == 2) {
        for (int i = 0; i < count; i++)
            fputc(ch, fout);
    }

    fclose(fin);
    fclose(fout);

    printf("Decompression completed! Output: %s\n", output);
}

int main() {
    int choice;
    char inputFile[50], outputFile[50];

    while (1) {
        printf("\n---- RLE DATA COMPRESSION TOOL ----\n");
        printf("1. Compress File\n");
        printf("2. Decompress File\n");
        printf("3. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter input file name: ");
                scanf("%s", inputFile);
                printf("Enter output file name: ");
                scanf("%s", outputFile);
                compressFile(inputFile, outputFile);
                break;

            case 2:
                printf("Enter compressed file name: ");
                scanf("%s", inputFile);
                printf("Enter output file name: ");
                scanf("%s", outputFile);
                decompressFile(inputFile, outputFile);
                break;

            case 3:
                return 0;

            default:
                printf("Invalid choice.\n");
        }
    }

    return 0;
}
