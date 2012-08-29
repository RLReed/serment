//----------------------------------*-C++-*----------------------------------//
/*!
 * \file   NeighborSurface.hh
 * \brief  NeighborSurface class definition
 * \author Jeremy Roberts
 * \date   Aug 27, 2012
 */
//---------------------------------------------------------------------------//

#ifndef NEIGHBORSURFACE_HH_
#define NEIGHBORSURFACE_HH_

#include <boost/serialization/access.hpp>

namespace erme_geometry
{

/*!
 *  \class NeighborSurface
 *  \brief Contains a neighbor index and the surface shared
 */
class NeighborSurface
{

public:

  typedef unsigned int size_type;

  NeighborSurface(const int n = 0, const size_type s = 0)
    : d_neighbor(n),
      d_surface(s)
  {/* ... */}

  int neighbor() const
  {
    return d_neighbor;
  }

  size_type surface() const
  {
    return d_surface;
  }

private:

  //-------------------------------------------------------------------------//
  // DATA
  //-------------------------------------------------------------------------//

  /// Index of a node's neighbor
  int d_neighbor;

  /// Index of the neighbor's surface a node shares
  size_type d_surface;

  //-------------------------------------------------------------------------//
  // IMPLEMENTATION
  //-------------------------------------------------------------------------//

  friend class boost::serialization::access;

  template <class Archive>
  void serialize(Archive & ar, const unsigned int version)
  {
    ar & d_neighbor;
    ar & d_surface;
  }

};


} // end namespace erme_geometry

#endif // NEIGHBORSURFACE_HH_ 

//---------------------------------------------------------------------------//
//              end of file NeighborSurface.hh
//---------------------------------------------------------------------------//