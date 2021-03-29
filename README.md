# KawaSpace-Assignment
Chatroom in Linux Using C programming and Socket Programming.



## Workflow:
- Program starts and asks for input as '/c'or '/x'.

- Server Initializes sockets at serverside.

- Starts listening for incoming connections.

- Accepts incoming client connection.

- Creates a thread for every client and stores all the FDs in an array.

- UserHandler handles all the chat functions at serverside.

- At clintside2 threads are used to handle receiving and sending messages

- When a user exits the room the num of users in FD array is decremented.



## Example

![Alt Text](https://media.giphy.com/media/N3LHwLpdF1iJKAtnQr/giphy.gif)





## How to run
``` 
cd <root code directory>

Make 

./server

./client
```
