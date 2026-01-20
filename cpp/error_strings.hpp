// This file was created on 25 Dec 2025.

#ifndef ERROR_STRINGS_HPP
#define ERROR_STRINGS_HPP

#include <cstdlib>
#include <cstdio>

/**
 * Each of the following is either
 * 1. A format string or
 * 2. A formula for format strings.
 *
 * Each of the following can be used as the first parameter of `printf()`.
 *
 * `ARR_ELEM` below stands for "array element".
 *
 * The leading "%s(): " corresponds to `__func__`.
 */
#define FORMAT_STRING___FATAL_ERROR___ARR_ELEM_IS_NULL(variable_name) ((void)variable_name, "%s(): Fatal error: `" #variable_name "[%d]` is NULL.\n")
#define FORMAT_STRING___FATAL_ERROR___VARIABLE_IS_NULL(variable_name) ((void)variable_name, "%s(): Fatal error: `" #variable_name "` is NULL.\n")
#define FORMAT_STRING___FATAL_ERROR___FUNCTION_FAILURE(function_name) ((void)function_name, "%s(): Fatal error: `" #function_name "()` failed.\n")
#define FORMAT_STRING___OTHER_ERROR___VARIABLE_IS_NULL(variable_name) ((void)variable_name, "%s(): Error: `" #variable_name "` is NULL.\n")
#define FORMAT_STRING___OTHER_ERROR___FUNCTION_FAILURE(function_name) ((void)function_name, "%s(): Error: `" #function_name "()` failed.\n")

/**
 * Each of the following is a call to only `printf()`.
 *
 * `ARR_ELEM` below stands for "array element".
 */
#define PRINTF___FATAL_ERROR___ARR_ELEM_IS_NULL(variable_name, index) printf(FORMAT_STRING___FATAL_ERROR___ARR_ELEM_IS_NULL(variable_name), __func__, index)
#define PRINTF___FATAL_ERROR___VARIABLE_IS_NULL(variable_name) printf(FORMAT_STRING___FATAL_ERROR___VARIABLE_IS_NULL(variable_name), __func__)
#define PRINTF___FATAL_ERROR___FUNCTION_FAILURE(function_name) printf(FORMAT_STRING___FATAL_ERROR___FUNCTION_FAILURE(function_name), __func__)
#define PRINTF___OTHER_ERROR___VARIABLE_IS_NULL(variable_name) printf(FORMAT_STRING___OTHER_ERROR___VARIABLE_IS_NULL(variable_name), __func__)
#define PRINTF___OTHER_ERROR___FUNCTION_FAILURE(function_name) printf(FORMAT_STRING___OTHER_ERROR___FUNCTION_FAILURE(function_name), __func__)

/**
 * Each of the following is comprised of
 * 1. A call to `printf()` then
 * 2. A call to `exit()`.
 *
 * `ARR_ELEM` below stands for "array element".
 */
#define PRINTF_EXIT___FATAL_ERROR___ARR_ELEM_IS_NULL(variable_name, index) (PRINTF___FATAL_ERROR___ARR_ELEM_IS_NULL(variable_name, index), exit(EXIT_FAILURE))
#define PRINTF_EXIT___FATAL_ERROR___VARIABLE_IS_NULL(variable_name) (PRINTF___FATAL_ERROR___VARIABLE_IS_NULL(variable_name), exit(EXIT_FAILURE))
#define PRINTF_EXIT___FATAL_ERROR___FUNCTION_FAILURE(function_name) (PRINTF___FATAL_ERROR___FUNCTION_FAILURE(function_name), exit(EXIT_FAILURE))

#endif // ERROR_STRINGS_HPP
