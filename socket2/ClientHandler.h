#ifndef CLIENTHANDLER_H
#define CLIENTHANDLER_H

#include <iostream>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <atomic>

class ClientHandler {
public:
    ClientHandler();
    void startHandling();
    void addClient(int client_socket);
    void stop();

private:
    std::queue<int> client_queue;
    std::mutex queue_mutex;
    std::condition_variable queue_cond;
    std::atomic<bool> stop_flag;
    void handleClients();
};

#endif // CLIENTHANDLER_H
