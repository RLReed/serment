//----------------------------------*-C++-*----------------------------------//
/*!
 * \file   StateERME.i.hh
 * \brief  StateERME inline member definitions
 * \author Jeremy Roberts
 * \date   Aug 23, 2012
 */
//---------------------------------------------------------------------------//

#ifndef STATEERME_I_HH_
#define STATEERME_I_HH_

namespace erme
{

inline void StateERME::set_k(const double k_val)
{
  d_k = k_val;
}

inline void StateERME::set_lambda(const double lambda_val)
{
  d_lambda = lambda_val;
}

inline double StateERME::k() const
{
  return d_k;
}

inline double StateERME::lambda() const
{
  return d_lambda;
}

} // end namespace erme

#endif // STATEERME_I_HH_ 

//---------------------------------------------------------------------------//
//              end of file StateERME.i.hh
//---------------------------------------------------------------------------//
