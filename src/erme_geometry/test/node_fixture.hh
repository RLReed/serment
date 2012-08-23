//----------------------------------*-C++-*----------------------------------//
/*!
 * \file   node_fixture.hh
 * \brief  Fixtures for various node types.
 * \author Jeremy Roberts
 * \date   Aug 22, 2012
 */
//---------------------------------------------------------------------------//

#ifndef NODE_FIXTURE_HH_
#define NODE_FIXTURE_HH_

#include "CartesianNodeDetran.hh"

namespace serment_test
{

typedef erme_geometry::Node::SP_node SP_node;

/*!
 *  The Detran Cartesian nodes are all 10 cm in extent
 *  with a monoenergetic material.  All applicable
 *  responses are first order.
 */

SP_node cartesian_node_detran(const int dim)
{
  Require(dim > 0 and dim <= 3);

  typedef erme_geometry::CartesianNodeDetran Node_T;

  // Parameter database
  Node_T::SP_db   db(new detran::InputDB());
  db->put("number_groups",  1);
  db->put("dimension",      dim);

  // Build the material
  Node_T::SP_material mat(new detran::Material(1, 1));
  mat->set_sigma_t(0, 0, 1.0);
  mat->set_sigma_s(0, 0, 0, 0.5);
  mat->set_sigma_f(0, 0, 0.5);

  // Define discretization and material map
  Node_T::vec_dbl cm(2, 0.0);
  cm[1] = 10.0;
  Node_T::vec_int fm(1, 10);
  Node_T::vec_int mt(1, 0);

  // Build the mesh
  Node_T::SP_mesh mesh;
  if (dim == 1)
    mesh = new detran::Mesh1D(fm, cm, mt);
  else if (dim == 2)
    mesh = new detran::Mesh2D(fm, fm, cm, cm, mt);
  else
    mesh = new detran::Mesh3D(fm, fm, fm, cm, cm, cm, mt);

  Node_T::vec_dbl widths(3, 1.0);
  for (int i = 0; i < dim; i++)
    widths[i] = 10.0;

  // Create node
  Node_T::SP_node
    node(new Node_T(dim, 2*dim, 123, "testnode", Node_T::Point(0, 0, 0),
         Node_T::vec2_size_type(2*dim, Node_T::vec_size_type(dim-1, 1)),
         Node_T::vec_size_type(2*dim, 1), Node_T::vec_size_type(2*dim, 0),
         Node_T::vec_size_type(2*dim, 0), widths, db, mat, mesh));
  Ensure(node);
  return node;
}


} // end namespace serment_test

#endif // NODE_FIXTURE_HH_ 

//---------------------------------------------------------------------------//
//              end of file node_fixture.hh
//---------------------------------------------------------------------------//