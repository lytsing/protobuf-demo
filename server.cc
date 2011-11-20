/*
 * Description:  test protobuf in server
 *
 * Copyright (C) 2011 lytsing.org
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

// refer to: http://hideto.iteye.com/blog/445848

#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string>
#include <iostream>

#include "./demo.people.pb.h"

#define PORT 8000
#define MAXDATASIZE 4096
#define BACKLOG 10

using std::cout;
using std::endl;
using std::string;

int main(int argc, char** argv) {
    int listenfd;
    int connectfd;
    int numbytes;
    char buf[MAXDATASIZE];
    struct sockaddr_in server;
    struct sockaddr_in client;
    socklen_t sin_size;

    listenfd = socket(AF_INET, SOCK_STREAM, 0);

    int opt = SO_REUSEADDR;
    setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    bzero(&server, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    server.sin_addr.s_addr = htonl(INADDR_ANY);

    bind(listenfd, (struct sockaddr *)&server, sizeof(struct sockaddr));

    listen(listenfd, BACKLOG);

    while (1) {
        sin_size = sizeof(struct sockaddr_in);

        connectfd = accept(listenfd, (struct sockaddr *)&client, &sin_size);

        numbytes = recv(connectfd, buf, MAXDATASIZE, 0);
        buf[numbytes] = '\0';
        string a = buf;
        cout << "You got a message from " << inet_ntoa(client.sin_addr) << endl;
        // cout << "Client Message: " << a << endl;

        // Receive  msg from clients
        demo::People p;
        p.ParseFromString(a);
        cout << "People:\t" << endl;
        cout << "Name:\t" << p.name() << endl;
        cout << "ID:\t" << p.id() << endl;
        cout << "Email:\t" << p.email() << endl;

        // Send msg to clients
        string data;
        demo::People to;
        to.set_name("Lysting Huang");
        to.set_id(123);
        to.set_email("lytsing@hotmail.com");
        to.SerializeToString(&data);
        char bts[data.length()];
        sprintf(bts, "%s", data.c_str());
        send(connectfd, bts, sizeof(bts), 0);

        close(connectfd);
    }

    close(listenfd);

    return 0;
}

