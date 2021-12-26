#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>

#include "../includes/colors.h"

#define CLEAR "\e[1;1H\e[2J"

#define CALCULATOR "1"
#define READFILE "2"
#define NEWFILE "3"
#define MESSAGEFRIENDS "4"
#define LAUNCHPROG "5"

#define CONFIG "!"
#define EXIT "@"
#define HELP "#"

bool mainMenu();
void calculator();
bool readFile();
bool newFile();
bool launchProg();
bool config();

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
    size_t buffsize = 2;

    while(success){
        printf(CLEAR);
        printf("Program For Grandma's, "GRE"Press One"RESET" of the "YEL"following numbers"RESET" and then "RED"Enter"RESET" to acess it.\n\n");
        printf(BACBLU"                                                "RESET"\n");
        printf("* Press 1 to acess a "RED"calculator"RESET"\n");
        printf("* Press 2 to "YEL"read a file "RESET"from a certain location\n");
        printf("* Press 3 to make a "GRE"new file "RESET"that contains text\n");
        printf("* Press 4 to"BLU" message your friends"RESET"(COMING SOON)\n");
        printf("* Press 5 to"MAG" launch a program"RESET"\n");
        printf(BACBLU"                                                "RESET);
        printf("\nPress ! to"RED" configure settings"RESET"\n");
        printf("Press @ to"YEL" exit the program"RESET"\n");
        printf("Press # for any"GRE" help you may need "RESET"with the program\n");
        printf(BACBLU"                                                "RESET);

        printf("\n\nEnter your choice...\n");

        if(!(choice = (char*)malloc(buffsize * sizeof(char)))){
            printf("An "RED"error eccoured while allocating memory for your choice string!"RESET"");
            success = false;    
        }

        getline(&choice, &buffsize, stdin);

        choice[strcspn(choice, "\n")] = '\0';       //removes any newlines from buffer

        printf("You entered "YEL"%s"RESET" is this correct? ", choice); printf(GRE"y"RESET"/"RED"n"RESET"\n");

        if(yesorno() == 0){
            printf("\n"BLU"Rerouting you to your choice"RESET""RED"."RESET""YEL"."RESET""GRE"."RESET"\n");
            sleep(1);

            if(strcmp(choice, CALCULATOR) == 0){
                calculator();
            }
            else if(strcmp(choice, READFILE) == 0){
                if(!readFile()){
                    printf("Error Eccoured while reading the file\n");
                    success = false;
                }
            }
            else if(strcmp(choice, NEWFILE) == 0){
                if(!newFile()){
                    printf("Error Eccoured while making a new file\n");
                    success = false;
                }
            }
            //else if(strcmp(choice, MESSAGEFRIENDS) == 0)
            else if(strcmp(choice, LAUNCHPROG) == 0){
                if(!launchProg()){
                    printf("Error Eccoured While running launchProg()!\n");
                    success = false;
                }
            }
            else if(strcmp(choice, CONFIG) == 0)
                config();
            else if(strcmp(choice, EXIT) == 0)
                exit(EXIT_SUCCESS);
            #if GNU==1
                else if(strcmp(choice, HELP) == 0)
                    system("xdg-open https://github.com/NateNoNameSOFT/ProgramForGrandmas");
            #elif WIN==1
                else if(strcmp(choice, HELP) == 0)
                    system("start https://github.com/NateNoNameSOFT/ProgramForGrandmas");
            #elif MAC==1
                else if(strcmp(choice, HELP) == 0)
                    system("open https://github.com/NateNoNameSOFT/ProgramForGrandmas");
            #endif
            else{
                printf("Incorrect Option!");
                sleep(2);
            }
            printf(CLEAR);
        }

        printf(CLEAR);
        free(choice);
        choice = NULL;
    }

    return success;
}

void calculator(){
    printf(CLEAR);
    printf("Enter a "BLU"mathmatical calculation"RESET" to be preformed... (value1 <"RED"+"RESET", "YEL"-"RESET", "GRE"*"RESET", "BLU"/"RESET"> value2)\n");

    char operator = '\0';
    float value1, value2;
    bool restart = false;

    while(!restart){
        scanf("%f %c %f", &value1, &operator, &value2);

        switch(operator){
            case '+':
            printf("\nAnswer is: "RED"%f"RESET"\n", value1 + value2);
            break;

            case '-':
            printf("\nAnswer is: "RED"%f"RESET"\n", value1 - value2);
            break;

            case '*':
            printf("\nAnswer is: "RED"%f"RESET"\n", value1 * value2);
            break;

            case '/':
            printf("\nAnswer is: "RED"%f"RESET"\n", value1 / value2);
            break;

            default:
            printf("The mathmatical operator you entered is invalid, would you like to retry?\n");
            if(yesorno() == 0)
                restart = true;
            else
                return;
            break;
        }
        break;
    }

    printf(BACBLU"                                                "RESET"\n");

    getchar();
    printf("Press "GRE"ENTER"RESET" to continue\n");
    getchar();

    return;
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
        success = false;
    }

    printf(GRE"YOUR FILES:"RESET"\n");
    printf("\n"RED"*************************************"RESET"\n");
    #if GNU==1 || MAC==1
        system("ls -l");
    #elif WIN==1
        system("dir");
    #endif
    printf("\n"RED"*************************************"RESET"\n\n");

    printf("Enter "GRE"a file"RESET" you would like to "RED"read"RESET" "MAG"(EX: /home/name/documents/text.txt)"RESET"\n");
    getline(&filePath, &buffsize, stdin);
    filePath[strcspn(filePath, "\n")] = '\0';

    if(!(fp = fopen(filePath, "r"))){
        printf("Error eccoured while opening the file!\nPossibly a non-existant file (path)\n");
        success = false;
    }

    free(filePath);

    if(!(fileLineBuff = (char*)malloc(buffsize * sizeof(char)))){
        printf("Error eccoured while allocating memory for the file line buffer\n");
        success = false;
    }

    if(success == true){
        printf("\n"RED"*************************************"RESET"\n");

        while(!feof(fp)){
            getline(&fileLineBuff, &buffsize, fp);
            printf("%s", fileLineBuff);
        }

        printf("\n"RED"*************************************"RESET"\n");
        fclose(fp);
    }

    free(fileLineBuff);

    printf("\nPress "GRE"ENTER"RESET" to continue\n");
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
    printf("What would you like to "GRE"name to new file?"RESET"\n");

    if(!(fileNameBuff = (char*)malloc(buffsize * sizeof(char)))){
        printf("Error while allocating memory for the file name buffer!\n");
        success = false;
    }

    getline(&fileNameBuff, &buffsize, stdin);
    fileNameBuff[strcspn(fileNameBuff, "\n")] = '\0';

    if(!(fp = fopen(fileNameBuff, "w+"))){
        printf("Error in creating file!\n");
        success = false;
    }

    free(fileNameBuff);

    if(success == true){
        printf("File is ready to be edited "CYA"press '`' (backtick)"RESET" to "GRE"save"RESET" and "RED"exit"RESET".\n\n");
        printf("\n"RED"*************************************"RESET"\n");
        while((ch = getchar()) != '`'){
            fputc(ch, fp);
        }
        printf("\n"RED"*************************************"RESET"\n");
        
        fclose(fp);
        getchar();
    }

    printf("\nPress "GRE"ENTER"RESET" to continue\n");
    getchar();

    return success;
}

bool launchProg(){
    bool success = true;
    char *progNameBuff = NULL;
    size_t buffsize = 255;

    printf(CLEAR);
    printf("Which "GRE"Program would you like to launch"RESET" "BLU"(Programs listed are what you have installed)"RESET"\n");
    sleep(2);
    printf("\n"RED"*************************************"RESET"\n");
    #if GNU==1 || MAC==1
        system("apt list --installed");
    #elif WIN==1
        system("wmic");
    #endif
    printf("\n"RED"*************************************"RESET"\n");

    printf("Witch "GRE"Program"RESET" would you like to "GRE"launch?"RESET" "MAG"(it may take awhile to launch)"RESET"\n");
    
    if(!(progNameBuff = (char*)malloc(buffsize * sizeof(char)))){
        printf("Error while allocating memory for the prog name buffer!\n");
        success = false;
    }

    getline(&progNameBuff, &buffsize, stdin);
    progNameBuff[strcspn(progNameBuff, "\n")] = '\0';
    
    system(progNameBuff);

    printf("Done!");

    return success;
}

bool config(){
    bool success = true;
    char *choice = NULL;
    size_t buffsize = 2;

    printf("What would you like to configure?\n\n");

    printf("Press 1 to edit the theme\n");

    if(strcmp(choice, "1") == 0){
        printf("Which theme world you like?\n\n");

        printf("Press 1 for white");
        printf("Press 2 for default black");
    }
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