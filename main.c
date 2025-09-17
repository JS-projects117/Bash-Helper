#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main(void) {

char charBuffer[1020400];
    fgets(charBuffer, 1024000, stdin);

    int length;
    for (int i = 0; charBuffer[i] != '\0'; i++) {
        if (charBuffer[i] == '\n') {
charBuffer[i] = '\0';
            length = i;;
            break;
        }
    }

    char* command[100];
    char* stringPart = strtok(charBuffer, " ");
int index = 0;
while (stringPart != NULL) {
  command[index] = stringPart;
   // printf("%s\n",  command[index]);
    stringPart = strtok(NULL, " ");
   ++index;
}
command[index] = NULL;

   //execvp(charBuffer, command);

    for (int j = 0; command[j] != NULL; j++) {
      printf("%s\n", command[j]);
    }

    return 0;
}