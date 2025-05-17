#include"part2.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>
#include<string.h>
#include<math.h>
#include<iostream>
int main()
{
    int sockfd = socket(
        AF_INET,
        SOCK_STREAM,
        0);
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080);
    server_addr.sin_addr.s_addr = INADDR_ANY;
    bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr));
    listen(sockfd, 5);
    struct sockaddr_in client_addr;
    socklen_t client_addr_len = sizeof(client_addr);
    while(true){
    int client_fd = accept(
        sockfd,
        (struct sockaddr *)&client_addr,
        &client_addr_len);
    
    // 接收数据
    uint32_t network_size1;
    recv(client_fd, &network_size1, sizeof(network_size1), 0);
    size_t data_size1 = ntohl(network_size1);
    std::cout << "data size:" << data_size1 << std::endl;

    std::vector<float> buffer(data_size1 / sizeof(float));
    recv(client_fd, buffer.data(), data_size1, 0);
    amatrix<float> received_matrix(1, 784);
    memcpy(received_matrix.Matrix[0].data(), buffer.data(), data_size1);
    std::string a;
    a = "mnist-fc";
    modelbase<float> *m1 = read<float>(a);
    if (!m1)
    {
        std::cerr << "Error: read<float>(a) returned nullptr!" << std::endl;
        return -1;
    }
    std::vector<float> output = m1->forward(received_matrix);

    // std::vector<float> h;
    std::cout << "calculating" << std::endl;

    // 发送数据
    float *data_ptr = output.data();
    size_t data_size = output.size() * sizeof(float);
    uint32_t network_size = htonl(data_size);
    send(client_fd, &network_size, sizeof(network_size), 0);
    send(client_fd, data_ptr, data_size, 0);
    std::cout << "sended" << std::endl;
    close(client_fd);
    close(sockfd);
}
    return 0;
}
