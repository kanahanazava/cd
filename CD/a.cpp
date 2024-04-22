/*
#include <stdio.h>
int main()
{
    int a;
    int b;
    scanf("%d",&a);
    scanf("%d",&b);
    printf("%d",a+b);
    return 0;
}
*/
#include <string.h>
#include <ctype.h>
#include <stdio.h>

void keyword(char str[10])
{
    // List of C keywords
    char keywords[][10] = {"for", "while", "do", "int", "float", "char", "double", "static", "switch", "case"};

    for (int i = 0; i < 10; i++)
    {
        if (strcmp(keywords[i], str) == 0)
        {
            printf("\n%s is a keyword", str);
            return;
        }
    }

    printf("\n%s is an identifier", str);
}

int main()
{
    FILE *f1, *f2, *f3;
    char c, str[10], st1[10];
    int num[100], lineno = 0, tokenvalue = 0, i = 0, j = 0, k = 0;

    printf("\nEnter the C program : "); /*gets(st1);*/
    f1 = fopen("input", "w");
    while ((c = getchar()) != EOF)
        putc(c, f1);
    fclose(f1);

    f1 = fopen("input", "r");
    f2 = fopen("identifier", "w");
    f3 = fopen("specialchar", "w");

    while ((c = getc(f1)) != EOF)
    {
        if (isdigit(c))
        {
            tokenvalue = c - '0';
            c = getc(f1);
            while (isdigit(c))
            {
                tokenvalue = tokenvalue * 10 + c - '0';
                c = getc(f1);
            }
            num[i++] = tokenvalue;
            ungetc(c, f1);
        }
        else if (isalpha(c) || c == '.')
        {
            putc(c, f2);
            c = getc(f1);
            while (isdigit(c) || isalpha(c) || c == '_' || c == '$')
            {
                putc(c, f2);
                c = getc(f1);
            }
            putc(' ', f2);
            ungetc(c, f1);
        }
        else if (c == '#')
        {
            // Handle preprocessor directive as a single entity
            while ((c = getc(f1)) != '\n' && c != EOF)
                putc(c, f2);
            putc(' ', f2);
            lineno++;
        }
        else if (c == ' ' || c == '\t')
            printf(" ");
        else if (c == '\n')
            lineno++;
        else
            putc(c, f3);
    }

    fclose(f2);
    fclose(f3);
    fclose(f1);

    printf("\nThe numbers in the program are");
    for (j = 0; j < i; j++)
        printf("%d ", num[j]);
    printf("\n");

    f2 = fopen("identifier", "r");
    k = 0;

    printf("The keywords and identifiers are:");
    while ((c = getc(f2)) != EOF)
    {
        if (c != ' ')
            str[k++] = c;
        else
        {
            str[k] = '\0';
            keyword(str);
            k = 0;
        }
    }

    fclose(f2);

    f3 = fopen("specialchar", "r");
    printf("\nSpecial characters are: ");
    while ((c = getc(f3)) != EOF)
        printf("%c", c);
    printf("\n");

    fclose(f3);
    printf("Total number of lines are: %d", lineno);

    return 0;
}
