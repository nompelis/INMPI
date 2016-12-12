/**************************************************************************
 Copyright (c) 2016, Ioannis Nompelis
 All rights reserved.

 Redistribution and use in source and binary forms, with or without any
 modification, are permitted provided that the following conditions are met:
 1. Redistributions of source code must retain the above copyright
    notice, this list of conditions and the following disclaimer.
 2. Redistributions in binary form must reproduce the above copyright
    notice, this list of conditions and the following disclaimer in the
    documentation and/or other materials provided with the distribution.
 3. All advertising materials mentioning features or use of this software
    must display the following acknowledgement:
    "This product includes software developed by Ioannis Nompelis."
 4. Neither the name of Ioannis Nompelis and his partners/affiliates nor the
    names of other contributors may be used to endorse or promote products
    derived from this software without specific prior written permission.
 5. Redistributions or use of source code and binary forms for profit must
    have written permission of the copyright holder.
 
 THIS SOFTWARE IS PROVIDED BY IOANNIS NOMPELIS ''AS IS'' AND ANY
 EXPRESSED OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 DISCLAIMED. IN NO EVENT SHALL IOANNIS NOMPELIS BE LIABLE FOR ANY
 DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 **************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <unistd.h>
#include <sched.h>
#include <sys/prctl.h>

#include "inmpi_sema.h"

static struct my_semaphore _0x9000001 = { 0,                                            -1,                                            -1,                                            MPI_COMM_NULL,                                            0 };int inMPI_DPsemaphore_Request( long *inum ){   int _0x0000101 = 1;   if( _0x9000001._0x0001111 == MPI_COMM_NULL ) {      if( _0x9000001._0x0000011 > 0 )      printf("Call to request from an un-instantiated distributed-parallel semaphore\n");      return(1);   }if( _0x9000001._0x0000011 == 2 ){int _0x0010001;MPI_Comm_rank( _0x9000001._0x0001111, &_0x0010001 );printf("Trying to get from a semaphore (%d)\n",_0x0010001);fflush(stdout);}   MPI_Send( &_0x0000101, 1, MPI_INT, _0x9000001._0x0000110, 9999,             _0x9000001._0x0001111 );   MPI_Recv( inum, 1, MPI_LONG, _0x9000001._0x0000110, 8888,             _0x9000001._0x0001111, MPI_STATUS_IGNORE );if( _0x9000001._0x0000011 == 2 ){int _0x0010001;MPI_Comm_rank( _0x9000001._0x0001111, &_0x0010001 );printf("Got from semaphore %ld (%d)\n",*inum,_0x0010001);fflush(stdout);}   if( *inum < 0 ) return(1);   return(0);}int inmpi_dpsemaphore_request_( long *inum, int *_0x0000111 ){   *_0x0000111 = inMPI_DPsemaphore_Request( inum );   return( *_0x0000111 );}int inMPI_DPsemaphore_SetNumber( long num ){   int _0x0010001;   if( _0x9000001._0x0001111 == MPI_COMM_NULL ) {      printf("Call to set total count to an un-instantiated distributed-parallel semaphore\n");      return(1);   }   MPI_Comm_rank( _0x9000001._0x0001111, &_0x0010001 );   if( _0x0010001 != _0x9000001._0x0000110 ) {      printf("Only the master process can (re)set the semaphore's count\n");      printf("Process attempting was: %d \n", _0x0010001 );      return(2);   }   _0x9000001._0x0001101 = num;   return(0);}int inmpi_dpsemaphore_setnumber_( long *num, int *_0x0000111 ){   *_0x0000111 = inMPI_DPsemaphore_SetNumber( *num );   return( *_0x0000111 );}void inMPI_DPsemaphore_Thread( void *arg ){   int _0x0000100 = 0;   printf("Distributed-parallel semaphore handling thread spawned \n");   while( _0x0000100 == 0 ) {      MPI_Status pstat;      int _0x0001010;      int _0x0000010;      long _0x0001001;            if( _0x9000001._0x0000101 == 1 ) {         _0x0000100 = 1;      }            MPI_Iprobe( MPI_ANY_SOURCE, 9999, _0x9000001._0x0001111,                  &_0x0001010, &pstat );      if(_0x0001010) {             if( pstat.MPI_TAG != 9999 ) fprintf(stdout,"WEIRD TAG! (%d)\n",                                             pstat.MPI_TAG);         MPI_Recv( &_0x0000010, 1, MPI_INT, pstat.MPI_SOURCE, pstat.MPI_TAG,                   _0x9000001._0x0001111, MPI_STATUS_IGNORE );         if( _0x0000010 == 1 ) {                      if( _0x9000001._0x0001101 >= 0 ) {               _0x0001001 = _0x9000001._0x0001101;               _0x9000001._0x0001101 -= 1;            } else {               _0x0001001 = 0;                    }         } else {              if( _0x9000001._0x0000011 == 2 )            printf("Received weird message from client!|n");            _0x0001001 = -1;         }         MPI_Send( &_0x0001001, 1, MPI_LONG, pstat.MPI_SOURCE, 8888,                   _0x9000001._0x0001111 );      }      }   printf("Distributed-parallel semaphore handling thread ending \n");}int inMPI_DPsemaphore_Init( MPI_Comm _0x0001111, int _0x0000110, int _0x0000011ose ){   int _0x0010001,_0x0010000;   int _0x0001100;   void *_0x0001011 = &( inMPI_DPsemaphore_Thread );   if( _0x0001111 == MPI_COMM_NULL ) {      printf("Tried to instantiate a parallel semaphore using a null _0x0001111unicator\n");      return(1);   }   MPI_Comm_size( _0x0001111, &_0x0010000 );   MPI_Comm_rank( _0x0001111, &_0x0010001 );      MPI_Query_thread( &_0x0001100 );   if( _0x0001100 != MPI_THREAD_MULTIPLE ) {      if( _0x0010001 == 0 ) printf("Need an MPI_THREAD_MULTIPLE capable MPI library (%d) \n", MPI_THREAD_MULTIPLE );      if( _0x0010001 == 0 ) printf("The running MPI library returned: %d \n", _0x0001100);      return(2);   }   if( _0x0000110 >= _0x0010000 ) {      if( _0x0010001 == 0 ) {         printf("Master rank provided greater than num. of proceses.\n");      }      return(3);   }   if( _0x9000001._0x0000110 != -1 ) {      if( _0x0010001 == 0 ) {         printf("The parallel semaphore has already been instantiated\n");      }      return(4);   } else {      _0x9000001._0x0000110 = _0x0000110;      _0x9000001._0x0001101 = 0;      _0x9000001._0x0000101 = 0;   }   _0x9000001._0x0000011 = _0x0000011ose;   MPI_Comm_dup( _0x0001111, &( _0x9000001._0x0001111 ) );   if( _0x0010001 == _0x0000110 ) {      pthread_attr_init( &( _0x9000001.tattr ) );      pthread_create( &( _0x9000001.pt ), &( _0x9000001.tattr ),                      _0x0001011, (void *) NULL );      printf("Parallel semaphore instantiated\n");   }   return(0);}int inmpi_dpsemaphore_init_( MPI_Fint *_0x0001110, int *_0x0000110, int *_0x0000011ose ){   MPI_Comm _0x0001111;   int _0x0000111;   _0x0001111 = MPI_Comm_f2c( *_0x0001110 );   _0x0000111 = inMPI_DPsemaphore_Init( _0x0001111, *_0x0000110, *_0x0000011ose );   return( _0x0000111 );}int inMPI_DPsemaphore_Term(){   int _0x0010001,_0x0010000;   void *pret;   if( _0x9000001._0x0001111 == MPI_COMM_NULL ) {      printf("Attempted to deconstruct an inactive semaphore \n");      return(1);   }   MPI_Comm_size( _0x9000001._0x0001111, &_0x0010000 );   MPI_Comm_rank( _0x9000001._0x0001111, &_0x0010001 );   MPI_Barrier( _0x9000001._0x0001111 );   if( _0x0010001 == _0x9000001._0x0000110 ) {            _0x9000001._0x0000101 = 1;            pthread_join( _0x9000001.pt, &pret );            (void) pthread_attr_destroy( &( _0x9000001.tattr ) );   }   MPI_Comm_free( &( _0x9000001._0x0001111 ) );   _0x9000001._0x0001111 = MPI_COMM_NULL;      _0x9000001._0x0000110 = -1;   _0x9000001._0x0001101 = -1;   _0x9000001._0x0000101 = 0;   if( _0x0010001 == 0 ) {      printf("Distributed parallel semaphore deconstructed \n");   }   return(0);}int inmpi_dpsemaphore_term_() {   (void) inMPI_DPsemaphore_Term();   return(0);}
