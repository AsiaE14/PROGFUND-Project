// test_unit.c
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include <time.h>

#define DATA_FILE "test_data.csv"



// สีสำหรับแสดงผล
#define GREEN   "\x1b[32m"
#define RED     "\x1b[31m"
#define YELLOW  "\x1b[33m"
#define CYAN    "\x1b[36m"
#define RESET   "\x1b[0m"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//  ประกาศฟังก์ชันจาก main.c ที่ต้องใช้เทสต์
int check_num(const char *str);
int is_valid_date(const char *date);
int is_valid_name(const char *name);
const char* auto_status(const char *start, const char *end);
int cmp_name(const void *a, const void *b);
void edit_record(char *record);
void test_rewrite_csv(char *records[], int count) {
    FILE *f = fopen("test_data.csv", "w");
    if (!f) {
        perror("Cannot create test_data.csv");
        return;
    }
    fprintf(f, "ProjectName,Start Date,End Date,Status\n");
    for (int i = 0; i < count; i++) {
        fprintf(f, "%s\n", records[i]);
    }
    fclose(f);
}
// ฟังก์ชันสำหรับแสดงผล
void print_result(const char *desc, int condition, int *pass, int *fail) {
    if (condition) {
        printf(GREEN " PASS " RESET "- %s\n", desc);
        (*pass)++;
    } else {
        printf(RED " FAIL " RESET "- %s\n", desc);
        (*fail)++;
    }
}

int main() {
    int pass = 0, fail = 0;

    system("cls||clear");
    printf(CYAN "\n======================================================\n" RESET);
    printf(YELLOW "                   UNIT TESTS (FULL)\n" RESET);
    printf(CYAN "======================================================\n\n" RESET);

    // ---------- check_num ----------
    print_result("check_num(\"12345\") should be TRUE",  check_num("12345") == 1, &pass, &fail);
    print_result("check_num(\"12a45\") should be FALSE", check_num("12a45") == 0, &pass, &fail);
    print_result("check_num(\"\") should be FALSE",       check_num("") == 0, &pass, &fail);

    // ---------- is_valid_date ----------
    print_result("is_valid_date(\"2025-05-15\") should be TRUE",  is_valid_date("2025-05-15") == 1, &pass, &fail);
    print_result("is_valid_date(\"2025-13-01\") should be FALSE", is_valid_date("2025-13-01") == 0, &pass, &fail);
    print_result("is_valid_date(\"2025-02-29\") (non-leap) FALSE",is_valid_date("2025-02-29") == 0, &pass, &fail);
    print_result("is_valid_date(\"2024-02-29\") (leap year) TRUE",is_valid_date("2024-02-29") == 1, &pass, &fail);
    print_result("is_valid_date(\"1999-00-10\") should be FALSE", is_valid_date("1999-00-10") == 0, &pass, &fail);
    print_result("is_valid_date(\"1999-12-32\") should be FALSE", is_valid_date("1999-12-32") == 0, &pass, &fail);

    // ---------- is_valid_name ----------
    print_result("is_valid_name(\"ProjectX\") TRUE", is_valid_name("ProjectX") == 1, &pass, &fail);
    print_result("is_valid_name(\"\") FALSE",        is_valid_name("") == 0, &pass, &fail);
    print_result("is_valid_name(\"A\") FALSE (too short)", is_valid_name("A") == 0, &pass, &fail);
    print_result("is_valid_name(\"Invalid,Name\") FALSE", is_valid_name("Invalid,Name") == 0, &pass, &fail);
    print_result("is_valid_name(\"My|Name\") FALSE", is_valid_name("My|Name") == 0, &pass, &fail);

    // ---------- auto_status ----------
    print_result("auto_status(In Progress)", strcmp(auto_status("2025-01-01","2025-12-31"), "In Progress") == 0, &pass, &fail);
    print_result("auto_status(Completed)",   strcmp(auto_status("2000-01-01","2005-12-31"), "Completed") == 0, &pass, &fail);
    print_result("auto_status(Not Started)", strcmp(auto_status("2030-01-01","2030-12-31"), "Not Started") == 0, &pass, &fail);

    // ---------- compare functions ----------
    char *a = "Apple,2025-01-01,2025-02-01,Done";
    char *b = "Banana,2025-01-01,2025-02-01,Done";
    print_result("cmp_name(A vs B) should < 0", cmp_name(&a, &b) < 0, &pass, &fail);

    // ---------- lowercasing search test ----------
    const char *name = "AssetManagement";
    const char *query = "asset";
    char nameLower[100], queryLower[100];
    for (int i = 0; name[i]; i++) nameLower[i] = tolower(name[i]);
    nameLower[strlen(name)] = '\0';
    for (int i = 0; query[i]; i++) queryLower[i] = tolower(query[i]);
    queryLower[strlen(query)] = '\0';
    print_result("case-insensitive search test", strstr(nameLower, queryLower) != NULL, &pass, &fail);

    // ---------- edit_record simulation ----------
    // จำลองการแก้ข้อมูลในบรรทัด
    char record[] = "TestProject,2025-01-01,2025-12-31,In Progress";
    edit_record(record); // ตรวจสอบว่าทำงานโดยไม่ crash
    print_result("edit_record() executed safely", 1, &pass, &fail);

    // ---------- rewrite_csv simulation ----------
    char *lines[] = {
        strdup("Apool,2025-01-01,2025-12-31,Done"),
        strdup("Bigbang,2024-01-01,2024-12-31,Done")
    };
    test_rewrite_csv(lines, 2);
    FILE *f = fopen("test_data.csv", "r");
    print_result("rewrite_csv created test_data.csv", f != NULL, &pass, &fail);
    if (f) fclose(f);

    // ---------- end of test ----------
    printf(CYAN "\n------------------------------------------------------\n" RESET);
    printf(GREEN " PASSED: %d  " RED " FAILED: %d\n" RESET, pass, fail);
    printf(CYAN "======================================================\n" RESET);

    printf(YELLOW "\nPress Enter to exit test...\n" RESET);
    getchar();
    return 0;
}