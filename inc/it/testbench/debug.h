#ifndef DEBUG_H_
#define DEBUG_H_

#include <iostream>

//#define DEBUG_PRINT_ENABLED   1

#if DEBUG_PRINT_ENABLED

/**
 * Define the whole set of debug and assert macros
 */

#define DEBUG(fmt) \
    (::std::cout <<__FILE__ <<":" <<__func__ <<":" <<__LINE__ <<"  " <<fmt <<::std::endl)
#define ASSERT_EQUAL(a, b) \
    DEBUG(( ((a) == (b)) ? "    PASS" : "    * FAIL *" ))
#define ASSERT_NOT_EQUAL(a, b) \
    DEBUG(( ((a) != (b)) ? "    PASS" : "    * FAIL *" ))
#define ASSERT_STRING_EQUAL(a, b) \
    DEBUG(( ((a).compare(b) == 0) ? "    PASS" : "    * FAIL *" ))
#define ASSERT_STRING_NOT_EQUAL(a, b) \
    DEBUG(( ((a).compare(b) != 0) ? "    PASS" : "    * FAIL *" ))

#else

/**
 * Debug and assert macros will be void
 */

#define DEBUG(fmt)
#define ASSERT_EQUAL(a, b)
#define ASSERT_NOT_EQUAL(a, b)
#define ASSERT_STRING_NOT_EQUAL(a, b)

#endif /* DEBUG_PRINT_ENABLED */

#endif /* DEBUG_H_ */
