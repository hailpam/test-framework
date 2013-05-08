#ifndef DEBUG_H_
#define DEBUG_H_

#include <iostream>

//#define DEBUG_PRINT_ENABLED   1

#if DEBUG_PRINT_ENABLED
#define DEBUG(fmt) (::std::cout <<fmt <<::std::endl)
#else
#define DEBUG(fmt)
#endif

#endif /* DEBUG_H_ */
