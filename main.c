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
//head//
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