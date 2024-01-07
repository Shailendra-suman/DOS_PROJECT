#include <stdio.h>

struct Process { 
    int processID;
    int arrivalTime; 
    int burstTime;
};

void executeFCFS(struct Process processes[], int n) { 
    int currentTime = 0;
    float avgTurnaroundTime = 0, avgWaitingTime = 0;

    printf("Gantt Chart (FCFS):\n"); 
    printf("Process\tStart Time\tEnd Time\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t\t%d\n", processes[i].processID, currentTime, currentTime + processes[i].burstTime);
        avgWaitingTime += currentTime - processes[i].arrivalTime; 
        avgTurnaroundTime += currentTime + processes[i].burstTime -processes[i].arrivalTime;
        currentTime += processes[i].burstTime;
        } 
        avgWaitingTime /= n; 
        avgTurnaroundTime /= n;
        printf("Average TurnAround Time = %.2f\t \n Average Waiting Time= %.2f\n", avgTurnaroundTime,avgWaitingTime);
        }
        void executeRR(struct Process processes[], int n, int timeQuantum) {
            int remainingBurst[n];
            int currentTime = 0;
            float avgTurnaroundTime = 0, avgWaitingTime = 0;
            for (int i = 0; i < n; i++) {
                remainingBurst[i] = processes[i].burstTime;
                }
                printf("Gantt Chart (Round Robin):\n");
                printf("Process\tStart Time\tEnd Time\n");
            while (1) {
                    int done = 1;
                    for (int i = 0; i < n; i++) {
                        if (remainingBurst[i] > 0) {
                            done = 0;
                            int executeTime = (remainingBurst[i] < timeQuantum) ? remainingBurst[i] : timeQuantum;
                            printf("P%d\t%d\t\t%d\n", processes[i].processID, currentTime, currentTime + executeTime);
                            currentTime += executeTime; 
                            remainingBurst[i] -= executeTime;
                            if (remainingBurst[i] == 0) { 
                            avgWaitingTime += currentTime - processes[i].arrivalTime - processes[i].burstTime;
                            avgTurnaroundTime += currentTime - processes[i].arrivalTime;
                            }
                        }
                    }
                    int allDone = 1;
                    for (int i = 0; i < n; i++) {
                        if (remainingBurst[i] > 0) {
                            allDone = 0;
                             break;
                         }
                     }
                     if (allDone == 1) {
                        break;
                        }
                }
                avgWaitingTime /= n;
                avgTurnaroundTime /= n;
                printf("Average TurnAround Time = %.2f\t \n Average Waiting Time=%.2f\n", avgTurnaroundTime,avgWaitingTime);
        }
        int main() {
            int n, choice, quantum;
            printf("Enter the number of processes: ");
            scanf("%d", &n);
            struct Process processes[n];
            printf("Enter process details (Arrival Time and Burst Time):\n");
            for (int i = 0; i < n; i++) {
                printf("Process %d: ", i + 1);
                processes[i].processID = i + 1;
                scanf("%d %d", &processes[i].arrivalTime, &processes[i].burstTime);
            }
            printf("\nChoose Scheduling Algorithm:\n");
            printf("1. First Come First Served (FCFS)\n");
            printf("2. Round Robin (RR)\n");
            printf("Enter your choice: ");
            scanf("%d", &choice);
            switch (choice) {
                case 1:
                  executeFCFS(processes, n);
                  break;
                case 2:
                  printf("Enter time quantum for Round Robin: ");
                  scanf("%d", &quantum);
                  executeRR(processes, n, quantum);
                  break;
                default:
                 printf("Invalid choice\n");
                 break;
            }
            return 0;
       }
