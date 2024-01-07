#include <stdio.h>
#include <stdbool.h>
#define NUM_PROCESSES 5
#define NUM_RESOURCES 4

int available[NUM_RESOURCES] = {6, 7, 12, 12}; 
int max[NUM_PROCESSES][NUM_RESOURCES] = {
    {0, 0, 1, 2},
    {2, 7, 5, 0},
    {6, 6, 5, 6},
    {4, 3, 5, 6},
    {0, 6, 5, 2}
};
int allocation[NUM_PROCESSES][NUM_RESOURCES] = {
    {0, 0, 1, 2},
    {2, 0, 0, 0},
    {0, 0, 3, 4},
    {2, 3, 5, 4},
    {0, 3, 3, 2}
};
int need[NUM_PROCESSES][NUM_RESOURCES];
bool finish[NUM_PROCESSES];

void calculateNeedMatrix() {
    for (int i = 0; i < NUM_PROCESSES; ++i) {
        for (int j = 0; j < NUM_RESOURCES; ++j) {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }
}

bool isSafeState(int safeSequence[NUM_PROCESSES]) {
    int work[NUM_RESOURCES];
    for (int i = 0; i < NUM_RESOURCES; ++i) {
        work[i] = available[i];
    }
    for (int i = 0; i < NUM_PROCESSES; ++i) {
        finish[i] = false;
    }
    int count = 0;
    while (count < NUM_PROCESSES) {
        bool found = false;
        for (int i = 0; i < NUM_PROCESSES; ++i) {
            if (!finish[i]) {
                bool canAllocate = true;
                for (int j = 0; j < NUM_RESOURCES; ++j) { 
                    if (need[i][j] > work[j]) {
                        canAllocate = false;
                        break;
                    }
                }
                if (canAllocate) {
                    for (int j = 0; j < NUM_RESOURCES; ++j) {
                        work[j] += allocation[i][j];
                    }
                    finish[i] = true;
                    safeSequence[count++] = i;
                    found = true;
                }
            }
        }
        if (!found) {
            return false;
        }
    }
    return true;
    }
    int requestResources(int process, int request[NUM_RESOURCES]) {
        for (int i = 0; i < NUM_RESOURCES; ++i) {
            if (request[i] > need[process][i] || request[i] > available[i]) {
                return -1;
            }
        }
        for (int i = 0; i < NUM_RESOURCES; ++i) {
            available[i] -= request[i]; allocation[process][i] += request[i];
            need[process][i] -= request[i];
        }
        int safeSequence[NUM_PROCESSES];
        if (isSafeState(safeSequence)) {
            return 1;
        }
        else {
            for (int i = 0; i < NUM_RESOURCES; ++i) {
                available[i] += request[i];
                allocation[process][i] -= request[i];
                need[process][i] += request[i];
            }
        return 0;
        }
    }
    void printNeedMatrix() {
        printf("a) Need Matrix:\n");
        for (int i = 0; i < NUM_PROCESSES; ++i) {
            for (int j = 0; j < NUM_RESOURCES; ++j) {
                printf("%d ", need[i][j]);
            }
            printf("\n");
        }
    }
    void displaySafeSequence(int safeSequence[NUM_PROCESSES]) {
        printf("\nb) ");
        if (isSafeState(safeSequence)) {
            printf("System is in a safe state.\nSafe Sequence: ");
            for (int i = 0; i < NUM_PROCESSES; ++i) {
                printf("P%d ", safeSequence[i] + 1);
            }
            printf("\n");
            } else {
                printf("System is not in a safe state.\n");
            }
    }
    int main() {
        calculateNeedMatrix();
        printNeedMatrix();
        int safeSequence[NUM_PROCESSES];
        displaySafeSequence(safeSequence);
        int process_num;
        int request[NUM_RESOURCES];
        printf("\n");
        printf("c) Enter process number (P1-P5, enter the corresponding number): ");
        scanf("%d", &process_num);
        process_num--;
        printf("Enter resource request for process P:%d ", process_num + 1);
        for (int i = 0; i < NUM_RESOURCES; ++i) {
            scanf("%d", &request[i]);
        }
        int result = requestResources(process_num, request);
        if (result == 1) {
            printf("Request can be granted immediately.\n");
            } else if (result == 0) {
                printf("Request denied as it leads to an unsafe state.\n");
            } else {
                printf("Requested resources exceed available or need.\n");
            }
            return 0;
    }



