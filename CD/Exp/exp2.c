//2.    Write a program to recognize strings under ‘a’, ‘a*b+’, ‘abb’.


#include <stdio.h>
#include <string.h>

int matchPattern(const char *str) {
    int i = 0;
    if(str[i]=='a' && str[i+1]=='\0')return 1;
    // Check for 'a'
    if (str[i] == 'a') {
        i++;
        if (str[i] == 'b' && str[i + 1] == 'b' && str[i + 2] == '\0') {
            return 1; // Matched 'abb'
        }
        while(str[i]=='a')
        {
            i++;
        }
        // Check for 'a*b+'
        while (str[i] == 'b') {
            i++;
        }
       
        if(str[i-1]=='b' && str[i]=='\0')return 1;

        return 0;
    }
    if(str[i]=='b')
    {
        while(str[i]=='b')
        {
            i++;
        }
        if(str[i]=='\0')return 1;
    }

    return 0; // Did not match any pattern
}

int main() {
    char input[100];

    printf("Enter a string: ");
    scanf("%s", input);

    if (matchPattern(input)) {
        printf("String matched one of the patterns.\n");
    } else {
        printf("String did not match any pattern.\n");
    }

    return 0;
}
