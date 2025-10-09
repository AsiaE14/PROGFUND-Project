// test_e2e.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define DATA_FILE "test_data.csv"
#define rewrite_csv test_rewrite_csv



#define GREEN   "\x1b[32m"
#define RED     "\x1b[31m"
#define YELLOW  "\x1b[33m"
#define CYAN    "\x1b[36m"
#define RESET   "\x1b[0m"

//  ใช้ไฟล์จำลองแทน data.csv 
#define TEST_FILE "test_data.csv"


void regis(void);
void search(void);
void Sall(void);
int is_valid_date(const char *date);
int is_valid_name(const char *name);

// เขียน CSV จำลอง
void setup_test_csv() {
    FILE *f = fopen(TEST_FILE, "w");
    fprintf(f, "Project,StartDate,EndDate,Status\n");
    fprintf(f, "Alpha,2025-01-01,2025-12-31,In Progress\n");
    fprintf(f, "Beta,2023-01-01,2023-12-31,Completed\n");
    fprintf(f, "Gamma,2026-05-01,2026-12-31,Not Started\n");
    fclose(f);
}

// อ่านจำนวนบรรทัดในไฟล์ 
int count_records(const char *filename) {
    FILE *f = fopen(filename, "r");
    if (!f) return -1;
    char buf[256];
    int count = -1; // ไม่รวม header
    while (fgets(buf, sizeof(buf), f)) count++;
    fclose(f);
    return count;
}

// ทดสอบเพิ่มข้อมูลใหม่
void test_add_record(int *pass, int *fail) {
    FILE *f = fopen(TEST_FILE, "a");
    if (!f) { printf(RED "FAIL: cannot open test CSV\n" RESET); (*fail)++; return; }
    fprintf(f, "Delta,2025-06-01,2025-09-01,In Progress\n");
    fclose(f);

    int lines = count_records(TEST_FILE);
    if (lines == 4) {
        printf(GREEN " PASS " RESET "- Added new record successfully.\n");
        (*pass)++;
    } else {
        printf(RED " FAIL " RESET "- Record count mismatch after add (got %d)\n", lines);
        (*fail)++;
    }
}

// ทดสอบแก้ไขข้อมูล
void test_edit_record(int *pass, int *fail) {
    FILE *f = fopen(TEST_FILE, "r");
    if (!f) { printf(RED "FAIL: cannot open test CSV\n" RESET); (*fail)++; return; }

    FILE *temp = fopen("temp_test.csv", "w");
    char buf[512];
    int edited = 0;
    while (fgets(buf, sizeof(buf), f)) {
        if (strstr(buf, "Beta")) {
            fprintf(temp, "Beta,2023-01-01,2023-12-31,Archived\n");
            edited = 1;
        } else {
            fprintf(temp, "%s", buf);
        }
    }
    fclose(f);
    fclose(temp);
    remove(TEST_FILE);
    rename("temp_test.csv", TEST_FILE);

    f = fopen(TEST_FILE, "r");
    int ok = 0;
    while (fgets(buf, sizeof(buf), f)) {
        if (strstr(buf, "Archived")) ok = 1;
    }
    fclose(f);

    if (edited && ok) {
        printf(GREEN " PASS " RESET "- Edited record successfully.\n");
        (*pass)++;
    } else {
        printf(RED " FAIL " RESET "- Edit operation failed.\n");
        (*fail)++;
    }
}

// ทดสอบลบข้อมูล
void test_delete_record(int *pass, int *fail) {
    FILE *f = fopen(TEST_FILE, "r");
    FILE *temp = fopen("temp_test.csv", "w");
    char buf[512];
    int deleted = 0;
    while (fgets(buf, sizeof(buf), f)) {
        if (strstr(buf, "Alpha")) { deleted = 1; continue; }
        fprintf(temp, "%s", buf);
    }
    fclose(f);
    fclose(temp);
    remove(TEST_FILE);
    rename("temp_test.csv", TEST_FILE);

    int lines = count_records(TEST_FILE);
    if (deleted && lines == 3) {
        printf(GREEN " PASS " RESET "- Deleted record successfully.\n");
        (*pass)++;
    } else {
        printf(RED " FAIL " RESET "- Delete operation failed (lines=%d)\n", lines);
        (*fail)++;
    }
}

// ทดสอบการค้นหา
void test_search(int *pass, int *fail) {
    FILE *f = fopen(TEST_FILE, "r");
    char buf[256];
    int found = 0;
    while (fgets(buf, sizeof(buf), f)) {
        char copy[256];
        strcpy(copy, buf);
        if (strstr(copy, "Gamma")) {
            found = 1;
            break;
        }
    }
    fclose(f);

    if (found) {
        printf(GREEN " PASS " RESET "- Search found 'Gamma' correctly.\n");
        (*pass)++;
    } else {
        printf(RED " FAIL " RESET "- Search did not find 'Gamma'.\n");
        (*fail)++;
    }
}

// ทดสอบการแสดงผล (จำลอง Sall)
void test_display(int *pass, int *fail) {
    FILE *f = fopen(TEST_FILE, "r");
    if (!f) { printf(RED "FAIL: cannot open test CSV\n" RESET); (*fail)++; return; }
    char buf[256];
    int printed = 0;
    printf(CYAN "\n--- Displaying test_data.csv ---\n" RESET);
    while (fgets(buf, sizeof(buf), f)) {
        printf("%s", buf);
        printed++;
    }
    fclose(f);
    printf(CYAN "--------------------------------\n" RESET);

    if (printed > 0) {
        printf(GREEN " PASS " RESET "- Display worked.\n");
        (*pass)++;
    } else {
        printf(RED " FAIL " RESET "- Display empty.\n");
        (*fail)++;
    }
}

// ลบไฟล์หลังทดสอบ
void cleanup() {
   // remove(TEST_FILE);
}

int main() {
    system("cls||clear");

    int pass = 0, fail = 0;
    printf(CYAN "\n======================================================\n" RESET);
    printf(YELLOW "                   E2E TEST (Full Flow)\n" RESET);
    printf(CYAN "======================================================\n" RESET);

    setup_test_csv();

    test_add_record(&pass, &fail);
    test_edit_record(&pass, &fail);
    test_delete_record(&pass, &fail);
    test_search(&pass, &fail);
    test_display(&pass, &fail);

    cleanup();

    printf(CYAN "\n------------------------------------------------------\n" RESET);
    printf(GREEN "PASSED: %d  " RED " FAILED: %d\n" RESET, pass, fail);
    printf(CYAN "======================================================\n" RESET);

    printf(YELLOW "\nPress Enter to exit E2E test...\n" RESET);
    getchar();
    return 0;
}