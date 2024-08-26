#include "Server.h"

int main() {
    const char* server_ip = "1.2.3.4";
    int server_port = 8888;

    try {
        Server server(server_ip, server_port);
        server.start();

        std::cout << "Server is running at " << server_ip << ":" << server_port << std::endl;

        // 서버가 중단될 때까지 대기
        while (true) {
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    } catch (const std::exception& ex) {
        std::cerr << "Error: " << ex.what() << std::endl;
        return 1;
    }

    return 0;
}