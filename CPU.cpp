#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
using namespace std;

// Structure to represent a process
struct Process {
    string pid;
    int arrivalTime;
    int burstTime;
    int remainingTime;
};

// Function to calculate FCFS scheduling
void fcfs(vector<Process>& processes) {
    int n = processes.size();
    vector<int> waitingTime(n, 0);
    vector<int> turnaroundTime(n, 0);
    int totalWaitingTime = 0;
    int totalTurnaroundTime = 0;

    // Calculate waiting time
    for (int i = 1; i < n; i++) {
        waitingTime[i] = processes[i - 1].burstTime + waitingTime[i - 1];
        totalWaitingTime += waitingTime[i];
    }

    // Calculate turnaround time
    for (int i = 0; i < n; i++) {
        turnaroundTime[i] = processes[i].burstTime + waitingTime[i];
        totalTurnaroundTime += turnaroundTime[i];
    }

    // Display results
    cout << "\nFCFS Scheduling:\n";
    cout << "Gantt Chart: ";
    for (int i = 0; i < n; i++) {
        cout << processes[i].pid << " (" << waitingTime[i] << "-" << turnaroundTime[i] << ")";
        if (i != n - 1) cout << " → ";
    }
    cout << "\nWaiting Times: ";
    for (int i = 0; i < n; i++) {
        cout << processes[i].pid << " = " << waitingTime[i];
        if (i != n - 1) cout << ", ";
    }
    cout << "\nTurnaround Times: ";
    for (int i = 0; i < n; i++) {
        cout << processes[i].pid << " = " << turnaroundTime[i];
        if (i != n - 1) cout << ", ";
    }
    cout << fixed << setprecision(2);
    cout << "\nAverage Waiting Time: " << (float)totalWaitingTime / n;
    cout << "\nAverage Turnaround Time: " << (float)totalTurnaroundTime / n << "\n";
}

// Function to calculate SJF scheduling
void sjf(vector<Process>& processes) {
    // Sort processes by burst time
    sort(processes.begin(), processes.end(), [](const Process& a, const Process& b) {
        return a.burstTime < b.burstTime;
    });
    fcfs(processes); // Reuse FCFS logic since SJF is non-preemptive
}

// Function to calculate SRT scheduling
void srt(vector<Process>& processes) {
    // Implement SRT (preemptive SJF)
    cout << "\nSRT Scheduling is not implemented in this example.\n";
}

// Function to calculate Round Robin scheduling
void roundRobin(vector<Process>& processes, int quantum) {
    // Implement Round Robin
    cout << "\nRound Robin Scheduling is not implemented in this example.\n";
}

int main() {
    while (true) {
        cout << "\nCPU Scheduling Algorithms\n";
        cout << "1. First-Come, First-Served (FCFS)\n";
        cout << "2. Shortest-Job-First (SJF)\n";
        cout << "3. Shortest-Remaining-Time (SRT)\n";
        cout << "4. Round Robin (RR)\n";
        cout << "5. Exit\n";
        int choice;
        cout << "Select an option: ";
        cin >> choice;

        if (choice == 5) break;

        int n;
        cout << "Enter the number of processes: ";
        cin >> n;

        vector<Process> processes(n);
        for (int i = 0; i < n; i++) {
            cout << "Enter Process ID for process " << i + 1 << ": ";
            cin >> processes[i].pid;
            cout << "Enter Arrival Time for " << processes[i].pid << ": ";
            cin >> processes[i].arrivalTime;
            cout << "Enter Burst Time for " << processes[i].pid << ": ";
            cin >> processes[i].burstTime;
            processes[i].remainingTime = processes[i].burstTime;
        }

        switch (choice) {
            case 1:
                fcfs(processes);
                break;
            case 2:
                sjf(processes);
                break;
            case 3:
                srt(processes);
                break;
            case 4:
                int quantum;
                cout << "Enter time quantum for Round Robin: ";
                cin >> quantum;
                roundRobin(processes, quantum);
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }
    return 0;
}