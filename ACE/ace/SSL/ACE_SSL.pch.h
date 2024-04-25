#pragma once

#ifdef _WIN32
#  define STRICT
#  define WIN32_LEAN_AND_MEAN      // Exclude rarely-used stuff from Windows headers
#  include <windows.h>
#  include <winnt.h>
#  include <WinSock2.h>
#endif

#include <cstdint>
#include <cstdlib>
#include <cstdio>

#ifdef _MSC_VER
#  include <xutility>
#endif
#include <utility>
#include <memory>
#include <string>
#include <sstream>
#include <ostream>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <array>
#include <vector>
#include <exception>
#include <stdexcept>
#include <functional>
#include <istream>
#include <limits>
#include <list>
#include <map>
#include <mutex>
#include <set>
#include <thread>
#include <tuple>
#include <unordered_map>
