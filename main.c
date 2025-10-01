#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_RECORDS 1000
#define PAGE_SIZE 15
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




/*====================================== KEY= Add/Register=====================================================*/

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
     printf("('exit' or 'q' to cancel)\n");
    printf("Project-Name: ");


  
       
     if (!fgets(name, sizeof(name), stdin)) continue;
    name[strcspn(name, "\n")] = '\0'; // ลบ newline

     if (strcmp(name, "q") == 0 || strcmp(name, "exit") == 0) {
        printf(" Cancel registration. Back to menu.\n");
        return;  
    }
  
  
    if (strlen(name) == 0) {
        printf("ERROR! Project-Name cannot be empty. Please try again.\n");
        continue;
    }

     
       
    
    break;
}

while (1) {
         printf("('exit' or 'q' to cancel)\n");
        printf("Start-Date (YYYY-MM-DD): ");
       
         if (!fgets(start, sizeof(start), stdin)) continue;
    start[strcspn(start, "\n")] = '\0';

     if (strcmp(start, "q") == 0 || strcmp(start, "exit") == 0) {
            printf(" Cancel registration. Back to menu.\n");
            return;  
        }else if (!is_valid_date(start) ) {
    printf(" Invalid format! Please try again.\n");
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
     printf("('exit' or 'q' to cancel)\n");
        printf("End-Date (YYYY-MM-DD): ");
      if (!fgets(end, sizeof(end), stdin)) continue;
    end[strcspn(end, "\n")] = '\0';

     if (strcmp(start, "q") == 0 || strcmp(start, "exit") == 0) {
            printf(" Cancel registration. Back to menu.\n");
            return;  
        }else if (!is_valid_date(end)) {
    printf(" Invalid format! Please try again.\n");
      continue;
   
}       

 char year_str[5];
    strncpy(year_str, end, 4);
    year_str[4] = '\0';
    int year = atoi(year_str);
     if (year > 2037) {
        printf("ERROR ! Year must be <= 2037.\n");
        continue;
    }
    
   
    

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
/*====================================== KEY= Search=====================================================*/
//edit space in csv
void trim_newline(char *s) {
    size_t n = strlen(s);
    while (n > 0 && (s[n-1] == '\n' || s[n-1] == '\r')) {
        s[--n] = '\0';
    }
}

void rewrite_csv(char *records[], int count) {
    FILE *f = fopen("data.csv", "w");
    if (!f) { perror("fopen"); return; }
    fputs("ProjectName,StartDate,EndDate,Status\n", f);
    for (int i = 0; i < count; i++) {
        fprintf(f, "%s\n", records[i]);
    }
    fclose(f);
}

void edit_record(char *line) {
    char copy[MAX_LINE_LENGTH];
    strcpy(copy, line);

    char *n = strtok(copy, ",");
    char *s = strtok(NULL, ",");
    char *e = strtok(NULL, ",");
    char *st = strtok(NULL, ",");

    char newName[100], newStart[20], newEnd[20];

    printf("Edit Project (press Enter to keep old value)\n");

    printf("Name [%s]: ", n);
    if (fgets(newName, sizeof(newName), stdin)) {
        if (newName[0] != '\n') {
            newName[strcspn(newName, "\n")] = '\0';
            n = newName;
        }
    }

    printf("StartDate [%s]: ", s);
    if (fgets(newStart, sizeof(newStart), stdin)) {
        if (newStart[0] != '\n') {
            newStart[strcspn(newStart, "\n")] = '\0';
            s = newStart;
        }
    }

    printf("EndDate [%s]: ", e);
    if (fgets(newEnd, sizeof(newEnd), stdin)) {
        if (newEnd[0] != '\n') {
            newEnd[strcspn(newEnd, "\n")] = '\0';
            e = newEnd;
        }
    }

    const char *status = auto_status(s, e);
    snprintf(line, MAX_LINE_LENGTH, "%s,%s,%s,%s", n, s, e, status);
}

void search() {
    char query[100];
    printf("Enter Project-Name to search: ");
    if (!fgets(query, sizeof(query), stdin)) return;
    query[strcspn(query, "\n")] = '\0';

    FILE *file = fopen("data.csv", "r");
    if (!file) { perror("fopen"); return; }

    char *records[MAX_RECORDS];
    char buf[MAX_LINE_LENGTH];
    int count = 0;

    fgets(buf, sizeof(buf), file); // skip header
    while (fgets(buf, sizeof(buf), file)) {
        buf[strcspn(buf, "\n")] = '\0';
        records[count++] = strdup(buf);
    }
    fclose(file);

    int foundIndex = -1;
    for (int i = 0; i < count; i++) {
        char copy[MAX_LINE_LENGTH];
        strcpy(copy, records[i]);
        char *n = strtok(copy, ",");
        if (n && strstr(n, query)) {
            printf("%d) %s\n", i+1, records[i]);
            foundIndex = i;
        }
    }

    if (foundIndex == -1) {
        printf("No record found!\n");
        return;
    }

    printf("Choose action: 1=Edit, 2=Delete, 0=Cancel: ");
    int opt; scanf("%d", &opt); getchar();

    if (opt == 1) {
        edit_record(records[foundIndex]);
        rewrite_csv(records, count);
        printf("Record updated!\n");
    } else if (opt == 2) {
        for (int i = foundIndex; i < count-1; i++) {
            records[i] = records[i+1];
        }
        count--;
        rewrite_csv(records, count);
        printf("Record deleted!\n");
    } else {
        printf("Canceled.\n");
    }

    for (int i = 0; i < count; i++) free(records[i]);
}





/*====================================== KEY= Sort and Show=====================================================*/




// edit date to int easy to sort
int date_to_int(const char *date) {
    // แปลง YYYY-MM-DD → YYYYMMDD (int) ใช้สำหรับเปรียบเทียบ
    char buf[9];
    strncpy(buf, date, 4);   // year
    strncpy(buf+4, date+5, 2); // month
    strncpy(buf+6, date+8, 2); // day
    buf[8] = '\0';
    return atoi(buf);
}

// === Sorting compare functions ===
int cmp_name(const void *a, const void *b) {
    char *lineA = *(char **)a;
    char *lineB = *(char **)b;
    char copyA[MAX_LINE_LENGTH], copyB[MAX_LINE_LENGTH];
    strcpy(copyA, lineA); strcpy(copyB, lineB);

     char *nA = strtok(copyA, ",");
    char *nB = strtok(copyB, ",");
    return strcmp(nA, nB);
}



int cmp_start(const void *a, const void *b) {
    char *lineA = *(char **)a;
    char *lineB = *(char **)b;
    char copyA[MAX_LINE_LENGTH], copyB[MAX_LINE_LENGTH];
    strcpy(copyA, lineA); strcpy(copyB, lineB);

    strtok(copyA, ","); // name
    char *sA = strtok(NULL, ",");
    strtok(copyB, ",");
    char *sB = strtok(NULL, ",");

    return date_to_int(sA) - date_to_int(sB);
}



int cmp_end(const void *a, const void *b) {
    char *lineA = *(char **)a;
    char *lineB = *(char **)b;
    char copyA[MAX_LINE_LENGTH], copyB[MAX_LINE_LENGTH];
    strcpy(copyA, lineA); strcpy(copyB, lineB);

    strtok(copyA, ","); strtok(NULL, ",");
    char *eA = strtok(NULL, ",");
    strtok(copyB, ","); strtok(NULL, ",");
    char *eB = strtok(NULL, ",");

    return date_to_int(eA) - date_to_int(eB);
}

int cmp_status(const void *a, const void *b) {
    // เรียง Completed < In Progress < Not Started
    char *lineA = *(char **)a;
    char *lineB = *(char **)b;
    char copyA[MAX_LINE_LENGTH], copyB[MAX_LINE_LENGTH];
    strcpy(copyA, lineA); strcpy(copyB, lineB);

    strtok(copyA, ","); char *sA = strtok(NULL, ","); char *eA = strtok(NULL, ",");
    strtok(copyB, ","); char *sB = strtok(NULL, ","); char *eB = strtok(NULL, ",");

    const char *statA = auto_status(sA, eA);
    const char *statB = auto_status(sB, eB);

    int valA = (strcmp(statA, "Completed")==0 ? 1 : strcmp(statA, "In Progress")==0 ? 2 : 3);
    int valB = (strcmp(statB, "Completed")==0 ? 1 : strcmp(statB, "In Progress")==0 ? 2 : 3);

    return valA - valB;
}



void Sall(){


      int is_header = 1;
    char *records[MAX_RECORDS];
   char buf[MAX_LINE_LENGTH];
    int count = 0;

    
    if (ensure_csv_with_header("data.csv") != 0) {
        printf("Error: cannot create data.csv\n");
        return;
    }
    

    FILE *file = fopen("data.csv", "r");
    if (!file) { perror("fopen"); return; }

    
  


 
    fgets(buf, sizeof(buf), file); // skip header
    while (fgets(buf, sizeof(buf), file)) {
        records[count] = strdup(buf);
        count++;
    }
    fclose(file);

     ////////////////////////////////////////////

      if (count == 0) {
        printf("No records found.\n");
        return;
    }

    // เลือกวิธี sort
    printf("Sort by: (1=Name, 2=StartDate, 3=EndDate, 4=Status): ");
    int opt = 1;
    scanf("%d", &opt);
    getchar(); // clear enter

    if (opt == 1) qsort(records, count, sizeof(char *), cmp_name);
    else if (opt == 2) qsort(records, count, sizeof(char *), cmp_start);
    else if (opt == 3) qsort(records, count, sizeof(char *), cmp_end);
    else if (opt == 4) qsort(records, count, sizeof(char *), cmp_status);

    // แบ่งหน้า
    int page = 0;
    int totalPages = (count + PAGE_SIZE - 1) / PAGE_SIZE;
    

    while (1) {
        printf("\n================ PROJECT LIST (Page %d/%d) =================\n", page+1, totalPages);
        printf("   %-4s | %-30s | %-10s | %-10s | %-12s\n", "No.", "ProjectName", "StartDate", "EndDate", "Status");
        printf("----------------------------------------------------------------------\n");

        int start = page * PAGE_SIZE;
        int end = start + PAGE_SIZE;
        if (end > count) end = count;

        for (int i = start; i < end; i++) {
            char line[MAX_LINE_LENGTH];
            strcpy(line, records[i]);
            trim_newline(line);

            char *n = strtok(line, ",");
            char *s = strtok(NULL, ",");
            char *e = strtok(NULL, ",");
            if (n && s && e) {
                const char *real_status = auto_status(s, e);
                printf("   %-4d | %-30s | %-10s | %-10s | %-12s\n",i+1, n, s, e, real_status);
            }
        }

        printf("=====================================================================\n");
        printf("Options: [1=Prev, 2=Next, 0=Exit]: ");
        int cmd;
        scanf("%d", &cmd);
        getchar();

        if (cmd == 2 && page < totalPages-1) page++;
        else if (cmd == 1 && page > 0) page--;
        else if (cmd == 0) break;
    }

    // cleanup
    for (int i = 0; i < count; i++) free(records[i]);
}



  





/*====================================== KEY= MAIN=====================================================*/

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
        printf("_________OPTIONS___________\nRegister-New-Project : 1\nSearch-And-Edit/Delete-Project : 2\nShow-all-Projects : 3\nOthers: 4\n Exit : 0\n_________OPTIONS___________\nEnter-your-Options: ");
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