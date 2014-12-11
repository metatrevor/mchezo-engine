#ifndef CNETWORK_H
#define CNETWORK_H

#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include "Log.h"

/**
 * @brief The CNetwork class provides networking
 */

class CNetwork
{
public:
    CNetwork(std::string server_hostname, int server_port);

    void GetUpdateFromServer(int sockfd, char board[][3]);
    void PostUpdateFromClient(int move);
    void TakeTurn(int sockfd);
    void DrawBoard(char board[][3]);
    void WriteServerInt(int sockfd, int msg);
    int  ReceiveInt(int sockfd);
    void CleanUp();
    void Error(const char *msg);



    int Init();
    void ReceiveMsg(int sockfd, char *msg);
    int ConnectToServer();
    void NetworkLoop();
private:
    std::string m_server_host;
    int m_server_port;
    bool m_game_status;
    int m_client_id;
    int m_sockfd;
    char m_msg[4];
    char m_buffer[10];
    bool m_connection_status;
    struct sockaddr_in m_serv_addr;
    struct hostent *m_server_hptr;

    /**
     * @brief Connect to the game server
     * @return
     */
    void connectServer();


};

#endif // CNETWORK_H
