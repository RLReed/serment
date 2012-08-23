//----------------------------------*-C++-*----------------------------------//
/*!
 * \file   MPI.hh
 * \brief  MPI communications interface
 * \author Jeremy Roberts
 * \date   Aug 21, 2012
 */
//---------------------------------------------------------------------------//

#ifndef MPI_HH_
#define MPI_HH_

// Serment Comm
//#include "Functions.hh"
#include "MPI_Traits.hh"

// Detran utilities
#include "DBC.hh"

// System
#include <mpi.h>

namespace serment_comm
{

//---------------------------------------------------------------------------//
// MPI Communicator
//---------------------------------------------------------------------------//

extern MPI_Comm default_communicator;
extern MPI_Comm communicator;

typedef MPI_Comm Communicator_t;

//---------------------------------------------------------------------------//
// BLOCKING SEND/RECEIVE OPERATIONS
//---------------------------------------------------------------------------//

template<class T>
inline int Comm::send(const T *buffer,
                      int      size,
                      int      destination,
                      int      tag)
{
  MPI_Send(const_cast<T *>(buffer), size, MPI_Traits<T>::element_type(),
           destination, tag, communicator);
  return COMM_SUCCESS;
}

template<class T>
inline int Comm::receive(T   *buffer,
            int  size,
            int  source,
            int  tag)
{
  int count = 0;

  // get a handle to the MPI_Status
  MPI_Status status;

  // do the blocking receive
  MPI_Recv(buffer, size, MPI_Traits<T>::element_type(), source, tag,
           communicator, &status);

  // get the count of received data
  MPI_Get_count(&status, MPI_Traits<T>::element_type(), &count);
  return count;
}

//---------------------------------------------------------------------------//
// BROADCAST
//---------------------------------------------------------------------------//

template<class T>
inline int Comm::broadcast(T  *buffer,
              int size,
              int root)
{
  int r = MPI_Bcast(buffer, size, MPI_Traits<T>::element_type(),
                    root, communicator);
  return r;
}

//---------------------------------------------------------------------------//
// BARRIER
//---------------------------------------------------------------------------//

inline void Comm::global_barrier()
{
  MPI_Barrier(communicator);
}

//---------------------------------------------------------------------------//
// TIMING
//---------------------------------------------------------------------------//

inline void Comm::tic()
{
  d_time = MPI_Wtime();
}

inline double Comm::toc()
{
  return MPI_Wtime() - d_time;
}

} // end namespace serment_comm

#endif // MPI_HH_ 

//---------------------------------------------------------------------------//
//              end of file MPI.hh
//---------------------------------------------------------------------------//