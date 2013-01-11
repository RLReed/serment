//----------------------------------*-C++-*----------------------------------//
/**
 *  @file   ResponseSourceDetran.hh
 *  @brief  ResponseSourceDetran class definition
 *  @author Jeremy Roberts
 *  @date   Sep 1, 2012
 */
//---------------------------------------------------------------------------//

#ifndef erme_response_RESPONSESOURCEDETRAN_HH_
#define erme_response_RESPONSESOURCEDETRAN_HH_

#include "erme_response/ResponseSource.hh"
#include "erme_geometry/CartesianNodeDetran.hh"
#include "orthog/OrthogonalBasis.hh"
#include "solvers/FixedSourceManager.hh"
#include "boundary/BoundaryBase.hh"
#include "boundary/BoundaryTraits.hh"
#include "angle/ProductQuadrature.hh"

namespace erme_response
{

/**
 *  @class ResponseSourceDetran
 *  @brief Compute responses using Detran
 */
template <class D>
class ResponseSourceDetran: public ResponseSource
{

public:

  //-------------------------------------------------------------------------//
  // TYPEDEFS
  //-------------------------------------------------------------------------//

  typedef erme_geometry::CartesianNodeDetran::SP_node   SP_node;
  typedef detran_utilities::InputDB::SP_input           SP_db;
  typedef detran_material::Material::SP_material        SP_material;
  typedef detran_geometry::Mesh::SP_mesh                SP_mesh;
  typedef detran_orthog::OrthogonalBasis::SP_basis      SP_basis;
  typedef std::vector<SP_basis>                         vec_basis;
  typedef std::vector<vec_basis>                        vec2_basis;
  typedef detran::BoundaryBase<D>                       Boundary_T;
  typedef typename Boundary_T::SP_boundary              SP_boundary;
  typedef detran::FixedSourceManager<D>                 Solver_T;
  typedef typename detran_utilities::SP<Solver_T>       SP_solver;
  typedef typename Solver_T::SP_quadrature              SP_quadrature;
  typedef detran_angle::ProductQuadrature               ProductQuadrature;
  typedef detran_utilities::SP<ProductQuadrature>       SP_productquadrature;

  //-------------------------------------------------------------------------//
  // PUBLIC INTERFACE
  //-------------------------------------------------------------------------//

  /// Constructor
  ResponseSourceDetran(SP_node node);

  //-------------------------------------------------------------------------//
  // ABSTRACT INTERFACE
  //-------------------------------------------------------------------------//

  void compute(SP_response response, ResponseIndex index)
  {
    /* ... */
  }

private:

  //-------------------------------------------------------------------------//
  // DATA
  //-------------------------------------------------------------------------//

  /// Detran db
  SP_db d_db;
  /// Detran material
  SP_material d_material;
  /// Detran mesh
  SP_mesh d_mesh;
  /// Detran solver
  SP_solver d_solver;
  /// Quadrature
  SP_quadrature d_quadrature;
  /// Energy basis [number surfaces]
  vec_basis d_basis_e;
  /// Spatial basis [number surfaces, dim per surface]
  vec2_basis d_basis_s;
  /// Azimuthal basis [number surfaces]
  vec_basis d_basis_a;
  /// Polar basis [number surfaces]
  vec_basis d_basis_p;

  //-------------------------------------------------------------------------//
  // IMPLEMENTATION
  //-------------------------------------------------------------------------//

  /**
   *  @brief Set the boundary condition for a given incident order
   *  @param boundary   Pointer to boundary flux container
   *  @param index      The response index that defines the boundary condition
   */
  template <class B>
  void set_boundary(B& boundary, ResponseIndex index);

  /// Construct the basis
  void construct_basis();

};

} // end namespace erme_response

#endif // erme_response_RESPONSESOURCEDETRAN_HH_

//---------------------------------------------------------------------------//
//              end of file ResponseSourceDetran.hh
//---------------------------------------------------------------------------//
