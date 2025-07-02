#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tags.h"

#define MAX_EXPENSES 100
#define MAX_NOTE 100

typedef struct {
    char date[11];      // Format: YYYY-MM-DD
    char category[MAX_CATEGORY];
    float amount;
    char note[MAX_NOTE];
} Expense;

Expense expenses[MAX_EXPENSES];


int compareDates(const void *a, const void *b) {
    return strcmp(((Expense *)a)->date, ((Expense *)b)->date);      // sorting function
}
int count = 0;
int tagCount = 0;
//tags = categories
int findCategoryIndex(char (*categories)[MAX_CATEGORY], int catCount, char *target) {
    for (int i = 0; i < catCount; i++) {
        if (strcmp(categories[i], target) == 0) {
            return i;
        }
    }
    return -1;
} //

char predefinedTags[MAX_TAGS][MAX_CATEGORY];

void addExpense() {
    if (count >= MAX_EXPENSES) {
        printf("\n🚫 Expense list is full!\n");
        return;
    }

    if (tagCount == 0) {
        printf("No tags available. Please set up tags first.");
        return;
    }

    printf("\nEnter date (YYYY-MM-DD): ");
    scanf("%10s", expenses[count].date);
    getchar();

    printf("Choose a tag:\n");
    for (int i = 0; i < tagCount; i++) {
        printf("%d. %s\n", i + 1, predefinedTags[i]);
    }
    int tagChoice;
    printf("Enter the number of the tag: ");
    scanf("%d", &tagChoice);
    getchar();
    if (tagChoice < 1 || tagChoice > tagCount) {
        printf("Invalid tag selection.\n");
        return;
    }
    strcpy(expenses[count].category, predefinedTags[tagChoice - 1]);

    printf("Enter amount: $");
    scanf("%f", &expenses[count].amount);
    getchar();

    printf("Enter note (optional): ");
    fgets(expenses[count].note, MAX_NOTE, stdin);
    expenses[count].note[strcspn(expenses[count].note, "\n")] = 0;

    count++;
    printf("Expense added successfully!\n");
}

void deleteExpense() {
    if (count == 0) {
        printf("\nNo expenses to delete.\n");
        return;
    }

void viewExpenses();
    printf("\nEnter the number of the expense to delete: ");
    int index;
    scanf("%d", &index);
    getchar();

    if (index < 1 || index > count) {
        printf("Invalid expense number.\n");
        return;
    }

    for (int i = index - 1; i < count - 1; i++) {
        expenses[i] = expenses[i + 1];
    }
    count--;
    printf("Expense deleted successfully.\n");
}

void viewExpenses() {
    if (count == 0) {
        printf("\nNo expenses recorded yet.\n");
        return;
    }

    qsort(expenses, count, sizeof(Expense), compareDates);

    float total = 0;
    char categories[MAX_EXPENSES][MAX_CATEGORY];
    float catTotals[MAX_EXPENSES] = {0};
    int catCount = 0;

    printf("\n===== Expense List (Chronological) =====\n");
    for (int i = 0; i < count; i++) {
        printf("%d. %s | %s | $%.2f | %s\n", i + 1,
               expenses[i].date,
               expenses[i].category,
               expenses[i].amount,
               expenses[i].note);
        total += expenses[i].amount;

        int idx = findCategoryIndex(categories, catCount, expenses[i].category);
        if (idx == -1) {
            strcpy(categories[catCount], expenses[i].category);
            catTotals[catCount] = expenses[i].amount;
            catCount++;
        } else {
            catTotals[idx] += expenses[i].amount;
        }
    }

    printf("\n===== Category Totals =====\n");
    for (int i = 0; i < catCount; i++) {
        printf("%s: $%.2f\n", categories[i], catTotals[i]);
    }

    printf("-----------------------------\n");
    printf("Total spent: $%.2f\n", total);
}

void showBarChart() {
    if (count == 0) {
        printf("\nNo expenses to show in bar chart.\n");
        return;
    }

    char categories[MAX_EXPENSES][MAX_CATEGORY];
    float catTotals[MAX_EXPENSES] = {0};
    int catCount = 0;
    float maxAmount = 0;

    for (int i = 0; i < count; i++) {
        int idx = findCategoryIndex(categories, catCount, expenses[i].category);
        if (idx == -1) {
            strcpy(categories[catCount], expenses[i].category);
            catTotals[catCount] = expenses[i].amount;
            if (catTotals[catCount] > maxAmount) maxAmount = catTotals[catCount];
            catCount++;
        } else {
            catTotals[idx] += expenses[i].amount;
            if (catTotals[idx] > maxAmount) maxAmount = catTotals[idx];
        }
    }

    printf("\n===== Category Bar Chart =====\n");
    for (int i = 0; i < catCount; i++) {
        printf("%-10s | ", categories[i]);
        int barLength = (int)(catTotals[i] / maxAmount * 40);
        for (int j = 0; j < barLength; j++) {
            putchar('#');
        }
        printf(" $%.2f\n", catTotals[i]);
    }
}

void saveToFile() {
    FILE *fp = fopen("expenses.txt", "w");
    if (!fp) {
        printf("\nError opening file!\n");
        return;
    }
    for (int i = 0; i < count; i++) {
        fprintf(fp, "%s,%s,%.2f,%s\n", expenses[i].date, expenses[i].category,
                expenses[i].amount, expenses[i].note);
    }
    fclose(fp);
    printf("\nExpenses saved to 'expenses.txt'\n");
}

void loadFromFile() {
    FILE *fp = fopen("expenses.txt", "r");
    if (!fp) return;

    while (fscanf(fp, "%10[^,],%29[^,],%f,%99[^\n]\n",
                  expenses[count].date,
                  expenses[count].category,
                  &expenses[count].amount,
                  expenses[count].note) == 4) {
        count++;
    }
    fclose(fp);
}

int main() {
    int choice;
    loadFromFile();
    loadTags();

    do {
        printf("\n===== Personal Expense Tracker =====\n");
        printf("1. Add Expense\n");
        printf("2. View Expenses\n");
        printf("3. Setup Tags\n");
        printf("4. Show Bar Chart\n");
        printf("5. Delete Expense\n");
        printf("6. Save & Exit\n");
        printf("Choose an option: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1: addExpense(); break;
            case 2: viewExpenses(); break;
            case 3: setupTags(); break;
            case 4: showBarChart(); break;
            case 5: deleteExpense(); break;
            case 6: saveToFile(); saveTags(); printf("Goodbye!\n"); break;
            default: printf("Invalid choice. Try again.\n");
        }
    } while (choice != 6);

    return 0;
}
