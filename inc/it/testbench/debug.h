#ifndef DEBUG_H_
#define DEBUG_H_

#include <iostream>

// $Id$
/**
 * @file debug.h
 * This module defines all the debugging macro used in the code
 *
 * @brief

 *
 * @author Paolo Maresca <plo.maresca@gmail.com>
 * @version 0.1
 */
// $Log$

///  Single line comment for dOxygen.

/// Macro for Data package/component

#define DEBUG_PRINT_ENABLED   1

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


///

#define DATA_DEBUG_ENABLED   1

#if DATA_DEBUG_ENABLED
#   define DATA_INFO(msg) do { cout << "[" << __FILE__ << "]::" << "[" << __func__ << "]::[" << __LINE__ << "]::" << msg << endl; } while(0)
#   define DATA_INFO_VAL(msg,i) do { cout << "[" << __FILE__ << "]::" << "[" << __func__ << "]::[" << __LINE__ << "]::" << msg << "|-->[" << i << "]" << endl; } while(0)
#   define DATA_EQ(msg,a,b) do { cout << "[" << __FILE__ << "]::" << "[" << __func__ << "]::[" << __LINE__ << "]::(" << msg << ") - [EQUAL]" << endl; } while(0)
#   define DATA_NEQ(msg,a,b) do { cout << "[" << __FILE__ << "]::" << "[" << __func__ << "]::[" << __LINE__ << "]::(" << msg << ") - [NOT EQUAL]" << endl; } while(0)
#else
#   define DATA_INFO(fmt) do {} while(0)
#   define DATA_INFO_VAL(msg,i) do {} while(0)
#   define DATA_EQ(msg,a,b) do {} while(0)
#   define DATA_NEQ(msg,a,b) do {} while(0)
#endif

/// Macro for Tests

#define TEST_DEBUG 1

#ifdef TEST_DEBUG
#  define TEST_EQ(i,t,f,d,a,b) do {cout << "===" << endl << i << ".["t << "]::[" << f << "]::'" << d << "'" << endl << " R--->[" << (((a) == (b))?"PASS":"FAIL") << "]" << endl << "=== " << endl;} while (0)
#  define TEST_NEQ(i,t,f,d,a,b) do {cout << "===" << endl << i << ".["t << "]::[" << f << "]::'" << d << "'" << endl << " R--->[" << (((a) != (b))?"PASS":"FAIL") << "]" << endl << "=== " << endl;} while (0)
#else
#  define TEST_EQ(i,t,f,d,a,b) do {} while (0)
#  define TEST_NEQ(i,t,f,d,a,b) do {} while (0)
#endif



#endif /* DEBUG_H_ */
