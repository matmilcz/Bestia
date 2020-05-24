#pragma once

#ifdef _DEBUG
	#include <iostream>
	#define LOG(x) do { std::cout << x; } while (0)
#else
	#define LOG(x)
#endif