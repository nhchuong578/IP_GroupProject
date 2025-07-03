#ifndef EXPENSES_H
#define EXPENSES_H
#define MAX_EXPENSES 100
#define MAX_CATEGORY 30
#define MAX_NOTE 100
#define MAX_TAGS 20
typedef struct {
    char date[11];
    char category[MAX_CATEGORY];
    float amount;
    char note[MAX_NOTE];
} Expense;
Expense expenses[MAX_EXPENSES];
extern int count;
extern char predefinedTags[MAX_TAGS][MAX_CATEGORY];
extern int tagCount;
int compareDates(const void *a, const void *b);
int isValidDate(const char *date);
void addExpense();
void viewExpenses();
void deleteExpense();
#endif // EXPENSES_H
