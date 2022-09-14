#include<stdio.h>
#include<string.h>

struct fileComp{

    char fileName[20];
    char members[10][20];
    char passcode[10][20];
    int top;
    char changesMade[10][30];
    char changesMaker[10][20];
}file;


int main()
{
    FILE* f1;
    int i = 0;
    int choice;
    int control = 1;
    int count = 0;
    int checker;
    int repeat = 0;
    int size;
    char ch;
    file.top = 0;
   
    while(1)
    {
    printf("What do you want to perform: \n");
    printf("--> 1. Create File \n");
    printf("--> 2. Edit File \n");
    printf("--> 3. Changes Made to the File \n");
    printf("--> 4. Exit \n");

    scanf("%d", &choice);
    getchar();
    if(choice == 4)
        break;

    switch(choice)
    {
        case 1:
            printf("Enter the name of the file (With Extension): ");
            fgets(file.fileName,sizeof(file.fileName),stdin);
            file.fileName[strlen(file.fileName)-1] = '\0';
            printf("\n");

            printf("Creating Your Project......\n\n");
            printf("Project Created!\n\n");

            printf("Now enter the Account name of the members who can access this project: \n");
            
            while(control)
            {
                printf("Enter the Account name: ");
                fgets(file.members[i],sizeof(file.members),stdin);
                file.members[i][strlen(file.members[i])-1] = '\0';

                printf("Enter their passcode: ");
                fgets(file.passcode[i], sizeof(file.passcode),stdin);

                printf("\n");
                printf("Are there any other members? Yes(1) or No(0): ");
                scanf("%d", &control);
                getchar();
                i++;
                count++;                
            }
            
            
            f1 =fopen(file.fileName, "a+");
            break;
        case 2:
        {   
            repeat = 0;
            char name[20];
            char password[20];

            printf("Enter Your Account Name: ");
            fgets(name, sizeof(name), stdin);
            name[strlen(name)-1] = '\0';

            printf("Enter Your Passcode: ");
            fgets(password,sizeof(password),stdin);
            for(int i =0 ; i<count;i++)
            {
                if(strcmp(file.members[i], name)==0)
                {   
                    
                    checker = i;
                    repeat = 0;
                    break;
                }
                else
                    repeat = 1;
            }
               

            if(repeat == 1)
            {
                printf("This account has not been linked!\n\n");
                continue;
            }
            

            printf("\n");
            if(strcmp(file.passcode[checker], password)== 0)
            {   
                printf("Verifying your Account link status.....\n\n");
                printf("Veification complete.\n\n");

                strcpy(file.changesMaker[file.top],name); 

                if(f1 != NULL)
                {
                    fseek(f1 , 0 , SEEK_END);
                    size = ftell(f1);
                    if(size!=0)
                    {   
                        fseek(f1 , 0 , SEEK_SET);
                        printf("The contents of the file are as follows: \n");
                        while((ch = fgetc(f1)) != EOF)
                        {
                            printf("%c", ch);
                        } 
                        
                    }

                }
                control = 1;
                while(control)
                {   
                    
                    printf("Write your changes: \n");
                    fgets(file.changesMade[file.top],sizeof(file.changesMade),stdin);
                    fprintf(f1, "%s",file.changesMade[file.top]);

                    file.top++;

                    printf("Do you want to make any further changes? Yes(1) or No(0)");
                    scanf("%d", &control);
                    getchar();
                    if(control == 1)
                        strcpy(file.changesMaker[file.top],name);

                }
            }
            else
            {   
                printf("You have entered incorrect Passcode!\n");
                continue;
            }
            
            break;
        }

        case 3:
            
            printf("Following are the changes made recently: \n");
            for (int i = file.top-1; i>= 0; i--)
            {
                printf("%-10s added --> %s \n",file.changesMaker[i],file.changesMade[i]);
            }
            break;             
    }
    
    }
}


