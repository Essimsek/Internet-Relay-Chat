#pragma once

#include <iostream>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <poll.h>
#include <cstring>
#include <vector>
#include <unistd.h>
#include <limits.h>
#include <sstream>
#include <string>

#define MSGSTART 2
#define TEXTSTART 3
