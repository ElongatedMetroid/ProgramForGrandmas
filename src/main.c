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
bool readFile();
bool newFile();
int yesorno();

int main(){

    while(1){
        if(!mainMenu()){
            printf("An error eccoured, please restart the program!\n");
            exit(EXIT_FAILURE);
        }
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

            if(strcmp(choice, CALCULATOR) == 0){
                calculator();
            }
            else if(strcmp(choice, READFILE) == 0){
                if(!readFile()){
                    printf("Error Eccoured while reading the file\n");
                    sleep(2);
                }
            }
            else if(strcmp(choice, NEWFILE) == 0){
                if(!newFile()){
                    printf("Error Eccoured while making a new file\n");
                    sleep(2);
                }
            }

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
            break;

            case '-':
            printf("\nAnswer is: %f\n", value1 - value2);
            break;

            case '*':
            printf("\nAnswer is: %f\n", value1 * value2);
            break;

            case '/':
            printf("\nAnswer is: %f\n", value1 / value2);
            break;

            default:
            printf("The mathmatical operator you entered is invalid, would you like to retry?\n");
            if(yesorno() == 0)
                restart = true;
            else
                return 0;
            break;
        }
        break;
    }

    sleep(3);

    mainMenu();
}

bool readFile(){
    bool success = true;
    char *filePath = NULL;
    char *fileLineBuff = NULL;
    size_t buffsize = 255;
    FILE *fp = NULL;

    printf(CLEAR);

    if(!(filePath = (char*)malloc(buffsize * sizeof(char)))){
        printf("Error eccoured while allocating memory for the file path\n");
        sleep(3);
        success = false;
        return success;
    }

    printf("Enter a file you would like to read (EX: /home/name/documents/text.txt)\n");
    getline(&filePath, &buffsize, stdin);
    filePath[strcspn(filePath, "\n")] = '\0';

    if(!(fp = fopen(filePath, "r"))){
        printf("Error eccoured while opening the file!\nPossibly a non-existant file (path)\n");
        sleep(3);
        success = false;
        return success;
    }

    free(filePath);

    if(!(fileLineBuff = (char*)malloc(buffsize * sizeof(char)))){
        printf("Error eccoured while allocating memory for the file line buffer\n");
        sleep(3);
        success = false;
        return success;
    }

    printf("\n*************************************\n");

    while(!feof(fp)){
        getline(&fileLineBuff, &buffsize, fp);
        printf("%s", fileLineBuff);
    }

    printf("\n*************************************\n");

    fclose(fp);
    free(fileLineBuff);

    printf("\n\nPress enter to continue...\n");
    getchar();
    return success;
}

bool newFile(){
    bool success = true;
    FILE *fp = NULL;
    char ch = '\0';
    char *fileNameBuff = NULL;
    size_t buffsize = 255;

    printf(CLEAR);
    printf("What would you like to name to new file?\n");

    if(!(fileNameBuff = (char*)malloc(buffsize * sizeof(char)))){
        printf("Error while allocating memory for the file name buffer!\n");
        sleep(2);
        success = false;
        return success;
    }

    getline(&fileNameBuff, &buffsize, stdin);
    fileNameBuff[strcspn(fileNameBuff, "\n")] = '\0';

    if(!(fp = fopen(fileNameBuff, "w+"))){
        printf("Error in creating file!");
        free(fileNameBuff);
        sleep(2);
        success = false;
        return success;
    }

    free(fileNameBuff);

    printf("File is ready to be edited press '`' (backtick) to save and exit.\n\n");
    printf("\n*************************************\n");
    while((ch = getchar()) != '`'){
        fputc(ch, fp);
    }
    printf("\n*************************************\n");

    fclose(fp);

    printf("\n\nPress Enter To Continue\n");
    getchar();

    return success;
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