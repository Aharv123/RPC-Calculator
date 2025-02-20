#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Calculator.h"

// Declare MIDL user memory allocation and deallocation functions
void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t size) {
    return malloc(size);
}

void __RPC_USER MIDL_user_free(void __RPC_FAR * ptr) {
    free(ptr);
}

// Define a pointer to the server interface
RPC_BINDING_HANDLE BindingHandle;

// Function to perform calculation by parsing the expression
float evaluateExpression(const char *expression) {
    int num1, num2;
    char operator;
    float result = 0;

    // Parse the expression
    sscanf(expression, "%d %c %d", &num1, &operator, &num2);

    // Perform the operation
    switch (operator) {
        case '+':
            result = num1 + num2;
            break;
        case '-':
            result = num1 - num2;
            break;
        case '*':
            result = num1 * num2;
            break;
        case '/':
            if (num2 != 0) {
                result = (float)num1 / num2;
            } else {
                printf("Error: Division by zero!\n");
            }
            break;
        default:
            printf("Invalid operator!\n");
            break;
    }

    return result;
}

int main() {
    RPC_STATUS status;
    char expression[100];
    float result;
    int continueCalculation = 1;  // Flag to continue or exit the loop
    char serverIP[50];

    // Ask user for server IP address (e.g., the IP of your laptop where the server is running)
    printf("Enter the server IP address (e.g., 192.168.20.7): ");
    fgets(serverIP, sizeof(serverIP), stdin);
    serverIP[strcspn(serverIP, "\n")] = 0; // Remove the trailing newline

    // Initialize the RPC binding handle with the server IP address
    char bindingString[100];
    sprintf(bindingString, "ncacn_ip_tcp:%s:4747", serverIP);  // Use the entered IP address
    status = RpcBindingFromStringBinding((unsigned char *)bindingString, &BindingHandle);
    if (status) {
        printf("Error in RpcBindingFromStringBinding: %d\n", status);
        return 1;
    }

    // Main loop to keep asking for calculations until user chooses to exit
    while (continueCalculation) {
        // Prompt the user for the mathematical expression
        printf("\nEnter your operation (e.g., 2 + 2) or type 'exit' to quit: ");
        fgets(expression, sizeof(expression), stdin);

        // Remove the trailing newline character from fgets
        expression[strcspn(expression, "\n")] = 0;

        // If the user types 'exit', break the loop
        if (strcmp(expression, "exit") == 0) {
            continueCalculation = 0;
            printf("Exiting the calculator...\n");
        } else {
            // Evaluate the expression locally
            result = evaluateExpression(expression);

            if (result != 0) {
                printf("The result of '%s' is: %.2f\n", expression, result);
            }
        }
    }

    // Cleanup and close the RPC binding
    RpcBindingFree(&BindingHandle);

    return 0;
}
