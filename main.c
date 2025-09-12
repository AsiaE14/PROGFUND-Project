#include<stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 1024
#define DELIMITER ","

void boom(){
     FILE *data = fopen("data.csv", "w");
      fclose(data);
    printf("All data deleted!");

}

char regis(){

    FILE *data = fopen("data.csv", "a");
char name[100];    
char start[100];
char end[100];    
char pocess[100];    


 printf("Project-Name: ");
    scanf("%s", name);
    printf("Start-Date: ");
    scanf("%s", start);
    printf("End-Date: ");
    scanf("%s", end);
    printf("Status: ");
    scanf("%s", pocess);
   

// data = fopen ("data.csv", "a");
    fprintf(data, "%s, %s, %s, %s\n",name,start,end,pocess); //I think there's something wrong here too...

    fclose(data);
    printf("Information edited successfully");


}

int Sall(){

FILE *file = fopen("data.csv", "r"); // Open the CSV file in read mode
    if (file == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    
    char line[1024]; // Buffer to store each line
    while (fgets(line, sizeof(line), file)) { // Read each line
        char *token = strtok(line, ","); // Split the line by commas
        while (token) {
            printf("%s ", token); // Print each value
            token = strtok(NULL, ",");
        }
        printf("\n");
    }

    fclose(file); // Close the file
    return EXIT_SUCCESS;


    
}



//search.....

void search(){
    
   

   

    printf("inpro\n");
   

}



// MAIN
int main(){
   int csa,caser,running =1 ;
    const char *input_file = "data.csv";
    const char *output_file = "data.csv";
    int column_to_edit = 1; // Column index to edit (0-based)
    const char *new_value = "UpdatedValue";



    FILE *data = fopen("data.csv", "w");
    if (data == NULL) {
        printf("Error: Could not open file.\n");
        return 1;
    }

    int ch;
    char line[100];
    while (fgets(line,sizeof(line),data)!=NULL){
        printf("test\n");
        printf("a%s",line);    }
    {
        /* code */
    }
    

    // Write data to the CSV file
   
   

    // Close the file


  
    
//menu//
     printf("+++++++++++++++++WelcomeTo-ProjectManagementInformationSystem++++++++++++++++++++++++++++\n");
   while (running)

    {
           printf("_________OPTIONS___________\nRegister-New-Project : 1\nSearch-and-Edit-Projects : 2\nShow-all-Projects : 3\nOthers: 4\n Exit : 0\n_________OPTIONS___________\nEnter-your-Options: ");
   
    
            
    
   scanf("%d",&caser);
    
  
    
    switch (caser)
    {
   
    case 1:
        regis();
        printf("\n");
        break;
        
    case 2:
       search();
        printf("\n");
        break;
       
        
    case 3:
         Sall();
          printf("\n");
         break;
        
    case 4:
        printf("InProcess\n");
         printf("\n");
       
        break;
        
    case 0:

        running =0;
        break;
    default:
        printf("Try-Again!!\n");
        break;
        
    }
 }
    
      printf("Exit-Program");
   



    return 0;

}