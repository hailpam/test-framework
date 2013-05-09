#ifndef DEBUG_H_
#define DEBUG_H_

#include <iostream>

//#define DEBUG_PRINT_ENABLED   1

#if DEBUG_PRINT_ENABLED
#define DEBUG(fmt) \
    (::std::cout <<__FILE__ <<":" <<__func__ <<":" <<__LINE__ <<"  " <<fmt <<::std::endl)
#else
#define DEBUG(fmt)
#endif /* DEBUG_PRINT_ENABLED */

/**
 * Define the whole set of print and assert macros
 */
#define PRINT(fmt) \
    (::std::cout <<fmt <<::std::endl)
#define ASSERT_EQUAL(a, b) \
    PRINT(( ((a) == (b)) ? "    PASS" : "    * FAIL *" ))
#define ASSERT_NOT_EQUAL(a, b) \
    PRINT(( ((a) != (b)) ? "    PASS" : "    * FAIL *" ))
#define ASSERT_STRING_EQUAL(a, b) \
    PRINT(( ((a).compare(b) == 0) ? "    PASS" : "    * FAIL *" ))
#define ASSERT_STRING_NOT_EQUAL(a, b) \
    PRINT(( ((a).compare(b) != 0) ? "    PASS" : "    * FAIL *" ))


#endif /* DEBUG_H_ */
