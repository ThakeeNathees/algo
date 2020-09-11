#pragma once

#include <stdio.h>
#include <time.h>
#include<io.h>
#include <fcntl.h>

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

#include <algorithm>
#include <chrono>
#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include <map>
#include <functional>
#include <unordered_map>

#define print(x) std::cout << (x) << std::endl
