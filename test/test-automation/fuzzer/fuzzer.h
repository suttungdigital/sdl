/*
  Copyright (C) 2011 Markus Kauppila <markus.kauppila@gmail.com>

  This software is provided 'as-is', without any express or implied
  warranty.  In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgment in the product documentation would be
     appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.
*/

#ifndef _FUZZER_H
#define _FUZZER_H

#include <SDL/SDL_stdinc.h>

#include "utl_crc32.h"
#include "utl_md5.h"
#include "utl_random.h"


/*!
 * Inits the fuzzer for a test
 */
void InitFuzzer(Uint64 execKey);


/*!
 * Deinits the fuzzer (for a test)
 */
void DeinitFuzzer();


/*!
 * Returns a random integer
 *
 * \returns Generated integer
 */
Sint32 RandomInteger();


/*!
 * Returns a random positive integer
 *
 * \returns Generated integer
 */
Uint32 RandomPositiveInteger();


/*!
 * Returns a random boundary value for Uint8 within the given boundaries.
 * Boundaries are inclusive, see the usage examples below. If validDomain
 * is true, the function will only return valid boundaries, otherwise non-valid
 * boundaries are also possible.
 * If boundary1 > boundary2, the values are swapped
 *
 * Usage examples:
 * RandomUint8BoundaryValue(10, 20, SDL_TRUE) returns 10, 11, 19 or 20
 * RandomUint8BoundaryValue(1, 20, SDL_FALSE) returns 0 or 21
 * RandomUint8BoundaryValue(0, 99, SDL_FALSE) returns 100
 * RandomUint8BoundaryValue(0, 255, SDL_FALSE) returns -1 (== error value)
 *
 * \param boundary1 Lower boundary limit
 * \param boundary2 Upper boundary limit
 * \param validDomain Should the generated boundary be valid or not?
 *
 * \returns Boundary value in given range or error value (-1)
 */
Uint8 RandomUint8BoundaryValue(Uint8 boundary1, Uint8 boundary2, SDL_bool validDomain);

/*!
 * Returns a random boundary value for Uint16 within the given boundaries.
 * Boundaries are inclusive, see the usage examples below. If validDomain
 * is true, the function will only return valid boundaries, otherwise non-valid
 * boundaries are also possible.
 * If boundary1 > boundary2, the values are swapped
 *
 * Usage examples:
 * RandomUint16BoundaryValue(10, 20, SDL_TRUE) returns 10, 11, 19 or 20
 * RandomUint16BoundaryValue(1, 20, SDL_FALSE) returns 0 or 21
 * RandomUint16BoundaryValue(0, 99, SDL_FALSE) returns 100
 * RandomUint16BoundaryValue(0, 0xFFFF, SDL_FALSE) returns -1 (== error value)
 *
 * \param boundary1 Lower boundary limit
 * \param boundary2 Upper boundary limit
 * \param validDomain Should the generated boundary be valid or not?
 *
 * \returns Boundary value in given range or error value (-1)
 */
Uint16 RandomUint16BoundaryValue(Uint16 boundary1, Uint16 boundary2, SDL_bool validDomain);

/*!
 * Returns a random boundary value for Uint32 within the given boundaries.
 * Boundaries are inclusive, see the usage examples below. If validDomain
 * is true, the function will only return valid boundaries, otherwise non-valid
 * boundaries are also possible.
 * If boundary1 > boundary2, the values are swapped
 *
 * Usage examples:
 * RandomUint32BoundaryValue(10, 20, SDL_TRUE) returns 10, 11, 19 or 20
 * RandomUint32BoundaryValue(1, 20, SDL_FALSE) returns 0 or 21
 * RandomUint32BoundaryValue(0, 99, SDL_FALSE) returns 100
 * RandomUint32BoundaryValue(0, 0xFFFFFFFF, SDL_FALSE) returns -1 (== error value)
 *
 * \param boundary1 Lower boundary limit
 * \param boundary2 Upper boundary limit
 * \param validDomain Should the generated boundary be valid or not?
 *
 * \returns Boundary value in given range or error value (-1)
 */
Uint32 RandomUint32BoundaryValue(Uint32 boundary1, Uint32 boundary2, SDL_bool validDomain);

/*!
 * Returns a random boundary value for Uint64 within the given boundaries.
 * Boundaries are inclusive, see the usage examples below. If validDomain
 * is true, the function will only return valid boundaries, otherwise non-valid
 * boundaries are also possible.
 * If boundary1 > boundary2, the values are swapped
 *
 * Usage examples:
 * RandomUint64BoundaryValue(10, 20, SDL_TRUE) returns 10, 11, 19 or 20
 * RandomUint64BoundaryValue(1, 20, SDL_FALSE) returns 0 or 21
 * RandomUint64BoundaryValue(0, 99, SDL_FALSE) returns 100
 * RandomUint64BoundaryValue(0, 0xFFFFFFFFFFFFFFFF, SDL_FALSE) returns -1 (== error value)
 *
 * \param boundary1 Lower boundary limit
 * \param boundary2 Upper boundary limit
 * \param validDomain Should the generated boundary be valid or not?
 *
 * \returns Boundary value in given range or error value (-1)
 */
Uint64 RandomUint64BoundaryValue(Uint64 boundary1, Uint64 boundary2, SDL_bool validDomain);

/*!
 * Returns random Sint8 boundary value.
 *
 * Note: not implemented.
 */
Sint8 RandomSint8BoundaryValue();


/*!
 * Returns integer in range [min, max] (inclusive).
 * Min and max values can be negative values.
 * If Max in smaller tham min, then the values are swapped.
 * Min and max are the same value, that value will be returned.
 *
 * \returns Generated integer
 */
Sint32 RandomIntegerInRange(Sint32 min, Sint32 max);


/*!
 * Generates random null-terminated string. The maximum length for
 * the string is 255 characters and it can contain ASCII characters
 * from 1 to 127.
 *
 * Note: Returned string needs to be deallocated.
 *
 * \returns newly allocated random string
 */
char *RandomAsciiString();


/*!
 * Generates random null-terminated string. The maximum length for
 * the string is defined by maxLenght parameter.
 * String can contain ASCII characters from 1 to 127.
 *
 * Note: Returned string needs to be deallocated.
 *
 * \param maxLength Maximum length of the generated string
 *
 * \returns newly allocated random string
 */
char *RandomAsciiStringWithMaximumLength(int maxLength);


/*!
 * Generates execution key (used for random seed) for a test
 *
 * \param runSeed Seed of the harness
 * \param suiteName Test suite name
 * \param testName Test name
 * \param iteration Number of test iteration
 *
 * \return Generated execution key as blob of 16 bytes. It needs be deallocated.
 * 			On error, returns NULL.
 */
Uint64 GenerateExecKey(char *runSeed, char *suiteName, char *testName, int interationNumber);


#endif
