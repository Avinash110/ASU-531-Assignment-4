#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sem.h"

struct message
{
    int msgs[10];
};

struct port
{
    struct message *message_queue;
    int startptr;
    int endptr;
    semaphore_t port_full, port_empty, port_mutex;
};

struct port ports[100];

void init_port(int index)
{
    int msg_queue_size = 10;
    ports[index].startptr = 0;
    ports[index].endptr = 0;
    ports[index].message_queue = (struct message *)malloc(msg_queue_size * sizeof(struct message));
    ports[index].port_full = CreateSem(msg_queue_size);
    ports[index].port_empty = CreateSem(0);
    ports[index].port_mutex = CreateSem(1);
}

void send(int portnumber, const struct message *sending_msg)
{
    P(&(ports[portnumber].port_full));
    P(&(ports[portnumber].port_mutex));
    ports[portnumber].message_queue[ports[portnumber].endptr] = *sending_msg;
    ports[portnumber].endptr = (ports[portnumber].endptr + 1) % 10;
    V(&(ports[portnumber].port_mutex));
    V(&(ports[portnumber].port_empty));
}

struct message *receive(int portnumber)
{
    struct message *recv_msg;
    recv_msg = (struct message *)malloc(sizeof(struct message));
    P(&ports[portnumber].port_empty);
    P(&ports[portnumber].port_mutex);
    struct message *curr_msg = &(ports[portnumber].message_queue[ports[portnumber].startptr]);
    memcpy(recv_msg->msgs, curr_msg->msgs, sizeof(curr_msg->msgs));
    ports[portnumber].startptr = (ports[portnumber].startptr + 1) % 10;
    V(&ports[portnumber].port_mutex);
    V(&ports[portnumber].port_full);
    return recv_msg;
}