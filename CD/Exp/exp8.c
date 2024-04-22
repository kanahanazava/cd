#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void generateThreeAddressCode(char *inputFilename, char *outputFilename);

int main() {
    char inputFilename[50], outputFilename[50];

    printf("Enter the filename of the intermediate code: ");
    scanf("%s", inputFilename);

    printf("Enter the filename to write the target code: ");
    scanf("%s", outputFilename);

    generateThreeAddressCode(inputFilename, outputFilename);

    printf("Three-address code generation complete!\n");

    return 0;
}

void generateThreeAddressCode(char *inputFilename, char *outputFilename) {
    FILE *inputFile = fopen(inputFilename, "r");
    FILE *outputFile = fopen(outputFilename, "w");

    if (!inputFile || !outputFile) {
        printf("Error: Unable to open files.\n");
        exit(1);
    }

    char op[10], operand1[10], operand2[10], result[10];
    int tempCount = 0;

    while (fscanf(inputFile, "%s %s %s %s", op, operand1, operand2, result) == 4) {
        if (strcmp(op, "+") == 0) {
            fprintf(outputFile, "t%d = %s + %s\n", tempCount, operand1, operand2);
            fprintf(outputFile, "%s = t%d\n", result, tempCount);
            tempCount++;
        } else if (strcmp(op, "-") == 0) {
            fprintf(outputFile, "t%d = %s - %s\n", tempCount, operand1, operand2);
            fprintf(outputFile, "%s = t%d\n", result, tempCount);
            tempCount++;
        } else if (strcmp(op, "*") == 0) {
            fprintf(outputFile, "t%d = %s * %s\n", tempCount, operand1, operand2);
            fprintf(outputFile, "%s = t%d\n", result, tempCount);
            tempCount++;
        } else if (strcmp(op, "/") == 0) {
            fprintf(outputFile, "t%d = %s / %s\n", tempCount, operand1, operand2);
            fprintf(outputFile, "%s = t%d\n", result, tempCount);
            tempCount++;
        } else {
            printf("Unsupported operation: %s\n", op);
        }
    }

    fclose(inputFile);
    fclose(outputFile);
}
