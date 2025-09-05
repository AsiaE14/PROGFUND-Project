#include<stdio.h>



void regis(){
printf("InProcess\n");
}
void Sall(){
printf("InProcess\n");
}
void search(){

    printf("InProcess\n");
     /*printf("if else : 1   switch case : 2\n");
        scanf("%d",&csa);
          switch (csa)
       {
       case 1:
        grade();
        break;
        
        case 2:
        printf("\nin progess");
        break;
       
       default:
        break;

       }
       
       
       */ 


        

}
int main(){
   int csa,caser,running =1 ;



    FILE *data = fopen("data.csv", "w");
    if (data == NULL) {
        printf("Error: Could not open file.\n");
        return 1;
    }

    // Write data to the CSV file
    fprintf(data, "Name,Start,End,Status\n");  // Header row
    fprintf(data, "A,05/21//23,04/29/24,Done\n");
    fprintf(data, "B,07/02//24,07/21/26,InProcess\n");
    fprintf(data, "C,05/21//23,07/21/23,Done\n");

    // Close the file
    fclose(data);

    printf("CSV file created successfully!\n ");
    return 0;
//menu//
/*     printf("+++++++++++++++++WelcomeTo-ProjectManagementInformationSystem++++++++++++++++++++++++++++\n");
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
   

*/


    return 0;

}