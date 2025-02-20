#include <windows.h>
#include <stdio.h>
#include "Calculator.h"

// Define the actual functions for RPC
int Add(int a, int b) {
    return a + b;
}

int Subtract(int a, int b) {
}

int Multiply(int a, int b) {
    return a * b;
}

float Divide(int a, int b) {
    if (b == 0) {
        printf("Division by zero!\n");
        return 0;
    }
    return (float)a / b;
}

// RPC server binding interface
void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t size) {
    return malloc(size);
}

void __RPC_USER MIDL_user_free(void __RPC_FAR * ptr) {
    free(ptr);
}

int main() {
    // Register the server interface
    RPC_STATUS status;
    status = RpcServerUseProtseqEp((unsigned char *)"ncacn_ip_tcp", RPC_C_PROTSEQ_MAX_REQS_DEFAULT, (unsigned char *)"4747", NULL);
    if (status) {
        printf("Error in RpcServerUseProtseqEp: %d\n", status);
        return 1;
    }

    status = RpcServerRegisterIf(Calculator_v1_0_s_ifspec, NULL, NULL);
    if (status) {
        printf("Error in RpcServerRegisterIf: %d\n", status);
        return 1;
    }

    // Start the server to listen for RPC calls
    status = RpcServerListen(1, RPC_C_LISTEN_MAX_CALLS_DEFAULT, FALSE);
    if (status) {
        printf("Error in RpcServerListen: %d\n", status);
        return 1;
    }

    return 0;
}
