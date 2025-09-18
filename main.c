#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


#define MAX_LINE_LENGTH 1024
#define DELIMITER ","

//check.csv file
int ensure_csv_with_header(const char *path) {
    FILE *f = fopen(path, "r");
    if (f) { fclose(f); return 0; }      // มีไฟล์อยู่แล้ว
    f = fopen(path, "w");
    if (!f) return -1;
    fputs("ProjectName,StartDate,EndDate,Status\n", f);  // header
    fclose(f);
    return 0;
}

int check_num(const char *s){

     if (*s == '\0') return 0;       // ว่างเปล่า ไม่ใช่เลข
    while (*s) {
        if (*s < '0' || *s > '9') return 0;
        s++;
    }
    return 1;

}

void pause(){
     getchar();
     getchar();
}




//register
void regis(){

    if (ensure_csv_with_header("data.csv") != 0) {
    printf("Error\n");
    return;
    }

    FILE *data = fopen("data.csv", "a");
     if (!data) { perror("fopen"); return; }
char name[100];    
char start[100];
char end[100];    
char process[100];    


 printf("Project-Name: ");
    scanf("%s", name);
    printf("Start-Date(YYYY-MM-DD): ");
    scanf("%s", start);
    printf("End-Date(YYYY-MM-DD): ");
    scanf("%s", end);
      printf("Status: ");
    scanf("%s", end);


   

  fprintf(data, "%s,%s,%s, %s\n", name, start, end, process);
    fclose(data);
    printf("Information edited successfully");


}




//short and show 
void trim_newline(char *s) {
    size_t n = strlen(s);
    while (n > 0 && (s[n-1] == '\n' || s[n-1] == '\r')) {
        s[--n] = '\0';
    }
}

void Sall(){

    
    if (ensure_csv_with_header("data.csv") != 0) {
        printf("Error: cannot create data.csv\n");
        return;
    }

    FILE *file = fopen("data.csv", "r");
    if (!file) { perror("fopen"); return; }

    char line[MAX_LINE_LENGTH];
    int is_header = 1;

    printf("\n============================= USER LIST =============================\n");
  

    while (fgets(line, sizeof(line), file)) {
        trim_newline(line);

    
        
        char *n    = strtok(line, ",");
        char *s    = strtok(NULL, ",");
        char *e    = strtok(NULL, ",");
        char *stat = strtok(NULL, ",");

        if (n && s && e && stat) {
            printf("%-30s | %-10s | %-10s | %-12s\n", n, s, e, stat);
        }
    }

    printf("=====================================================================\n");
    
    fclose(file);



  
}


    




//search.....

void search(){
    
   

   

    printf("inpro\n");
   

}



// MAIN
int main()
{
  
    int csa,caser,running =1 ;
   
  
    
        //menu//
    
  
    if (ensure_csv_with_header("data.csv") != 0) {
  
            printf("Error: cannot init CSV\n");
   
            return 1;
    }
   
   
    while (running)
    {

        printf("+++++++++++++++++WelcomeTo-ProjectManagementInformationSystem++++++++++++++++++++++++++++\n");
        printf("_________OPTIONS___________\nRegister-New-Project : 1\nSearch-and-Edit-Projects : 2\nShow-all-Projects : 3\nOthers: 4\n Exit : 0\n_________OPTIONS___________\nEnter-your-Options: ");
        scanf("%d",&caser);
         switch (caser)
         {
             case 1:
            regis();
            printf("\n");
            pause();
            break;

             case 2:
            search();
            printf("\n");
            pause();
            break;

            case 3:
            Sall();
            printf("\n");
            pause();
            break;
         
            case 4:
            printf("InProcess\n");
            printf("\n");
            pause();
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