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
}





//time sys

time_t make_time(const char *dateStr) {
    int y, m, d;
    struct tm t = {0};
    if (sscanf(dateStr, "%d-%d-%d", &y, &m, &d) == 3) {
        t.tm_year = y - 1900;
        t.tm_mon  = m - 1;
        t.tm_mday = d;
        return mktime(&t);
    }
    return (time_t)-1;
}



// คำนวณสถานะอัตโนมัติ
const char* auto_status(const char *start, const char *end) {
    time_t now = time(NULL);
    struct tm *today = localtime(&now);

    char todayStr[11];
    snprintf(todayStr, sizeof(todayStr), "%04d-%02d-%02d",
             today->tm_year + 1900, today->tm_mon + 1, today->tm_mday);

    time_t tStart = make_time(start);
    time_t tEnd   = make_time(end);
    time_t tToday = make_time(todayStr);

  // ถ้า parse ไม่ได้เลย → Unknown
    if (tStart == (time_t)-1 || tEnd == (time_t)-1) {
        return "Error";
    }

    if (difftime(tToday, tStart) < 0) return "Not Started";
    else if (difftime(tToday, tEnd) > 0) return "Completed";
   
    

    else return "In Progress";
}



//ตรวจ input Date 
int is_valid_date(const char *date) {
    if (strlen(date) != 10) return 0;  //  10 ตัวอักษร

    if (date[4] != '-' || date[7] != '-') return 0;  //  4,7เป็น '-' จาก 0

    char y[5], m[3], d[3];
    strncpy(y, date, 4); y[4] = '\0';  //4ตัวแรก year  นับจาก 1
    strncpy(m, date+5, 2); m[2] = '\0'; //ตำแหน่งหลัง 5 month  นับจาก 1
    strncpy(d, date+8, 2); d[2] = '\0';//ตำแห่งหลัง 8 day  นับจาก 1

    if (!check_num(y) || !check_num(m) || !check_num(d)) return 0;  //ตรวจเลข

    int year = atoi(y), month = atoi(m), day = atoi(d); //แปลงตัวเลข ในกรณีเลขหลักเดียว ex 04 -> 4

    if (year < 1900 || year > 9999) return 0; //กำหนด ymd ที่ควรใส่
    if (month < 1 || month > 12) return 0;
    if (day < 1 || day > 31) return 0;

    // ตรวจสอบจำนวนวันในเดือนคร่าวๆ
    int days_in_month[] = {31,28,31,30,31,30,31,31,30,31,30,31};
    if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) //เงื่อนไขleap year
        days_in_month[1] = 29; // leap year

    if (day > days_in_month[month-1]) return 0;

    return 1;
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
   


while (1) {
    printf("Project-Name: ");
    if (!fgets(name, sizeof(name), stdin)) continue;
    name[strcspn(name, "\n")] = '\0'; // ลบ newline
    if (strlen(name) == 0) {
        printf("❌ Project-Name cannot be empty. Please try again.\n");
        continue;
    }
    
    break;
}

while (1) {
        printf("Start-Date (YYYY-MM-DD): ");
       
         if (!fgets(start, sizeof(start), stdin)) continue;
    start[strcspn(start, "\n")] = '\0';

        if (!is_valid_date(start) ) {
    printf("❌ Invalid format! Please try again.\n");
      continue;
        }

           char year_str[5];
    strncpy(year_str, start, 4);
    year_str[4] = '\0';
    int year = atoi(year_str);

    if (year < 1975) {
        printf("ERROR ! Year must be >= 1975.\n");
        continue;
    }
   
          break;
}
 while (1) {
        printf("End-Date (YYYY-MM-DD): ");
      if (!fgets(end, sizeof(end), stdin)) continue;
    end[strcspn(end, "\n")] = '\0';
       if (!is_valid_date(end)) {
    printf("❌ Invalid format! Please try again.\n");
      continue;
   
} 

 char year_str[5];
    strncpy(year_str, end, 4);
    year_str[4] = '\0';
    int year = atoi(year_str);
    
   
    

    time_t tStart = make_time(start);
    time_t tEnd   = make_time(end);
    if (difftime(tEnd, tStart) < 0) {
        printf(" End-Date must be after Start-Date! Please try again.\n");
        continue;
    }

    
    break; // ผ่านแล้ว
  
}



         const char *status = auto_status(start, end);// func คำนวณวัน



  fprintf(data, "%s,%s,%s,%s\n", name, start, end,status);
    fclose(data);
    printf("Information edited successfully with status: %s\n",status);


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
    printf("   %-30s | %-10s | %-10s | %-12s\n", "ProjectName", "StartDate", "EndDate", "Status");
    printf("----------------------------------------------------------------------\n");



    
  

    while (fgets(line, sizeof(line), file)) {
        trim_newline(line);
         if (is_header) { is_header = 0; continue; }

    
        
        char *n    = strtok(line, ",");
        char *s    = strtok(NULL, ",");
        char *e    = strtok(NULL, ",");
       // char *stat = strtok(NULL, ",");//



        if (n && s && e ) {
            const char *real_status = auto_status(s, e);  //ประกาศและเรียกfunc auto_status
            printf("   %-30s | %-10s | %-10s | %-12s\n", n, s, e, real_status);
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
       char buf[10];
        if (fgets(buf, sizeof(buf), stdin)) {
        if (sscanf(buf, "%d", &caser) != 1) {
        printf(" Invalid option! Try again.\n");
        continue;
    }
}

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