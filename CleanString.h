/* L I C E N S E * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *
 *  Copyright 2019 Michael Schaechinger
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/**
 * \author Michael Schaechinger
 * \date 2019
 * \file CleanString.h
 * \version 1.0
 */

#ifndef CLEANSTRING_H
#define CLEANSTRING_H

/** \brief Cleans up a given string.
 *
 * Removes leading and trailing blanks and every occurence of ascii control
 * character from a given string.
 *
 * \param str   non-const string to be cleaned
 *
 * \return  \arg 0:   function successfully executed
 *          \arg 1:   please check the error code by calling get_error()
 */
int clean_string               (char* str);

/** \brief Removes every occurence of a character from a given string.
 *
 * \param str       string to be modified
 * \param character character to be removed from the string
 *
 * \return  \arg 0:   function successfully executed
 *          \arg 1:   please check the error code by calling get_error()
 */
int remove_char                (char* str,
                                char  character);

/** \brief Removes every occurence of ascii control characters from a given
 *         string.
 *
 * \param str   string to be modified
 *
 * \return  \arg 0:   function successfully executed
 *          \arg 1:   please check the error code by calling get_error_message
 */
int remove_ascii_control_chars (char* str);

/** \brief Returns the error code if there was an error during the execution of
 *         one of the previous functions.
 *
 * \return Error code as defined in errno.h or NO_ERROR if there was no error
 */
int get_error                  ();

#endif /* CLEANSTRING_H */
