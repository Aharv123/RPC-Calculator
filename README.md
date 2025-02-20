RPC-Based Calculator

This project implements a Remote Procedure Call (RPC) based Calculator, where multiple clients (running on different machines) can connect to a central server to perform basic arithmetic operations.

Features

Server handles multiple clients.

Clients can connect to the server over a network using an IP address.

Supports basic arithmetic operations: Addition, Subtraction, Multiplication, and Division.

Prerequisites

Install Required Tools on Both Server and Client Machines:

Install Microsoft Visual Studio (with C/C++ development tools).

Install Windows SDK (for RPC development).

Ensure the system has rpc.h and rpcndr.h installed.

Network Setup:

The server should have a static IP address.

Ensure the firewall allows incoming connections on the RPC port (default 4747).

Setup Instructions

Step 1: Server Setup (On Your Laptop)

Compile and Run the Server:

cl /D "UNICODE" /D "_UNICODE" /EHsc /MD Server.c RpcServerStub.c RpcServer_s.c /link rpcrt4.lib
Server.exe

Ensure the Server is Running and Listening for Client Requests.

Step 2: Client Setup (On Other Laptops)

Compile and Run the Client:

cl /D "UNICODE" /D "_UNICODE" /EHsc /MD Client.c RpcClientStub.c RpcClient_s.c /link rpcrt4.lib
Client.exe

When prompted, enter the server IP address (e.g., 192.168.20.7).

Usage

Start the server on your laptop.

Run the client on another laptop and enter the server's IP.

Input a mathematical expression (e.g., 5 + 3).

The server processes the request and returns the result.

Type exit to terminate the client session.

Troubleshooting

If Clients Cannot Connect:

Ensure the server is running and listening on the correct port.

Check the firewall settings to allow connections on port 4747.

Ensure client machines are on the same network as the server.

Verify the server IP address using ipconfig in the command prompt.

Future Enhancements

Implement SSL encryption for secure communication.

Support advanced mathematical operations.

Implement multi-threading to handle multiple clients efficiently.



