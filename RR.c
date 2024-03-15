#include <stdio.h> 
#include <unistd.h> 

#define MAX_P 5 

struct PCB { 
	pid_t pid; 
	int arrivalTime; 
	int burst; 
}; 

// Function to perform the scheduling 
void roundRobin(struct PCB processTable[], int num_processes, int quantum) { 
	int remaining_time[MAX_P];
	int current_time = 0; 
	
	// Initialize remaining time for each process
	for (int i = 0; i < num_processes; ++i) { 
		remaining_time[i] = processTable[i].burst; 
	} 

	while (1) { 
		int all_finished = 1; // Flag to check if all processes are done 
	
		for (int i = 0; i < num_processes; ++i) { 
			if (remaining_time[i] > 0) { 
				all_finished = 0; // Means at least one is not done 

				// Execute process for the quantum or until finish
				int execute_time; 
				if (remaining_time[i] < quantum) { 
					execute_time = remaining_time[i]; 
				} else { 
					execute_time = quantum; 
				} 

				printf("Process %d (PID %d) executed for %d ms. Remaining time: %d ms\n", i, processTable[i].pid, execute_time, remaining_time[i]);

				// Update remaining time for the process 
				remaining_time[i] -= execute_time; 
		
				// Update the current time 
				current_time += execute_time; 
			}
	}
	if (all_finished) { 
			break; // all done
	}
	} 
}

int main() { 
	struct PCB processTable[MAX_P] = { 
		{1001, 0, 250},
        {1002, 50, 170},
        {1003, 130, 75},
        {1004, 190, 100},
        {1005, 210, 130}
    };
	
	int num_processes = sizeof(processTable) / sizeof(processTable[0]); 
	int quantum = 100; // Time quantum in ms 

	printf("Round-Robin Scheduling Simulation: \n"); 
	roundRobin(processTable, num_processes, quantum); 

	return 0; 
}
