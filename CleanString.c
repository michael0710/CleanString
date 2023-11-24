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
 * \file CleanString.c
 * \version 1.0
 */
/* I N C L U D E S  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
#include <errno.h>

#include "CleanString.h"

/* D E F I N E S  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
#define NO_ERROR            0
#define ERROR_FLAG_HIGH     1
#define ERROR_FLAG_LOW      0

/* G L O B A L   V A R I A B L E D E F I N I T I O N S  * * * * * * * * * * * */
static int g_err_code = NO_ERROR;
static int g_err_flag = ERROR_FLAG_LOW;

/* F U N C T I O N D E C L A R A T I O N S  * * * * * * * * * * * * * * * * * */
/* -> see headerfile CleanString.h */

/* P R I V A T E   F U N C T I O N D E C L A R A T I O N S  * * * * * * * * * */
static void set_error_code (int err_code);

static void set_error_flag (int flag);

/* F U N C T I O N D E F I N I T I O N S  * * * * * * * * * * * * * * * * * * */
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
int clean_string (char* str)
{
    char* old_string = str;
    char* new_string = str;
    /* skip leading blanks */
    while ((*old_string != '\0')
            && ((*old_string <= 0x20) || (*old_string == 0x7F)))
    {
        old_string++;
    }
    while (*old_string != '\0')
    {
        if ((*old_string >= 0x20) && (*old_string <= 0x7E))
        {
            *new_string = *old_string;
            new_string++;
        }
        old_string++;
    }
    /* do also copy the null terminator after finishing the loop */
    *new_string = *old_string;
    new_string--;
    /* skip trailing blanks as long as the pointer newString points to a valid
    address */
    while (((*new_string <= 0x20) || (*new_string == 0x7F))
            && (new_string >= str))
    {
        new_string--;
    }
    new_string++;
    /* add the null terminator if it has not been done yet */
    if (*new_string)
    {
        *new_string = '\0';
    }
    return 0;
}

/** \brief Removes every occurence of a character from a given string.
 *
 * \param str       string to be modified
 * \param character character to be removed from the string
 *
 * \return  \arg 0:   function successfully executed
 *          \arg 1:   please check the error code by calling get_error()
 */
int remove_char (char* str,
                 char  character)
{
    /* return an error if someone tries to remove the null terminator */
    if (character == '\0')
    {
        /* Invalid argument */
        set_error_code(EINVAL);
        return 1;
    }

    char* old_string = str;
    char* new_string = str;
    while (*old_string != '\0')
    {
        /* copy all characters except the one to be removed */
        *new_string = *old_string;
        /* only go to the next character if the copied character was not one
           to be removed */
        new_string = new_string + (*old_string != character);
        old_string++;
    }
    /* copy null terminator */
    *new_string = *old_string;
    return 0;
}

/** \brief Removes every occurence of ascii control characters from a given
 *         string.
 *
 * \param str   string to be modified
 *
 * \return  \arg 0:   function successfully executed
 *          \arg 1:   please check the error code by calling get_error_message
 */
int remove_ascii_control_chars (char* str)
{
    char* old_string = str;
    char* new_string = str;

    while (*old_string != '\0')
    {
        /* copy characters only if it isn't a ascii control character */
        if (!((*old_string <= 0x1F) || (*old_string == 0x7F)))
        {
            *new_string = *old_string;
            new_string++;
        }
        old_string++;
    }
    /* copy null terminator */
    *new_string = *old_string;
    return 0;
}

/** \brief Returns the error code if there was an error during the execution of
 *         one of the previous functions.
 *
 * \return Error code as defined in errno.h or NO_ERROR if there was no error
 */
int get_error ()
{
    set_error_flag (ERROR_FLAG_LOW);
    int err_code = g_err_code;
    g_err_code = NO_ERROR;
    return err_code;
}

/* P R I V A T E   F U N C T I O N D E F I N I T I O N S  * * * * * * * * * * */
static inline void set_error_code (int err_code)
{
    set_error_flag (ERROR_FLAG_HIGH);
    g_err_code = err_code;
}

static inline void set_error_flag (int flag)
{
    g_err_flag = flag;
}
