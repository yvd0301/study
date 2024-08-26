#include "ClientHandler.h"
#include <unistd.h>
#include <cstring>

ClientHandler::ClientHandler() : stop_flag(false) {}

void ClientHandler::startHandling() {
    std::thread(&ClientHandler::handleClients, this).detach();
}

void ClientHandler::addClient(int client_socket) {
    std::lock_guard<std::mutex> lock(queue_mutex);
    client_queue.push(client_socket);
    queue_cond.notify_one();
}

void ClientHandler::stop() {
    stop_flag = true;
    queue_cond.notify_all(); // 스레드 깨우기
}

void ClientHandler::handleClients() {
    while (!stop_flag) {
        std::unique_lock<std::mutex> lock(queue_mutex);

        queue_cond.wait(lock, [this]() { return !client_queue.empty() || stop_flag; });

        if (stop_flag && client_queue.empty()) {
            break;
        }

        int client_socket = client_queue.front();
        client_queue.pop();
        lock.unlock();

        // 클라이언트와 데이터 송수신
        char buffer[256];
        ssize_t bytes_read = read(client_socket, buffer, sizeof(buffer) - 1);
        if (bytes_read > 0) {
            buffer[bytes_read] = '\0';
            std::cout << "Received: " << buffer << std::endl;
            write(client_socket, buffer, bytes_read);
        }

        close(client_socket);
    }
}
