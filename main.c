#include <stdio.h>

void matchFunc(int programmers[][5], int departments[][5]) {
    // List of programmer/department matches, index is department and value is programmer
    int matches[5] = {0};

    // List of programmers, 0 if available, 1 if taken.
    int taken[5] = {0};

    // Iterator to run the function five times
    int i = 0;
    while (i < 5) {
        // Create an arr of highest choices, where 0 means department at that index is filled
        int highestChoice[5] = {0};

        // To find highest choices
        for (int j = 0; j < 5; j++) {
            // If department already has programmer, leave as 0
            if (matches[j] != 0) {
                continue;
            }

            // Otherwise make it the value of their highest choice that's remaining
            int k = 0;
            while (1) {
                // This means their highest choice is gone, continue on
                if (taken[departments[j][k] - 1] == 1) {
                    k++;
                } else {
                    highestChoice[j] = departments[j][k];
                    break;
                }
            }
        }
        
        // Mark the first department that doesn't have a programmer
        int pickingDept;
        for (int l = 0; l < 5; l++) {
            if (highestChoice[l] != 0) {
                pickingDept = l;
                break;
            }
        }

        // Mark all departments that want the programmer wanted by the "picking department"
        int competitors[5] = {0};
        int isCompetitor = 0;
        for (int m = 0; m < 5; m++) {
            if (m == pickingDept) {
                competitors[m] = 1;
                continue;
            }
            if (highestChoice[m] == highestChoice[pickingDept]) {
                competitors[m] = 1;
                isCompetitor = 1;
            }
        }

        // If there's competition, find the programmer's first choice among departments wanting them
        if (isCompetitor) {
            for (int n = 0; n < 5; n++) {
                if (competitors[programmers[highestChoice[pickingDept] - 1][n] - 1] == 1) {
                    // Set the department to that programmer
                    matches[programmers[highestChoice[pickingDept] - 1][n] - 1] = highestChoice[pickingDept];
                    // Mark that programmer as taken
                    taken[highestChoice[pickingDept] - 1] = 1;
                    break;
                }
            }
        // Otherwise, give them their top choice
        } else {
            matches[pickingDept] = highestChoice[pickingDept];
        }

        i++;
    }

    // Printing output
    for (int o = 0; o < 5; o++) {
        printf("Department #%d will get Programmer #%d\n", o + 1, matches[o]);
    }
}

int main() {
    // Get file, initialize programmer and department arrays
    FILE *in_file = fopen("matching-data.txt", "r");
    int programmers[5][5] = {{0}};
    int departments[5][5] = {{0}};

    // Read from the file
    for (int i = 0; i < 10; i++) {
        // Assign to departments
        if (i < 5) {
            fscanf(in_file, "%d %d %d %d %d", &departments[0][i], &departments[1][i], &departments[2][i], &departments[3][i], &departments[4][i]);
        // Assign to programmers
        } else {
            fscanf(in_file, "%d %d %d %d %d", &programmers[0][i - 5], &programmers[1][i - 5], &programmers[2][i - 5], &programmers[3][i - 5], &programmers[4][i - 5]);
        }
    }
    matchFunc(programmers, departments);

    return 0;

}