/*****************************************************************************

  The following code is derived, directly or indirectly, from the SystemC
  source code Copyright (c) 1996-2002 by all Contributors.
  All Rights reserved.

  The contents of this file are subject to the restrictions and limitations
  set forth in the SystemC Open Source License Version 2.3 (the "License");
  You may not use this file except in compliance with such restrictions and
  limitations. You may obtain instructions on how to receive a copy of the
  License at http://www.systemc.org/. Software distributed by Contributors
  under the License is distributed on an "AS IS" basis, WITHOUT WARRANTY OF
  ANY KIND, either express or implied. See the License for the specific
  language governing rights and limitations under the License.

 *****************************************************************************/

/*****************************************************************************

  scv_config.h

  Original Authors (Cadence Design Systems, Inc):
  Norris Ip, Dean Shea, John Rose, Jasvinder Singh, William Paulsen,
  John Pierce, Rachida Kebichi, Ted Elkind, David Bailey
  2002-09-23

 *****************************************************************************/

/*****************************************************************************

  MODIFICATION LOG - modifiers, enter your name, affiliation, date and
  changes you are making here.

      Name, Affiliation, Date:
  Description of Modification:

 *****************************************************************************/

#include "scv/scv_config.h"

#ifndef _MSC_VER
#include <sys/times.h>
#endif

#include <string.h>

#ifdef __linux__
# include <sys/time.h>
#else 
#include <time.h>
#endif

extern unsigned long long _scv_get_global_seed(void);

unsigned long long
_scv_default_global_init_seed(unsigned long job_number)
{
#ifdef _MSC_VER
  __time64_t ltime_sec;
  _time64( &ltime_sec );
  unsigned __int64 ltime_usec = 0;
  long i = 6000000L;
  unsigned int clk;
  clock_t start, finish;

  // measure the duration of an event
  start = clock();
  while( i-- ) ;
  finish = clock();
  clk = finish - start;

  // select a "random" seed
  unsigned __int64 seed
    = ((unsigned long)(ltime_sec^ltime_usec^clk^job_number) * 654435769) >> 1;
#else
  // get time of date
  struct timeval tp;
  struct timezone dummy1;
  gettimeofday(&tp, &dummy1);

  // get system time
  struct tms dummy2;
  clock_t clk;
  clk = times(&dummy2);

  // select a "random" seed
  unsigned long long seed
    = ((unsigned long)(tp.tv_sec^tp.tv_usec^clk^job_number) * 654435769) >> 1;
#endif

  if (seed==0) seed = 46831694;
  return seed;
}

unsigned long long 
_scv_get_seed_from_name(const char * name, unsigned inst_num)
{
  unsigned long long seed = 0;

  if (name) {
    for (unsigned i=0;i < strlen(name); i++) {
      if (name[i] != 0) {
        seed += name[i];
      }
    }
  } else {
    seed = 1;
  }

  seed = ((unsigned long) ((_scv_get_global_seed() * seed) + 
            inst_num * 1023 ) * 654435769) >> 1;
 
  if (seed==0) seed = 46831694;
  return seed;
}

