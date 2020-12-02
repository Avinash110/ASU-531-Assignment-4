/*
 * Project members
 *  
 * Name: Ankit Rai        - 1217088301 
 * Name: Avinash Bhojwani - 1217145904
 * 
 *  
*/
#include <stdlib.h>
#include <stdio.h>
#include "msgs.h"


int id = 0;
semaphore_t sem;

/*
Assumption: We assume that the server is listening on port 0. Hence the first port is always dedicated for listening irrespective of the number of ports on the server
*/

#define SERVER_PORT 0

void sever(void)
{
    struct message *msg_receive;
    struct message *msg_send;

    while (1)
    {
        msg_receive = receive(SERVER_PORT);
        int reply_port = msg_receive->msgs[0];
        int client_id = msg_receive->msgs[1];
        printf("Sever \t Receive : processing request for client %d and will reply on port %d \n", client_id, reply_port);
        msg_send = (struct message *)malloc(sizeof(struct message));
        msg_send->msgs[0] = reply_port;
        msg_send->msgs[1] = msg_receive->msgs[1];
        for (int i = 2; i < 10; i++)
        {
            msg_send->msgs[i] = 0;
        }
        printf("Sever \t Send : sending reply on client port %d \n", reply_port);
        send(reply_port, msg_send);
        sleep(1);
    }
}

void client(void)
{
    int client_id;
    P(&sem);
    client_id = id++;
    V(&sem);
    int reply_port;
    struct message *msg_receive;
    struct message *msg_send;

    while (1)
    {
        reply_port = (client_id % 98) + 1;

        msg_send = (struct message *)malloc(sizeof(struct message));
        msg_send->msgs[0] = reply_port;
        msg_send->msgs[1] = client_id;
        for (int i = 2; i < 10; i++)
        {
            msg_send->msgs[i] = 0;
        }
        printf("\t\t\tClient %d Send : message on server port %d and waiting for response on port %d \n", client_id, SERVER_PORT, reply_port);
        send(SERVER_PORT, msg_send);
        msg_receive = receive(reply_port);
        printf("\t\t\tClient %d Receive : response on port %d\n", client_id, reply_port);
        printf("\t\t\tClient %d \tData received %d \n", client_id, msg_receive->msgs[1]);
        sleep(1);
    }
}

int main()
{
    ReadyQ = newQueue(ReadyQ);
    sem = CreateSem(1);
    for (int i = 0; i < 100; i++)
    {
        init_port(i);
    }
    start_thread(sever);
    printf("Server Thread started\n");
    printf("Sever listening on %d \n", SERVER_PORT);
    for (int i = 0; i < 20; i++)
    {
        printf("Client %d started\n",i);
        start_thread(client);
    }
    run();
    while (1)
    {

    }
}