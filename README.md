# CipherMessenger

CipherMessenger is a client-server application that can be used to exchange encrypted messages.

## Building the Project

To build the project, follow these steps:

```bash
$ mkdir build
$ cd build
$ cmake ..
$ make
```

## How to use

After you build the project, you need to start the server. Use the `./server` command in the terminal to do this. After that, run the `./client` in another terminal. Now in any of the terminals, write a message and it will be encrypted and sent, upon receipt the message is decrypted.