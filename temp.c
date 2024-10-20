#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <tlhelp32.h> // Include this header for process enumeration functions

void get_pid_by_name(const char *process_name) {
    HANDLE hProcessSnap;
    PROCESSENTRY32 pe32;

    // Take a snapshot of all processes in the system
    hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPALL, 0); // Use TH32CS_SNAPALL instead of TH32CS_PROCESS
    if (hProcessSnap == INVALID_HANDLE_VALUE) {
        printf("CreateToolhelp32Snapshot failed\n");
        return;
    }

    pe32.dwSize = sizeof(PROCESSENTRY32);

    // Retrieve information about the first process
    if (Process32First(hProcessSnap, &pe32)) {
        int found = 0; // Flag to check if the process is found
        do {
            // Compare the process name with the input process name
            if (strcmp(pe32.szExeFile, process_name) == 0) {
                printf("PID: %u, Process Name: %s\n", pe32.th32ProcessID, pe32.szExeFile);
                found = 1; // Set the flag to indicate that a match was found
            }
        } while (Process32Next(hProcessSnap, &pe32));

        if (!found) {
            printf("Process '%s' not found.\n", process_name);
        }
    } else {
        printf("Process32First failed\n");
    }

    CloseHandle(hProcessSnap);
}

int main() {
    char process_name[256];
    char choice;

    do {
        printf("Enter the process name (e.g., explorer.exe): ");
        scanf("%s", process_name); // Get the process name from user input

        get_pid_by_name(process_name); // Retrieve and print the PID

        printf("Do you want to search for another process? (y/n): ");
        scanf(" %c", &choice); // Read user's choice to continue or not
    } while (choice == 'y' || choice == 'Y'); // Repeat if the user chooses 'y'

    return 0;
}
