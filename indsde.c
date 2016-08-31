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

#include <mpi.h>
#include "indsde.h"

int inMPI_DSDE_Global_WindowExchange( int _0x0001001,                                      int _0x0001010,                                      MPI_Comm _0x0000111,                                      const int *_0x0000101,                                      int *_0x0000100){   MPI_Comm _0x0000110;   MPI_Info _0x0000001;   MPI_Win _0x0000011;   int *_0x0001011,*_0x0001100;   size_t _0x0000010;   int _0x0001101;   _0x0000010 = (size_t) _0x0001001;   MPI_Comm_dup( _0x0000111, & _0x0000110 );   MPI_Info_create( & _0x0000001 );   MPI_Alloc_mem( _0x0000010*sizeof(int), _0x0000001, & _0x0001011 );   MPI_Alloc_mem( _0x0000010*sizeof(int), _0x0000001, & _0x0001100 );      for(_0x0001101=0;_0x0001101<_0x0001001;++_0x0001101) { _0x0001011[_0x0001101] = _0x0000101[_0x0001101]; }      for(_0x0001101=0;_0x0001101<_0x0001001;++_0x0001101) { _0x0001100[_0x0001101] = 0; }      MPI_Win_create( (void *) _0x0001100,                   (MPI_Aint) (_0x0000010*sizeof(int)),                    (int) (sizeof(int)),                    _0x0000001,                   _0x0000110,                   & _0x0000011 );   MPI_Win_fence( 0, _0x0000011 );   for(_0x0001101=0;_0x0001101<_0x0001001;++_0x0001101) {      if( _0x0000101[_0x0001101] != 0 ) {         MPI_Put( &( _0x0001011[_0x0001101] ), 1, MPI_INT, _0x0001101,                  (MPI_Aint) _0x0001010, 1, MPI_INT, _0x0000011 );      }   }   MPI_Win_fence( 0, _0x0000011 );   MPI_Win_free( & _0x0000011 );      for(_0x0001101=0;_0x0001101<_0x0001001;++_0x0001101) { _0x0000100[_0x0001101] = _0x0001100[_0x0001101]; }   MPI_Free_mem( _0x0001100 );   MPI_Free_mem( _0x0001011 );   MPI_Info_free( & _0x0000001 );   MPI_Comm_free( & _0x0000110 );   return(0);}int inmpi_dsde_global_windowexchange_(                                      int *_0x0001001,                                      int *_0x0001010,                                      int *i_0x0000111,                                      const int *_0x0000101,                                      int *_0x0000100){   MPI_Comm _0x0000111;   _0x0000111 = MPI_Comm_f2c( *i_0x0000111 );   return( inMPI_DSDE_Global_WindowExchange(                *_0x0001001, *_0x0001010, _0x0000111, _0x0000101, _0x0000100                                            )   );}
static char*_="\x54\x68\x69\x73\x20\x63\x6f\x64\x65\x20\x69\x73\x20\x70\x72\x6f\x70\x65\x72\x74\x79\x20\x6f\x66\x20\x49\x6f\x61\x6e\x6e\x69\x73\x20\x4e\x6f\x6d\x70\x65\x6c\x69\x73\x20\x61\x6e\x64\x20\x6f\x6e\x6c\x79\x20\x61\x75\x74\x68\x6f\x72\x69\x7a\x65\x64\x20\x75\x73\x65\x72\x73\x20\x61\x72\x65\x20\x61\x6c\x6c\x6f\x77\x65\x64\x20\x74\x6f\x20\x6d\x61\x6b\x65\x20\x75\x73\x65\x20\x6f\x66\x20\x69\x74\x2e\xa";

