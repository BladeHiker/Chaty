#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <malloc.h>
#include <unistd.h>
#include <stdbool.h>
#include <time.h>
#include <pthread.h>
#include "user.h"
#include "client.h"
#include "commondata.h"
#include "messagequeue.h"
unsigned int G_TIMEOUT = 300;
unsigned int G_groupSize = 1024;
int G_serverFileDescriptor;

void *groupServer(void *pointer) {
    const unsigned int TIMEOUT = G_TIMEOUT;
    int serverFileDescriptor = G_serverFileDescriptor;
    ConnectionTable table = TableNew(G_groupSize);
    if (table == NULL) {
        exit(-1);
    }
    struct User userBuf;
    struct Message message;
    message.client.length = sizeof(struct sockaddr_in);
    MessageQueue queue = New_Queue();
    *((MessageQueue*)pointer) = queue;
    while (true) {
        if (Empty_Queue(queue)) {
            usleep(100000);
            continue;
        }
        message = Front_Queue(queue);
        Pop_Queue(queue);
        struct Client *client = TableGet(table, &message.client);
        if (client == NULL) {
            if (message.data.code == CONNECT) {
                strcpy(message.client.nickname, "Unnamed");
                message.client.time = time(NULL);
                message.client.status = UnLoggedIN;
                if (!TableSet(table, &message.client)) {
                    message.data.code = ERROR;
                    strcpy(message.data.message, "Server : This group is full");
                } else {
                    strcpy(message.data.message, "Server : Connect successfully");
                }
            } else {
                strcpy(message.data.message, "Server : You haven't connected yet");
            }

        } else {
            if (time(NULL) - client->time > TIMEOUT) {
                strcpy(message.data.message, "Server : Time out");
                TableErase(table, client);
            } else {
                client->time = time(NULL);
                if (message.data.code == CHAT) {
                    if (client->status == LoggedIN) {
                        sprintf(message.data.message, "Status : %s | NickName:%s", "Logged in", client->nickname);
                    } else {
                        sprintf(message.data.message, "Status : %s | NickName:%s", "Not logged in", client->nickname);
                    }
                    for (int i = 0; i < table->capacity; i++) {
                        if (table->clients[i] != NULL) {
                            if (time(NULL) - table->clients[i]->time > TIMEOUT) {
                                free(table->clients[i]);
                                table->clients[i] = NULL;
                                table->size--;
                                continue;
                            }
                            sendto(serverFileDescriptor, &message.data, sizeof(struct CommonData), 0,
                                   (struct sockaddr *) &table->clients[i]->address, table->clients[i]->length);
                        }
                    }
                    goto PRINT;
                } else if (message.data.code == RENAME) {
                    strcpy(TableGet(table, &message.client)->nickname, message.data.data);
                    sprintf(message.data.message, "Server : Set username (Name:%s) successfully", message.data.data);
                } else if (message.data.code == DISCONNECT) {
                    TableErase(table, &message.client);
                    strcpy(message.data.message, "Server : Disconnect successfully");
                } else if (message.data.code == LOGIN) {
                    if (GetUserByUserName(&userBuf, message.data.message) != -1) {
                        if (strcmp(userBuf.password, message.data.data) == 0) {
                            client->status = LoggedIN;
                            strcpy(message.data.message, "Server : Login successfully");
                        } else {
                            strcpy(message.data.message, "Server : Wrong password");
                        }
                    } else {
                        strcpy(message.data.message, "Server : None username");
                    }
                } else if (message.data.code == LOGOUT) {
                    client->status = UnLoggedIN;
                    strcpy(message.data.message, "Server : Logout successfully");
                } else if (message.data.code == REGISTER) {
                    strcpy(userBuf.username, message.data.message);
                    strcpy(userBuf.password, message.data.data);
                    if (GetUserByUserName(&userBuf, message.data.message) == -1) {
                        if (SetUserByPlace(&userBuf, GetUserCount())) {
                            strcpy(message.data.message, "Server : Register successfully");
                        } else {
                            strcpy(message.data.message, "Server : Register unsuccessfully");
                        }
                    } else {
                        strcpy(message.data.message, "Server : Duplicate username");
                    }
                } else if (message.data.code == UNREGISTER) {
                    long temp = GetUserByUserName(&userBuf, message.data.message);
                    if (temp == -1) {
                        strcpy(message.data.message, "Server : None username");
                    } else {
                        if (strcmp(userBuf.password, message.data.data) == 0) {
                            if (RemoveUserByPlace(temp) != -1) {
                                strcpy(message.data.message, "Server : Unregister successfully");
                            } else {
                                strcpy(message.data.message, "Server : Unregister unsuccessfully");
                            }
                        } else {
                            strcpy(message.data.message, "Server : Wrong password");
                        }
                    }
                }else if (message.data.code == EXIT) {
                    break;
                } else {
                    message.data.code = UNKNOWN;
                    strcpy(message.data.message, "Unknown");
                }
            }
        }
        strcpy(message.data.data, "");
        sendto(serverFileDescriptor, &message.data, sizeof(struct CommonData), 0,
               (struct sockaddr *) &message.client.address, message.client.length);
        PRINT:
        printf("thread: %lu\t",pthread_self());
        printf("%hhu.", *(char *) (&message.client.address.sin_addr.s_addr));
        printf("%hhu.", *((char *) (&message.client.address.sin_addr.s_addr) + 1));
        printf("%hhu.", *((char *) (&message.client.address.sin_addr.s_addr) + 2));
        printf("%hhu:", *((char *) (&message.client.address.sin_addr.s_addr) + 3));
        printf("%d", message.client.address.sin_port);
        printf("\t Code : %d\tGroup : %d\t", message.data.code, message.data.group);
        printf("size: %d\n", table->size);
    }
    Destroy_Queue(queue);
    TableDestroy(table);
    return NULL;
}
#include "messagequeue.h"
int main(int argc, char *argv[]) {
    unsigned int TIMEOUT = 300;
    unsigned int groupSize = 1024;
    unsigned int groupNumber = 1024;
    short SERVER_PORT = 9999;
    for (int i = 0; i < argc; i++) {
        if (argv[i][0] == '-') {
            if (strncmp(argv[i] + 1, "port", 4) == 0) {
                char *temp;
                SERVER_PORT = (short) strtol(argv[i] + 5, &temp, 10);
            } else if (strncmp(argv[i] + 1, "groupSize", 9) == 0) {
                char *temp;
                groupSize = (unsigned int) strtol(argv[i] + 10, &temp, 10);
            } else if (strncmp(argv[i] + 1, "groupNumber", 11) == 0) {
                char *temp;
                groupNumber = (unsigned int) strtol(argv[i] + 12, &temp, 10);
            } else if (strncmp(argv[i] + 1, "timeOut", 7) == 0) {
                char *temp;
                TIMEOUT = (int) strtol(argv[i] + 8, &temp, 10);
            }
        }
        puts(argv[i]);
    }

    struct sockaddr_in serverAddress;
    int serverFileDescriptor = socket(AF_INET, SOCK_DGRAM, 0); //AF_INET:IPV4;SOCK_DGRAM:UDP
    if (serverFileDescriptor < 0) {
        puts("Create socket fail!");
        return -1;
    }
    puts("Create socket successfully");
    memset(&serverAddress, 0, sizeof(struct sockaddr_in));
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);
    serverAddress.sin_port = htons(SERVER_PORT);
    if (bind(serverFileDescriptor, (struct sockaddr *) &serverAddress, sizeof(serverAddress)) < 0) {
        puts("Socket bind fail");
        close(serverFileDescriptor);
        return -2;
    }
    puts("Bind successfully");
    puts("Turn on successfully");
    MessageQueue queues[groupNumber];

    G_serverFileDescriptor = serverFileDescriptor;
    G_groupSize = groupSize;
    G_TIMEOUT = TIMEOUT;

    pthread_t pid[groupNumber];
    for (unsigned int i = 0; i < groupNumber; i++) {
        pthread_create(&pid[i], NULL, (void *(*)(void *)) groupServer, &queues[i]);
    }
    struct DataBuf {
        struct CommonData data;
        char others[1024];
    };
    struct Client clientBuf;
    struct DataBuf dataBuf;
    clientBuf.length = sizeof(clientBuf.address);
    while (true) {
        long int count = recvfrom(serverFileDescriptor, &dataBuf, sizeof(struct DataBuf), 0,
                                  (struct sockaddr *) &clientBuf.address, &clientBuf.length);
        if (count == -1) {
            puts("Receive data fail");
            break;
        } else if (count != sizeof(struct CommonData)) {
            continue;
        }
        if (dataBuf.data.group >= groupNumber) {
            strcpy(dataBuf.data.message, "Server : Wrong group");
            sendto(serverFileDescriptor, &dataBuf, sizeof(struct CommonData), 0,
                   (struct sockaddr *) &clientBuf.address, clientBuf.length);
            continue;
        }
        struct Message message;
        message.client = clientBuf;
        message.data = dataBuf.data;
        Push_Queue(queues[dataBuf.data.group],message);
    }
    puts("Shutdown server successfully");
    close(serverFileDescriptor);
    puts("Close socket successfully");
    return 0;
}