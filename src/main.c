#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tags.h"
#include "expense.h"
#include "file.h"
#include "chart.h"

Expense expenses[MAX_EXPENSES];
int count = 0;
char predefinedTags[MAX_TAGS][MAX_CATEGORY];
int tagCount = 0;

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
            default: printf("Invalid choice. Please try again!\n");
        }
    } while (choice != 6);
    return 0;
}
