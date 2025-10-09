#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

#ifndef DATA_FILE
#define DATA_FILE "data.csv"
#endif


#define MAX_RECORDS 1000
#define PAGE_SIZE 15
#define MAX_LINE_LENGTH 1024
#define DELIMITER ","

const char *GR = "\x1b[90m";  
 const char *R   = "\x1b[31m";
 const char *BR   = "\x1b[91m";
    const char *G = "\x1b[32m";
    const char *Y= "\x1b[33m";
    const char *B  = "\x1b[34m";
    const char *C  = "\x1b[36m";
    const char *RESET = "\x1b[0m";
    const char *BOLD  = "\x1b[1m";

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

// ตรวจสอบชื่อโปรเจ็กต์ว่าปลอดภัยและอยู่ในรูปแบบที่ถูกต้อง
int is_valid_name(const char *name) {
    if (name == NULL || strlen(name) == 0) {
        printf("ERROR: Project name cannot be empty.\n");
        return 0;
    }

    if (strlen(name) < 3) {
        printf("%sERROR: Project name must be at least 3 characters.%s\n",R,RESET);
        return 0;
    }

    // ห้ามมีเครื่องหมายที่อาจทำให้ CSV เสีย เช่น , หรือ "
    for (int i = 0; name[i] != '\0'; i++) {
        if (name[i] == ',' || name[i] == '"' || name[i] == ';' || name[i] == '|') {
            printf("%sERROR: Project name contains invalid characters (, \" ; | not allowed).%s\n",R,RESET);
            return 0;
        }
    }

    return 1; //  ผ่านทั้งหมด
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
    if (difftime(tEnd, tStart) < 0) return "Error";

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

    if (year < 1900 || year > 9000) return 0; //กำหนด ymd ที่ควรใส่ (เช็คอีกทีตอนinput)
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
    
 system("cls||clear");
  printf("\n");
printf("=====================================================================\n");
printf("                              %s%sREGISTER%s\n",BOLD,C,RESET);
printf("=====================================================================\n");
  printf("%s('exit' or 'q' to cancel)%s\n",GR,RESET);
    if (ensure_csv_with_header(DATA_FILE) != 0) {
    printf("%sError! No Data.csv%s\n",R,RESET);
    return;
    }

    FILE *data = fopen(DATA_FILE, "a");
     if (!data) { perror("fopen"); return; }
char name[100];    
char start[100];
char end[100];    
   


while (1) {
    
   
    printf("Project-Name: ");


  
       
     if (!fgets(name, sizeof(name), stdin)) continue;
    name[strcspn(name, "\n")] = '\0'; // ลบ newline


   
     if (strcmp(name, "q") == 0 || strcmp(name, "exit") == 0) {
        printf(" %sCancel registration. Back to menu.%s\n",BR,RESET);
        return;  
    }
     if (!is_valid_name(name)) {
    continue;
}

    
  
    if (strlen(name) == 0) {
        printf("%sERROR: Project-Name cannot be empty. Please try again.%S\n",R,RESET);
        continue;
    }

     
       
    
    break;
}

while (1) {
    
        
        printf("Start-Date (YYYY-MM-DD): ");
       
         if (!fgets(start, sizeof(start), stdin)) continue;
    start[strcspn(start, "\n")] = '\0';

     if (strcmp(start, "q") == 0 || strcmp(start, "exit") == 0) {
            printf(" %sCancel registration. Back to menu.\n%s",BR,RESET);
            return;  
        }else if (!is_valid_date(start) ) {
    printf(" %sInvalid format! Please try again.%s\n",R,RESET);
      continue;
        }

           char year_str[5];
    strncpy(year_str, start, 4);
    year_str[4] = '\0';
    int year = atoi(year_str);

    if (year < 1975) {
        printf("%sERROR: Year must be >= 1975.%s\n",R,RESET);
        continue;
    }
   
          break;
}
 while (1) {
     
    
        printf("End-Date (YYYY-MM-DD): ");
      if (!fgets(end, sizeof(end), stdin)) continue;
    end[strcspn(end, "\n")] = '\0';

     if (strcmp(start, "q") == 0 || strcmp(start, "exit") == 0) {
            printf(" %sCancel registration. Back to menu.%s\n",BR,RESET);
            return;  
        }else if (!is_valid_date(end)) {
    printf("%s Invalid format! Please try again.%s\n",R,RESET);
      continue;
   
}       

 char year_str[5];
    strncpy(year_str, end, 4);
    year_str[4] = '\0';
    int year = atoi(year_str);
     if (year > 2037) {
        printf("%sERROR:  Year must be <= 2037.%s\n",R,RESET);
        continue;
    }
    
   
    

    time_t tStart = make_time(start);
    time_t tEnd   = make_time(end);
    if (difftime(tEnd, tStart) < 0) {
        printf("%s End-Date must be after Start-Date! Please try again.%s\n",R,RESET);
        continue;
    }

    
    break; // ผ่านแล้ว
  
}




const char *status = auto_status(start, end);// func คำนวณวัน
 system("cls||clear");
  printf("\n");
printf("=====================================================================\n");
printf("                              %s%sREGISTER%s\n",BOLD,C,RESET);
printf("=====================================================================\n");  
printf("  %sProject Name   :%s %s\n",BOLD,RESET,name);
printf("  %sStart Date     :%s %s\n",BOLD,RESET,start);
printf("  %sEnd Date       :%s %s\n",BOLD,RESET,end);
printf("---------------------------------------------------------------------\n");
printf("%s[1]%s Confirm                                                 %s[2]%sCancel\n",Y,RESET,Y,RESET);
 printf("\nEnter your choice: ");


int a ;
scanf("%d",&a);
if(a == 1 ){
    fprintf(data, "%s,%s,%s,%s\n", name, start, end,status);
    fclose(data);
    printf("\n=====================================================================\n");
    printf("       %sInformation registered successfully with status:%s %s\n",G,status,RESET);
    printf("=====================================================================\n");
    pause();
}else{
    printf("\n=====================================================================\n");
    printf("                        %sRegistration  Canceled.%s\n",BR,RESET);
    printf("=====================================================================\n");
      printf(" \n");
       pause();

            return;  
}



  

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
    FILE *tmp = fopen("data_tmp.csv", "w");
    if (!tmp) { perror("temp open"); return; }

    fprintf(tmp, "ProjectName,StartDate,EndDate,Status\n");
    for (int i = 0; i < count; i++) {
        if (records[i] && strlen(records[i]) > 0)
            fprintf(tmp, "%s\n", records[i]);
    }
    fclose(tmp);

    // เขียนครบทุกบรรทัดแล้วเท่านั้นถึงแทนที่ไฟล์จริง
    remove(DATA_FILE);
    rename("data_tmp.csv", DATA_FILE);
}

char *edit_record(const char *oldRecord) {
    char copy[MAX_LINE_LENGTH];
    strcpy(copy, oldRecord);

    char *proj = strtok(copy, ",");
    char *start = strtok(NULL, ",");
    char *end = strtok(NULL, ",");
    // char *status = strtok(NULL, ",");

    printf("\nEditing Record:\n");
    printf("Current Project: %s\n", proj);

    char newProj[100], newStart[50], newEnd[50];
    const char *status;
    int valid = 0;

    // ====== Project Name ======
    while (1) {
        printf("Enter new Project %s[Enter to keep %s]%s: ",GR,proj,RESET);
        if (!fgets(newProj, sizeof(newProj), stdin)) continue;
        newProj[strcspn(newProj, "\n")] = '\0';

        if (strlen(newProj) == 0) strcpy(newProj, proj);

        if (!is_valid_name(newProj)) {
    continue;
}
        break;
    }

    // ====== Start Date ======
    while (1) {
        printf("Enter new StartDate %s(YYYY-MM-DD) %s[Enter to keep %s]%s: ",G,GR, start,RESET);
        if (!fgets(newStart, sizeof(newStart), stdin)) continue;
        newStart[strcspn(newStart, "\n")] = '\0';

        if (strlen(newStart) == 0) strcpy(newStart, start);

        if (!is_valid_date(newStart)) {
            printf("%sInvalid StartDate format! Must be YYYY-MM-DD.%s\n",R,RESET);
            continue;
        }

        char year_str[5];
        strncpy(year_str, newStart, 4);
        year_str[4] = '\0';
        int year = atoi(year_str);

        if (year < 1975) {
            printf("%sERROR: Year must be >= 1975.%s\n",R,RESET);
            continue;
        }

        break;
    }

    // ====== End Date ======
    while (1) {
        printf("Enter new EndDate %s(YYYY-MM-DD) %s[Enter to keep %s]%s: ",G,GR ,end,RESET);
        if (!fgets(newEnd, sizeof(newEnd), stdin)) continue;
        newEnd[strcspn(newEnd, "\n")] = '\0';

        if (strlen(newEnd) == 0) strcpy(newEnd, end);

        if (!is_valid_date(newEnd)) {
            printf("%sInvalid StartDate format! Must be YYYY-MM-DD.%s\n",R,RESET);
            continue;
        }

        char year_str[5];
        strncpy(year_str, newEnd, 4);
        year_str[4] = '\0';
        int year = atoi(year_str);
        if (year > 2037) {
            printf("%sERROR: Year must be <= 2037.%s\n",R,RESET);
            continue;
        }

        time_t tStart = make_time(newStart);
        time_t tEnd = make_time(newEnd);
        if (difftime(tEnd, tStart) < 0) {
            printf("%sERROR: EndDate must be after StartDate.%s\n",R,RESET);
            continue;
        }
        break;
    }

    // ====== Auto calculate status ======
    status = auto_status(newStart, newEnd);

    // ====== Combine updated record ======
    static char newRecord[MAX_LINE_LENGTH];
    snprintf(newRecord, sizeof(newRecord), "%s,%s,%s,%s", newProj, newStart, newEnd, status);

    printf("\n %sRecord successfully updated! with Status: %s%s\n", G,status,RESET);
    return newRecord;
}

void search() {
    char query[100];
    system("cls||clear");
    printf("\n");
    printf("=====================================================================\n");
    printf("                              %s%sSEARCH%s\n",BOLD,C,RESET);
    printf("=====================================================================\n");
    printf("Enter Project-Name to search %s[Enter = Show all]%s: ",GR,RESET);
    if (!fgets(query, sizeof(query), stdin)) return;
    query[strcspn(query, "\n")] = '\0'; // ลบ newline

    FILE *file = fopen(DATA_FILE, "r");
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

    int foundIndexes[MAX_RECORDS];
    int foundCount = 0;

    //  Normalize query → lowercase
    char queryLower[100];
    for (int j = 0; query[j] && j < sizeof(queryLower) - 1; j++)
        queryLower[j] = tolower((unsigned char)query[j]);
    queryLower[strlen(query)] = '\0';

    //  ค้นหา (case-insensitive) หรือแสดงทั้งหมดถ้า query ว่าง
    for (int i = 0; i < count; i++) {
        char copy[MAX_LINE_LENGTH];
        strcpy(copy, records[i]);
        char *n = strtok(copy, ",");
        if (!n) continue;

        if (strlen(queryLower) == 0) { // ถ้าไม่พิมพ์ query แสดงทุก record
            foundIndexes[foundCount++] = i;
            continue;
        }

        char nameLower[MAX_LINE_LENGTH];
        for (int j = 0; n[j] && j < MAX_LINE_LENGTH - 1; j++)
            nameLower[j] = tolower((unsigned char)n[j]);
        nameLower[strlen(n)] = '\0';

        if (strstr(nameLower, queryLower))
            foundIndexes[foundCount++] = i;
    }

    if (foundCount == 0) {
        printf("%sNo record found!%s\n", R, RESET);
        for (int i = 0; i < count; i++) free(records[i]);
        return;
    }

    int current = 0;
    char cmd[10];

    while (1) {
        system("cls||clear");
        printf("\n===============================================================================================\n");
        printf("                                    %sSEARCH RESULTS TABLE%s\n",C,RESET);
        printf("===============================================================================================\n");
        printf("  %s %-4s | %-30s | %-10s | %-10s | %-12s%s\n", C,"No.", "ProjectName", "StartDate", "EndDate", "Status",RESET);
        printf("-----------------------------------------------------------------------------------------------\n");

        for (int i = 0; i < foundCount; i++) {
            char copy[MAX_LINE_LENGTH];
            strcpy(copy, records[foundIndexes[i]]);
            char *proj = strtok(copy, ",");
            char *start = strtok(NULL, ",");
            char *end = strtok(NULL, ",");
            char *status = strtok(NULL, ",");

            if (!proj) continue;
            if (!start) start = "-";
            if (!end) end = "-";
            if (!status) status = "-";

            if (i == current)
                printf("%s->%s %s%-4d | %-30s | %-10s | %-10s | %-12s %s<- %s\n",
                       R,RESET,BOLD, i + 1, proj, start, end, status,R, RESET);
            else
                 printf("   %s%-4d %s| %-30s | %s%-10s | %s%-10s | %s%-12s \n%s",GR,i+1,RESET, proj, Y,start,BR, end, G,status,RESET);
               // printf("   %-4d | %-30s | %-10s | %-10s | %-12s\n",i+1, proj,start, end,status);
        }

        printf("===============================================================================================\n");
        printf("%s[1]%s Up  %s[2]%s Down  %s[3]%s Select  %s[0]%s Cancel\n",Y,RESET,Y,RESET,Y,RESET,Y,RESET);
        printf("Choose option: ");

        if (!fgets(cmd, sizeof(cmd), stdin)) continue;
        cmd[strcspn(cmd, "\n")] = '\0';

        if (strcmp(cmd, "1") == 0) {
            if (current > 0) current--;
        } else if (strcmp(cmd, "2") == 0) {
            if (current < foundCount - 1) current++;
        } else if (strcmp(cmd, "3") == 0) {
            break;
        } else if (strcmp(cmd, "0") == 0) {
            printf("Canceled.\n");
            for (int i = 0; i < count; i++) free(records[i]);
            return;
        } else {
            printf("Invalid input!\n");
        }
    }

    int targetIndex = foundIndexes[current];
    printf("\nYou selected: %s\n", records[targetIndex]);

    // เมนูเลือก
    char bufAct[10];
    int opt = -1;
    while (1) {
        printf("%s[1]%s Edit  %s[2]%s Delete   %s[0]%s Cancel\n",Y,RESET,Y,RESET,Y,RESET);
        printf("Choose option: ");
        if (!fgets(bufAct, sizeof(bufAct), stdin)) continue;
        bufAct[strcspn(bufAct, "\n")] = '\0';
        if (!check_num(bufAct)) {
            printf("%sInvalid input! Please enter 0, 1, or 2.%s\n",R,RESET);
            continue;
        }
        opt = atoi(bufAct);
        if (opt < 0 || opt > 2) {
            printf("%sTry again!%s\n",R,RESET);
            continue;
        }
        break;
    }

    if (opt == 1) {
        char *edited = edit_record(records[targetIndex]);
        if (edited == NULL) {
            printf("%sEdit canceled or invalid data. No changes made.%s\n",R,RESET);
        } else {
            free(records[targetIndex]);
            records[targetIndex] = strdup(edited);
            rewrite_csv(records, count);
            printf("%sRecord updated!%s\n",G,RESET);
        }
    } else if (opt == 2) {
        free(records[targetIndex]);
        for (int i = targetIndex; i < count - 1; i++) {
            records[i] = records[i + 1];
        }
        count--;
        rewrite_csv(records, count);
        printf("%sRecord deleted!%s\n",R,RESET);
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
    strcpy(copyA, lineA);
    strcpy(copyB, lineB);

    char *nA = strtok(copyA, ",");
    char *nB = strtok(copyB, ",");

    return strcasecmp(nA, nB); // เรียงโดยไม่แยก case
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
system("cls||clear");
printf("\n");
    printf("=====================================================================\n");
    printf("                            %s%sSHOW ALL%s\n",BOLD,C,RESET);
    printf("=====================================================================\n");

    

    
    if (ensure_csv_with_header(DATA_FILE) != 0) {
        printf("%sError: cannot create data.csv%s\n",R,RESET);
        return;
    }
    

    FILE *file = fopen(DATA_FILE, "r");
    if (!file) { perror("fopen"); return; }

    
  


 
    fgets(buf, sizeof(buf), file); // skip header
    while (fgets(buf, sizeof(buf), file)) {
        records[count] = strdup(buf);
        count++;
    }
    fclose(file);

     ////////////////////////////////////////////

      if (count == 0) {
        printf("%sNo records found!%s\n",R,RESET);
        return;
    }

    // เลือกวิธี sort
    printf("%sSort by: (1=Name, 2=StartDate, 3=EndDate, 4=Status, Other=.csv list ):%s ",Y,RESET);
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
         system("cls||clear");

        printf("\n================ %sPROJECT LIST (Page %d/%d)%s =================\n", Y,page+1, totalPages,RESET);
        printf("  %s %-4s | %-30s | %-10s | %-10s | %-12s%s\n",C, "No.", "ProjectName", "StartDate", "EndDate", "Status",RESET);
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
                printf("   %s%-4d %s| %-30s | %s%-10s | %s%-10s | %s%-12s \n%s",GR,i+1,RESET, n, Y,s,BR, e, G,real_status,RESET);
            }
        }

        printf("=====================================================================\n");
        printf("%sOptions: [1=Prev, 2=Next, 0=Exit]:%s ",Y,RESET);
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

/*====================================== KEY= UNIT_TEST=====================================================*/

void run_unit_tests() {

     system("cls||clear");
    printf("\nRunning UNIT TESTS...\n\n");
    system("test_unit.exe");   // บน Windows อาจต้องเป็น "test_unit.exe"
    
   /* system("cls||clear");
    printf("\n======================================================\n");
    printf("                    %s%sUNIT TESTS%s\n",BOLD,C,RESET);
    printf("======================================================\n");

    int pass = 0, fail = 0;

    // Test check_num
        printf("Test check_num(\"12345\")                     => %s%s\n", check_num("12345") ? ("%sPASS",G) : ("%sFAIL",R),RESET);
    pass += check_num("12345") ? 1 : 0;
    fail += !check_num("12345");

        printf("Test check_num(\"12a45\")                     => %s%s\n", check_num("12a45") ? ("%sPASS",G) : ("%sFAIL",R),RESET);
    pass += check_num("12a45") ? 1 : 0;
    fail += !check_num("12a45");

    // Test date validation
        printf("Test is_valid_date(\"2025-05-15\")            => %s%s\n", is_valid_date("2025-05-15") ? ("%sPASS",G) : ("%sFAIL",R),RESET);
    pass += is_valid_date("2025-05-15");
    fail += !is_valid_date("2025-05-15");

        printf("Test is_valid_date(\"2025-13-01\")            => %s%s\n", is_valid_date("2025-13-01") ? ("%sPASS",G) : ("%sFAIL",R),RESET);
    pass += is_valid_date("2025-13-01");
    fail += !is_valid_date("2025-13-01");
    
    // Test leap year validation
        printf("Test(leap Year) is_valid_date(\"2025-02-29\") => %s%s\n", is_valid_date("2025-02-29") ? ("%sPASS",G) : ("%sFAIL",R),RESET);
    pass += is_valid_date("2025-02-29");
    fail += !is_valid_date("2025-02-29");
   
        printf("Test(leap Year) is_valid_date(\"2024-02-29\") => %s%s\n", is_valid_date("2024-02-29") ? ("%sPASS",G) : ("%sFAIL",R),RESET);
    pass += is_valid_date("2024-02-29");
    fail += !is_valid_date("2024-02-29");

    // Test name validation
        printf("Test is_valid_name(\"ValidName\")             => %s%s\n", is_valid_name("ValidName") ? ("%sPASS",G) : ("%sFAIL",R),RESET);
    pass +=is_valid_name("ValidName");
    fail += !is_valid_name("ValidName");
        printf("Test is_valid_name(\"Invalid,Name\")          => %s%s\n", is_valid_name("Invalid,Name") ? ("%sPASS",G) : ("%sFAIL",R),RESET);
    pass += is_valid_name("Invalid,Name");
    fail += !is_valid_name("Invalid,Name");

    // Test auto_status
    printf("\n");
    printf("%sTest auto_status() logic check...%s\n",Y,RESET);
    const char *s1 = auto_status("2025-01-01", "2025-12-31");
        printf(" auto_status(2025-01-01,2025-12-31)          => %s%s%s\n", BOLD,s1,RESET);
    const char *s2 = auto_status("2000-01-01", "2005-12-31");
        printf(" auto_status(2000-01-01,2005-12-31)          => %s%s%s\n", BOLD,s2,RESET);
     const char *s3 = auto_status("2026-01-01", "2027-12-31");
        printf(" auto_status(2026-01-01,2027-12-31)          => %s%s%s\n", BOLD,s3,RESET);
     const char *s4 = auto_status("2000-01-01", "2027-12-31");
        printf(" auto_status(2000-01-01,2027-12-31)          => %s%s%s\n", BOLD,s4,RESET);
    

    printf("------------------------------------------------------\n");
    printf(" %sPASSED%s: %d |  %sFAILED%s: %d\n",G,RESET, pass,R,RESET, fail);
    printf("======================================================\n");
   */
}

/*====================================== KEY= E2E=====================================================*/
void run_e2e_test() {
    system("cls||clear");
    printf("\nRunning END-TO-END TESTS...\n\n");
    system("test_e2e.exe");   // หรือ "test_e2e.exe"
   /* system("cls||clear");
    printf("\n======================================================\n");
    printf("               %s%sEND-TO-END (E2E) TEST%s\n",BOLD,C,RESET);
    printf("======================================================\n");

    const char *testFile = "test_data.csv";
    remove(testFile);
    ensure_csv_with_header(testFile);

    FILE *f = fopen(testFile, "a");
    if (!f) { perror("fopen"); return; }

    fprintf(f, "Website,2025-01-01,2025-05-01,Completed\n");
    fprintf(f, "MobileApp,2025-06-01,2025-09-01,In Progress\n");
    fclose(f);

    printf("Inserted 2 test records into %s\n", testFile);

    // Simulate reading & sorting
    FILE *rf = fopen(testFile, "r");
    char buf[256];
    int lines = 0;
    fgets(buf, sizeof(buf), rf); // skip header
    while (fgets(buf, sizeof(buf), rf)) lines++;
    fclose(rf);

    if (lines == 2) {
        printf(" E2E PASS: 2 records inserted & read correctly.\n");
    } else {
        printf(" E2E FAIL: record count mismatch (got %d)\n", lines);
    }

    printf("------------------------------------------------------\n");
    printf("%sE2E test finished. test_data.csv remains for inspection.%s\n");
    printf("======================================================\n");
    pause();*/
}


/*====================================== KEY= MAIN=====================================================*/
#ifndef TEST_MODE
int main()
{
   
   


    int caser,running =1 ;
    if (ensure_csv_with_header(DATA_FILE) != 0) {
        printf("%sError:%s cannot init CSV\n", R, RESET);
        return 1;
    }

    while (running)
    {
        system("cls||clear");
        printf("\n");
        printf("=====================================================================\n");
        printf("         %s%s PROJECT MANAGEMENT INFORMATION SYSTEM %s\n", BOLD, C, RESET);
        printf("=====================================================================\n");
        printf("  %s[1]%s > %sRegister%s                  %s:Add New Project%s\n", Y, RESET, BOLD, RESET, G, RESET);
        printf("  %s[2]%s > %sSearch%s                    %s:Find / Edit / Delete Project%s\n", Y, RESET, BOLD, RESET, G, RESET);
        printf("  %s[3]%s > %sShow All%s                  %s:Display All Projects (Sortable)%s\n", Y, RESET, BOLD, RESET, G, RESET);
        printf("  %s[4]%s > %sUnits Test%s                %s:Test Each Important Functions%s\n", Y, RESET, BOLD, RESET, G, RESET);
        printf("  %s[5]%s > %sRun End-to-End (E2E) Test%s %s:Test Full Project Scenario%s\n", Y, RESET, BOLD, RESET, G, RESET);
        printf("  %s[0]%s > %sExit%s                      %s:Close the Program%s\n", Y, RESET, BOLD, RESET, BR, RESET);
        printf("---------------------------------------------------------------------\n");
        printf("  Enter your choice: ");

        char buf[10];
        if (fgets(buf, sizeof(buf), stdin)) {
            if (sscanf(buf, "%d", &caser) != 1) {
                printf("%s Invalid option! Try again.%s\n", BR, RESET);
                continue;
            }
        }

        system("cls||clear");

        switch (caser)
        {
            case 1:
                printf("%s>>> %sRegistering New Project...%s \n\n", G, BOLD, RESET);
                regis();
                printf("\nPress Enter to return to menu...");
                pause();
                break;

            case 2:
                printf("%s>>> %sSearching Projects...%s \n\n", C, BOLD, RESET);
                search();
                printf("\nPress Enter to return to menu...");
                pause();
                break;

            case 3:
                printf("%s>>> %sDisplaying All Projects...%s \n\n", Y, BOLD, RESET);
                Sall();
                printf("\nPress Enter to return to menu...");
                pause();
                break;

            case 4:
                printf("%s>>> %sRunning Unit Tests...%s \n", C, BOLD, RESET);
                run_unit_tests();
                printf("\nPress Enter to return to menu...");
                pause();
                break;
            
            case 5:
                printf("%s>>> %sRunning End-to-End Tests...%s \n", G, BOLD, RESET);
                run_e2e_test();
                printf("\nPress Enter to return to menu...");
                pause();
                break;

            case 0:
                running = 0;
                break;

            default:
                printf("%s Invalid option! Try again.%s\n", BR, RESET);
                pause();
                break;
        }
    }

    printf("\n%s=====================================================================%s\n", B, RESET);
    printf("     %sExiting...%s Thank you for using %sProject Management System!%s \n", C, RESET, BOLD, RESET);
    printf("%s=====================================================================%s\n", B, RESET);
    pause();

    return 0;
}
#endif