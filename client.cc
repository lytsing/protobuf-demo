/*
 * Description:  test protobuf in client
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

#include <stdio.h>
#include <unistd.h>
#include <strings.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string>
#include <iostream>
#include "demo.people.pb.h"

#define HOST "localhost"
#define PORT 8000
#define MAXDATASIZE 4096

using namespace std;

int main(int argc, char ** argv) {
    int fd, numbytes;
    char buf[MAXDATASIZE];
    struct hostent *he;
    struct sockaddr_in server;

    if (argc != 2) {
        printf("Usage: %s \"COMMAND\"\n", argv[0]);
        exit(0);
    }

    he = gethostbyname(HOST);
    fd = socket(AF_INET, SOCK_STREAM, 0);
    bzero(&server, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    server.sin_addr = *((struct in_addr *)he->h_addr);

    connect(fd, (struct sockaddr *)&server, sizeof(struct sockaddr));

    send(fd, argv[1], 20, 0);

    numbytes = recv(fd, buf, MAXDATASIZE, 0);
    buf[numbytes] = '\0';
    cout << buf << endl;
    string data = buf;
    demo::People p;
    p.ParseFromString(data);
    cout << "People: "  << endl;
    cout << "Name: "    << p.name() << endl;
    cout << "ID: "      << p.id() << endl;
    cout << "Email: "   << p.email() << endl;

    close(fd);
    return 0;
}

