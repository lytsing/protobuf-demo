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
#include "./demo.people.pb.h"

#define HOSTNAME "localhost"
#define PORT 8000
#define MAXDATASIZE 4096

using std::cout;
using std::endl;
using std::string;

int main(int argc, char** argv) {
    int fd;
    int numbytes;
    char buf[MAXDATASIZE];
    struct hostent *he;
    struct sockaddr_in server;

    he = gethostbyname(HOSTNAME);
    fd = socket(AF_INET, SOCK_STREAM, 0);
    bzero(&server, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    server.sin_addr = *((struct in_addr *)he->h_addr);

    connect(fd, (struct sockaddr *)&server, sizeof(struct sockaddr));

    string msg;
    demo::People to;
    to.set_name("violet");
    to.set_email("violet@gmail.com");
    to.set_id(1002);
    to.SerializeToString(&msg);
    sprintf(buf, "%s", msg.c_str());
    send(fd, buf, sizeof(buf), 0);

    numbytes = recv(fd, buf, MAXDATASIZE, 0);
    buf[numbytes] = '\0';
    string data = buf;
    demo::People p;
    p.ParseFromString(data);
    cout << "People:\t"  << endl;
    cout << "Name:\t"    << p.name() << endl;
    cout << "ID:\t"      << p.id() << endl;
    cout << "Email:\t"   << p.email() << endl;

    close(fd);
    return 0;
}

