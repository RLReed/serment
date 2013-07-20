//----------------------------------*-C++-*-----------------------------------//
/**
 *  @file   GlobalSolverPicard.hh
 *  @brief  GlobalSolverPicard class definition
 *  @note   Copyright (C) 2013 Jeremy Roberts
 */
//----------------------------------------------------------------------------//

#ifndef erme_solver_GLOBALSOLVERPICARD_HH_
#define erme_solver_GLOBALSOLVERPICARD_HH_

#include "EigenvalueUpdate.hh"
#include "GlobalSolverBase.hh"
#include "linear_algebra/EigenSolver.hh"

namespace erme_solver
{

/**
 *  @class GlobalSolverPicard
 *  @brief Solves the problem using Picard (fixed point) iteration
 *
 *  The eigenvalue response matrix equations can be cast in
 *  the form of an inner current eigenvalue equation
 *  @f[
 *      \mathbf{MR}(k^{n})\mathbf{J} =  \lambda\mathbf{J} \, ,
 *  @f]
 *  with the associated @f$ k @f$ eigenvalue update
 *  @f[
 *      k^{n+1} = \frac{ \mathbf{F}(k^{n}) }
 *                     { \mathbf{A}(k^{n}) + mathbf{L}(k^{n}) }
 *  @f]
 *  which is a mathematical statement of gains-to-losses.
 *  These coupled equations represent a fixed-point iteration
 *  in the nonlinear variable @f$ k @f$.  Steffensen's method
 *  is easily implemented by extrapolating from three successive
 *  @f$ k @f$ values and is available as an optional update function.
 */
class GlobalSolverPicard: public GlobalSolverBase
{

public:

  //--------------------------------------------------------------------------//
  // TYPEDEFS
  //--------------------------------------------------------------------------//

  typedef detran_utilities::SP<GlobalSolverPicard>    SP_solver;
  typedef GlobalSolverBase                            Base;
  typedef OperatorMR::SP_MR                           SP_MR;
  typedef linear_algebra::EigenSolver::SP_solver      SP_innersolver;
  typedef EigenvalueUpdate::SP_update                 SP_update;

  //--------------------------------------------------------------------------//
  // PUBLIC INTERFACE
  //--------------------------------------------------------------------------//

  /**
   *  @brief Constructor
   *  @param db       	Pointer to parameter database
   *  @param indexer  	Pointer to response indexer
   *  @param server   	Pointer to response server
   *  @param state    	Pointer to state vector
   *  @param responses	Container of the responses
   */
  GlobalSolverPicard(SP_db 								db,
  		               SP_indexer 					indexer,
  		               SP_server 						server,
                     SP_state 						state,
                     SP_responsecontainer	responses);

  /// Virtual destructor
  virtual ~GlobalSolverPicard(){}

  /// Solve
  void solve();

  /// Perform a single Picard iteration
  double iterate(SP_vector x, double &keff, double &lambda);

private:

  //--------------------------------------------------------------------------//
  // DATA
  //--------------------------------------------------------------------------//

  /// Inner solver
  SP_innersolver d_innersolver;
  /// Eigenvalue update
  SP_update d_update;
  /// MR operator
  SP_MR d_MR;
  //@{
  /// Temporary working vectors
//  SP_vector d_J0;
//  SP_vector d_J1;
  //@}

  //--------------------------------------------------------------------------//
  // IMPLEMENTATION
  //--------------------------------------------------------------------------//

  void display(const size_t it,
               const double norm,
               const double keff,
               const double lambda);

};

} // end namespace erme_solver

#endif // erme_solver_GLOBALSOLVERPICARD_HH_

//----------------------------------------------------------------------------//
//              end of file GlobalSolverPicard.hh
//----------------------------------------------------------------------------//
