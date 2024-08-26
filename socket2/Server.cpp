#include "Server.h"
#include <csignal>
#include <iostream>
#include <unistd.h>
#include <arpa/inet.h>

Server::Server(const char* ip, int port) : stop_flag(false) {
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket < 0) {
        throw std::runtime_error("Failed to create socket");
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(ip);
    server_addr.sin_port = htons(port);

    if (bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        throw std::runtime_error("Bind failed");
    }

    if (listen(server_socket, 5) < 0) {
        throw std::runtime_error("Listen failed");
    }

    signal(SIGINT, Server::signalHandler);
}

Server::~Server() {
    stop();
}

void Server::start() {
    client_handler.startHandling();
    std::thread(&Server::handleConnections, this).detach();
}

void Server::stop() {
    stop_flag = true;
    client_handler.stop();
    close(server_socket);
}

void Server::handleConnections() {
    while (!stop_flag) {
        int client_socket = accept(server_socket, nullptr, nullptr);
        if (client_socket < 0) {
            if (stop_flag) break;
            std::cerr << "Accept failed\n";
            continue;
        }

        client_handler.addClient(client_socket);
    }
}

void Server::signalHandler(int signal) {
    std::cout << "\nServer terminated.\n";
    exit(0);
}
