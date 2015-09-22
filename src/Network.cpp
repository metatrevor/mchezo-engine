#include "Network.h"

#define DEBUG 1

char m_board[3][3] = {{' ', ' ', ' '}, /* Game board */
                      {' ', ' ', ' '},
                      {' ', ' ', ' '}};


CNetwork::CNetwork(std::string server_hostname, int server_port)
        : m_server_host(server_hostname), m_server_port(server_port), m_game_status(false)
{
}

void CNetwork::Error(const char *msg)
{
#ifdef DEBUG
    perror(msg);
#else
    printf("Either the server shut down or the other player disconnected.\nGame over.\n");
#endif

    exit(0);
}

/*
 * Socket Read Functions
 */

/* Reads a message from the serve196.201.229.49   r socket. */
void CNetwork::ReceiveMsg(int m_sockfd, char *msg)
{
    /* All messages are 3 bytes. */
    memset(msg, 0, 4);
    Log::Info("Begin read wait");
    int n = read(m_sockfd, msg, 3);
    Log::Info("End read wait");
    if (n < 0 || n != 3) /* Not what we were expecting. Server got killed or the other client disconnected. */
        Error("ERROR reading message from server socket.");

#ifdef DEBUG
    printf("[DEBUG] Received message: %s\n", msg);
#endif
}

/* Reads an int from the server socket. */
int CNetwork::ReceiveInt(int m_sockfd)
{
    int msg = 0;
    int n = read(m_sockfd, &msg, sizeof(int));

    if (n < 0 || n != sizeof(int))
        Error("ERROR reading int from server socket");

#ifdef DEBUG
    printf("[DEBUG] Received int: %d\n", msg);
#endif

    return msg;
}

/*
 * Socket Write Functions
 */

/* Writes an int to the server socket. */
void CNetwork::WriteServerInt(int m_sockfd, int msg)
{
    int n = write(m_sockfd, &msg, sizeof(int));
    if (n < 0)
        Error("ERROR writing int to server socket");

#ifdef DEBUG
    printf("[DEBUG] Wrote int to server: %d\n", msg);
#endif
}

/*
 * Connect Functions
 */

/* Sets up the connection to the server. */
int CNetwork::ConnectToServer()
{
    /* Get a socket. */
    int m_sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (m_sockfd < 0)
        Error("ERROR opening socket for server.");

    /* Get the address of the server. */
    m_server_hptr = gethostbyname(m_server_host.c_str());

    if (m_server_hptr == NULL) {
        fprintf(stderr, "ERROR, no such host\n");
        exit(0);
    }

    /* Zero out memory for server info. */
    memset(&m_serv_addr, 0, sizeof(m_serv_addr));

    /* Set up the server info. */
    m_serv_addr.sin_family = AF_INET;
    memcpy(m_server_hptr->h_addr, &m_serv_addr.sin_addr.s_addr, m_server_hptr->h_length);
    m_serv_addr.sin_port = htons(m_server_port);

    /* Make the connection. */
    if (connect(m_sockfd, (struct sockaddr *) &m_serv_addr, sizeof(m_serv_addr)) < 0)
        Error("ERROR connecting to server");

#ifdef DEBUG
    printf("[DEBUG] Connected to server.\n");
#endif

    return m_sockfd;
}

/*
 * Game Functions
 */

/* Draws the game board to stdout. */
void CNetwork::DrawBoard(char board[][3])
{
    printf(" %c | %c | %c \n", board[0][0], board[0][1], board[0][2]);
    printf("-----------\n");
    printf(" %c | %c | %c \n", board[1][0], board[1][1], board[1][2]);
    printf("-----------\n");
    printf(" %c | %c | %c \n", board[2][0], board[2][1], board[2][2]);
}

/* Get's the players turn and sends it to the server. */
void CNetwork::TakeTurn(int m_sockfd)
{
    char buffer[10];

    while (1) { /* Ask until we receive. */
        printf("Enter 0-8 to make a move, or 9 for number of active players: ");
        fgets(buffer, 10, stdin);
        int move = buffer[0] - '0';
        if (move <= 9 && move >= 0) {
            printf("\n");
            /* Send players move to the server. */
            WriteServerInt(m_sockfd, move);
            break;
        }
        else
            printf("\nInvalid input. Try again.\n");
    }
}

/* Gets a board update from the server. */
void CNetwork::GetUpdateFromServer(int m_sockfd, char board[][3])
{
    /* Get the update. */
    int player_id = ReceiveInt(m_sockfd);
    int move = ReceiveInt(m_sockfd);

    /* Update the game board. */
    board[move / 3][move % 3] = player_id ? 'X' : 'O';
}

void CNetwork::PostUpdateFromClient(int move)
{
    Log::Info("After move : id " + Log::IntToString(move));
}

/*
 * Main Program
 */

int CNetwork::Init()
{
    /* Connect to the server. */
    m_sockfd = ConnectToServer();

    /* The client ID is the first thing we receive after connecting. */
    int id = ReceiveInt(m_sockfd);

#ifdef DEBUG
    printf("[DEBUG] Client ID: %d\n", id);
#endif

    printf("Tic-Tac-Toe\n------------\n");

    /*
     *
     * Wait for the game to start.
     */

    ReceiveMsg(m_sockfd, m_msg);
    Log::Info(m_msg);
    Log::Info("strcmp value");
    Log::Info(Log::IntToString(strcmp(m_msg, "SRT")));
    if (strcmp(m_msg, "HLD") == 0) //The server is waiting on a second client
        printf("Waiting for a second player...\n");

    /* The game has begun. */
    printf("Game on!\n");
    printf("Your are %c's\n", id ? 'X' : 'O');
    DrawBoard(m_board);
}

void CNetwork::NetworkLoop()
{
    if (m_game_status == false)
        Init();

    ReceiveMsg(m_sockfd, m_msg);

    if (!strcmp(m_msg, "TRN")) { /* Take a turn. */
        printf("Your move...\n");
        TakeTurn(m_sockfd);
    }
    else if (!strcmp(m_msg,
                     "INV")) { /* Move was invalid. Note that a "TRN" message will always follow an "INV" message, so we will end up at the above case in the next iteration. */
        printf("That position has already been played. Try again.\n");
    }
    else if (!strcmp(m_msg,
                     "CNT")) { /* Server is sending the number of active players. Note that a "TRN" message will always follow a "CNT" message. */
        int num_players = ReceiveInt(m_sockfd);
        printf("There are currently %d active players.\n", num_players);
    }
    else if (!strcmp(m_msg, "UPD")) { /* Server is sending a game board update. */
        GetUpdateFromServer(m_sockfd, m_board);
        DrawBoard(m_board);
    }
    else if (!strcmp(m_msg, "WAT")) { /* Wait for other player to take a turn. */
        printf("Waiting for other players move...\n");
    }
    else if (!strcmp(m_msg, "WIN")) { /* Winner. */
        printf("You win!\n");
        CleanUp();
    }
    else if (!strcmp(m_msg, "LSE")) { /* Loser. */
        printf("You lost.\n");
        CleanUp();
    }
    else if (!strcmp(m_msg, "DRW")) { /* Game is a draw. */
        printf("Draw.\n");
        CleanUp();
    }
    else /* Weird... */
        Error("Unknown message.");
}


void CNetwork::CleanUp()
{

    printf("Game over.\n");

    /* Close server socket and exit. */
    close(m_sockfd);
}

