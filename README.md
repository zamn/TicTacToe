Tic Tac Toe Online!
==========================

This is a tic tac toe server/client I created over the past couple months working on/off on it. It is entirely created in C++ and only works on Linux currently. However, I did create a C# client for the server which you can view here: https://github.com/zamN/T3CSharp.

Installation
=========================

Simply run the following commands:

To make and run the Server
----------------------
```
cd TicTacToe/Server && make
./server
```
The server runs on port 6000 which you can change in T3Server.cpp.

To make and run the Client
----------------------------
```
cd TicTacToe/Client && make
./client
```
If you changed the port on the server then you will need to edit T3Client.cpp and change the port there also. I didn't make that as user friendly as I should have.

**NOTE: Client does still have some bugs as I was simply using it to test the server. I recommend using the C# client if you want to play the game.**

Contact Info
=====================
Feel free to contact me: adam [at] zamn [dot] net if you have any questions/concerns. 
