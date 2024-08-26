#ifndef SERVER_H
#define SERVER_H

#include <netinet/in.h>
#include <atomic>
#include "ClientHandler.h"

class Server {
public:
    Server(const char* ip, int port);
    ~Server();
    void start();
    void stop();

private:
    int server_socket;
    sockaddr_in server_addr;
    std::atomic<bool> stop_flag;
    ClientHandler client_handler;

    void handleConnections();
    static void signalHandler(int signal);
};

#endif // SERVER_H
