#include <iostream>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <pthread.h>
#include <signal.h>
#include <queue>
#include <csignal>

volatile sig_atomic_t stop = 0;
int server_socket;
const char* server_ip = "1.2.3.4"; // 테스트할 IP 주소
const int server_port = 8080; // 사용할 포트 번호

// 시그널 핸들러
void handle_signal(int signal) {
    stop = 1;
    close(server_socket); // 서버 소켓 닫기
    std::cout << "Server terminated.\n";
    exit(0);  // 안전하게 종료
}

/*
// 클라이언트 처리 스레드 함수
void* handle_client(void* arg) {
    int client_socket = *(int*)arg;
    delete (int*)arg;  // 메모리 해제

    char buffer[256];

    while (!stop) {
        ssize_t bytes_read = read(client_socket, buffer, sizeof(buffer) - 1);

        if (bytes_read > 0) {
            buffer[bytes_read] = '\0';
            std::cout << "Received: " << buffer << std::endl;
            // 클라이언트에게 동일한 메시지를 다시 전송
            write(client_socket, buffer, bytes_read);
        } else if (bytes_read == 0) {
            std::cout << "Client disconnected.\n";
            break;
        } else if (bytes_read < 0) {
            std::cerr << "Read error\n";
            break;
        }
    }

    close(client_socket);
    return nullptr;
}

int main() {
    std::cout << "Hello, World!" << std::endl;

    signal(SIGINT, handle_signal); // Ctrl+C 시그널 처리

    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket < 0) {
        std::cerr << "Failed to create socket\n";
        return 1;
    }

    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(server_ip);
    server_addr.sin_port = htons(server_port);

    if (bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        std::cerr << "Bind failed\n";
        return 1;
    }

    if (listen(server_socket, 5) < 0) {
        std::cerr << "Listen failed\n";
        return 1;
    }

    std::cout << "Server is listening at " << server_ip << ":" << server_port << std::endl;

    while (!stop) {
        std::cout << "Waiting for a client to connect..." << std::endl;

        int client_socket = accept(server_socket, NULL, NULL);
        if (client_socket < 0) {
            if (stop) break; // 종료 신호가 발생하면 루프 종료
            std::cerr << "Accept failed\n";
            continue;
        }

        std::cout << "Client connected!" << std::endl;

        // 클라이언트 처리 스레드 생성
        pthread_t thread_id;
        int *pclient = new int;
        *pclient = client_socket;
        pthread_create(&thread_id, nullptr, handle_client, pclient);
        pthread_detach(thread_id); // 스레드 종료 시 자원 자동 해제
    }

    close(server_socket);
    std::cout << "end of program" << std::endl;
    return 0;
}
*/

// 작업 큐와 뮤텍스/조건 변수
std::queue<int> client_queue;
pthread_mutex_t queue_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t queue_cond = PTHREAD_COND_INITIALIZER;

const int MAX_THREADS = 4; // 스레드 풀 크기

// 클라이언트 요청 처리 함수
void* handle_client(void* arg) {
    while (!stop) {
        pthread_mutex_lock(&queue_mutex);

        // 큐에 클라이언트 소켓이 들어올 때까지 대기
        while (client_queue.empty() && !stop) {
            pthread_cond_wait(&queue_cond, &queue_mutex);
        }

        if (stop) {
            pthread_mutex_unlock(&queue_mutex);
            break;
        }

        // 큐에서 클라이언트 소켓을 꺼내 처리
        int client_socket = client_queue.front();
        client_queue.pop();
        pthread_mutex_unlock(&queue_mutex);

        // 클라이언트와 데이터 송수신
        char buffer[256];
        ssize_t bytes_read = read(client_socket, buffer, sizeof(buffer) - 1);
        if (bytes_read > 0) {
            buffer[bytes_read] = '\0';
            std::cout << "Received: " << buffer << std::endl;
            // 클라이언트에게 동일한 메시지를 다시 전송
            write(client_socket, buffer, bytes_read);
        }

        close(client_socket); // 클라이언트 소켓 닫기
    }

    return nullptr;
}

int main() {
    signal(SIGINT, handle_signal); // Ctrl+C 시그널 처리

    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket < 0) {
        std::cerr << "Failed to create socket\n";
        return 1;
    }

    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(server_ip);
    server_addr.sin_port = htons(server_port);

    if (bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        std::cerr << "Bind failed\n";
        return 1;
    }

    if (listen(server_socket, 5) < 0) {
        std::cerr << "Listen failed\n";
        return 1;
    }

    std::cout << "Server is listening at " << server_ip << ":" << server_port << std::endl;

    // 스레드 풀 생성
    std::vector<pthread_t> threads(MAX_THREADS);
    for (int i = 0; i < MAX_THREADS; ++i) {
        pthread_create(&threads[i], nullptr, handle_client, nullptr);
    }

    // 클라이언트 연결 처리
    while (!stop) {
        int client_socket = accept(server_socket, NULL, NULL);
        if (client_socket < 0) {
            if (stop) break; // 종료 신호가 발생하면 루프 종료
            std::cerr << "Accept failed\n";
            continue;
        }

        // 클라이언트 소켓을 작업 큐에 추가
        pthread_mutex_lock(&queue_mutex);
        client_queue.push(client_socket);
        pthread_cond_signal(&queue_cond); // 대기 중인 스레드 중 하나를 깨움
        pthread_mutex_unlock(&queue_mutex);
    }

    // 서버 종료 처리
    for (pthread_t& thread : threads) {
        pthread_join(thread, nullptr);
    }

    close(server_socket);
    return 0;
}

