#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>

#define CLEAR "\e[1;1H\e[2J"

#define CALCULATOR "1"
#define READFILE "2"
#define NEWFILE "3"
#define MESSAGEFRIENDS "4"

bool mainMenu();
bool calculator();
int yesorno();

int main(){

    if(!mainMenu()){
        printf("An error eccoured, please restart the program!\n");
        exit(EXIT_FAILURE);
    }

    return 0;
}

bool mainMenu(){
    bool success = true;
    char *choice = NULL;
    size_t buffsize = 3;

    while(success){
        printf(CLEAR);
        printf("Program For Grandma's, Press One of the following number and then Enter to acess it.\n\n");

        printf("Press 1 to acess a calculator\n");
        printf("Press 2 to read a file from a certain location\n");
        printf("Press 3 to make a new file that contains text\n");
        printf("Press 4 to message your friends (COMING SOON)\n");

        printf("\n\nEnter your choice...\n");

        if(!(choice = (char*)malloc(buffsize * sizeof(char)))){
            printf("An error eccoured!\nYou will be sent back to the beginning.\n\n");
            sleep(3);
            success = false;    
        }

        getline(&choice, &buffsize, stdin);

        choice[strcspn(choice, "\n")] = '\0';       //removes any newlines from buffer

        printf("You entered %s is this correct? y/n\n", choice);

        if(yesorno() == 0){
            printf("\nRerouting you to your choice...\n");
            sleep(1);

            if(strcmp(choice, CALCULATOR) == 0)
                calculator();
            // else if(strcmp(choice, READFILE) == 0)
            //     readFile();
            // else if(strcmp(choice, NEWFILE) == 0)
            //     newFile();

            printf(CLEAR);
        }

        free(choice);
        choice = NULL;
    }

    return success;
}

bool calculator(){
    printf(CLEAR);
    printf("Enter a mathmatical calculation to be preformed... (value1 <+, -, *, /> value2)\n");

    char operator = '\0';
    float value1, value2;
    bool restart = false;

    while(!restart){
        scanf("%f %c %f", &value1, &operator, &value2);

        switch(operator){
            case '+':
            printf("\nAnswer is: %f\n", value1 + value2);
            sleep(3);
            printf(CLEAR);
            break;

            case '-':
            printf("\nAnswer is: %f\n", value1 - value2);
            sleep(3);
            printf(CLEAR);
            break;

            case '*':
            printf("\nAnswer is: %f\n", value1 * value2);
            sleep(3);
            printf(CLEAR);
            break;

            case '/':
            printf("\nAnswer is: %f\n", value1 / value2);
            sleep(3);
            printf(CLEAR);
            break;

            default:
            printf("The mathmatical operator you entered is invalid, would you like to retry?\n");
            if(yesorno() == 0)
                restart = true;
            else
                mainMenu();
            break;
        }
    }

    mainMenu();
}

int yesorno(){
    char *buff;
    size_t buffsize = 3;

    if(!(buff = (char*)malloc(buffsize * sizeof(char)))){
        printf("An error eccoured. Sending you back to main menu!\n");
        mainMenu();
    }

    getline(&buff, &buffsize, stdin);    

    buff[strcspn(buff, "\n")] = '\0';

    if(strcmp(buff, "y") == 0 || strcmp(buff, "Y") == 0){
        free(buff);
        return 0;
    }
    else{
        free(buff);
        return 1;
    }
}