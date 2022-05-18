#include <stdio.h>
#include <unistd.h>

int main() {
    char* args[50];          // Argument array.
    char userInput[200];     // User input.
    char* userQuit = "quit"; // String to be compared to user input to quit program.
    int pid;                 // Process ID for fork().
    int i = 0;               // Counter.

    while(1) {
        // Promt and get input from user.
        printf("minor5> ");
        fgets(userInput, sizeof(userInput), stdin);

        // Pass userInput into args array.
        args[0] = strtok(userInput, " \n\0");

        // Loop to separate args into individual arguments, delimited by either space, newline, or NULL.
        while(args[i] != NULL) {
            i++;
            args[i] = strtok(NULL, " \n\0");
        }

        // If the first argument is "quit", exit the program.
        if(strcmp(args[0], userQuit) == 0) {
            printf("Exiting Minor5 Shell...\n");
            exit(EXIT_SUCCESS);
        }
        // Create child process.
        pid = fork();

        // Parent process will wait for child to execute.
        // Child process will execute the command given in userInput.
        if(pid > 0) {
            // Parent //
            wait( (int *) 0 );
        } else {
            // Child //
            int errChk;
            errChk = execvp(args[0], args);

            if(errChk == -1) {
                printf("%s: Command not found\n", userInput);
            }
        }
    }

    return 0;
}
