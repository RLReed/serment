//----------------------------------*-C++-*----------------------------------//
/*!
 * \file   ResponseIndex.hh
 * \brief  ResponseIndex class definition
 * \author Jeremy Roberts
 * \date   Aug 24, 2012
 */
//---------------------------------------------------------------------------//

#ifndef RESPONSEINDEX_HH_
#define RESPONSEINDEX_HH_

#include <iostream>

namespace erme_response
{

/*!
 *  \struct ResponseIndex
 *  \brief  Convenience container for indices
 *  \param  n   Global node index
 *  \param  s   Node surface index
 *  \param  e   Energy moment order
 *  \param  p   Polar moment order
 *  \param  a   Azimithual moment order
 *  \param  s0  First spatial dimension order
 *  \param  s1  Second spatial dimenion order
 *  \param  eo  Is the combined function even=false or odd=true?
 *  \param  l   Moment index with set of local nodes
 */
struct ResponseIndex
{
  typedef unsigned int size_t;

  ResponseIndex(size_t n  = 0,
                size_t s  = 0,
                size_t e  = 0,
                size_t p  = 0,
                size_t a  = 0,
                size_t s0 = 0,
                size_t s1 = 0,
                bool   eo = false,
                size_t l  = 0)
  : node(n), surface(s), energy(e), polar(p), azimuth(a),
    space0(s0), space1(s1), even_odd(eo),
    local(l)
  {/* ... */}
  size_t node;
  size_t surface;
  size_t energy;
  size_t polar;
  size_t azimuth;
  size_t space0;
  size_t space1;
  bool   even_odd;
  size_t local;

};

} // end namespace erme_response

inline std::ostream& operator<< (std::ostream &out,
                                 const erme_response::ResponseIndex &r)
{
  out << "ResponseIndex:" << std::endl
      << "     node = " << r.node << std::endl
      << "  surface = " << r.surface << std::endl
      << "   energy = " << r.energy << std::endl
      << "    polar = " << r.polar << std::endl
      << "  azimuth = " << r.azimuth << std::endl
      << "   space0 = " << r.space0 << std::endl
      << "   space1 = " << r.space1 << std::endl
      << "    local = " << r.local << std::endl;
  return out;
}

#endif // RESPONSEINDEX_HH_ 

//---------------------------------------------------------------------------//
//              end of file ResponseIndex.hh
//---------------------------------------------------------------------------//
