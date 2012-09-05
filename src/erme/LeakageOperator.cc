//----------------------------------*-C++-*----------------------------------//
/*!
 * \file   LeakageOperator.cc
 * \brief  LeakageOperator 
 * \author Jeremy Roberts
 * \date   Sep 4, 2012
 */
//---------------------------------------------------------------------------//

#include "LeakageOperator.hh"

namespace erme
{

LeakageOperator::LeakageOperator(SP_nodelist nodes,
                                 SP_indexer indexer,
                                 SP_server server)
  : ResponseOperator(nodes, indexer, server)
  , Matrix(nodes->number_local_surfaces(),
           indexer->number_local_moments())
  , d_global_leakage(nodes->number_local_surfaces(), 0.0)
  , d_L_times_moments(nodes->number_local_surfaces(), 0.0)
{

  vec_int nnz_on_diag(d_nodes->number_local_surfaces(),  0);
  vec_int nnz_off_diag(d_nodes->number_local_surfaces(), 0);

  int index_s = 0;
  int index_m = 0;

  /*!
   *  Loop over all nodes.  The nonzero count is the number of moments
   *  for the node.  The global leakage vector gets an entry for each
   *  node surface.
   */
  for (int n = d_nodes->lower_bound(); n < d_nodes->upper_bound(); n++)
  {
    int size = d_indexer->number_node_moments(n);
    for (int i = 0; i < size; i++, index_m++)
      nnz_on_diag[index_m] = size;

    for (int s = 0; s < d_nodes->node(n)->number_surfaces(); s++, index_s++)
    {
      if (d_nodes->neighbor(n, s).neighbor() == erme_geometry::Node::VACUUM)
      {
        d_global_leakage[index_s] = 1.0;
      }
    }
  }

  // Preallocate.  This also computes the bounds and such.
  preallocate(nnz_on_diag, nnz_off_diag);

}

void LeakageOperator::update()
{
  using std::cout;
  using std::endl;

  // Offset for a block.  Starts at this matrix's lower bound.
  int offset = lower_bound();

  // Loop through nodes
  for (int n = 0; n < d_nodes->number_local_nodes(); n++)
  {

    // Get response
    SP_response r = d_server->response(n);

    // Block indices
    vec_int indices(r->number_surfaces(), offset);
    for (size_type i = 0; i < indices.size(); i++)
      indices[i] += i;

    // Insert each column (corresponding to an incident moment)
    for (int in = 0; in < r->size(); in++)
    {
      int col = in + offset;
      insert_values(r->size(), &indices[0], 1, &col,
                    &r->leakage_response(0, in));
    }

    offset += indices.size();
  }

  // Assemble after finishing
  assemble();

  d_L_times_moments.assemble();
  d_global_leakage.assemble();
}

double LeakageOperator::leakage(linear_algebra::Vector &x)
{
  // Preconditions
  Require(x.local_size() == number_local_columns());

  // Compute L * x
  multiply(x, d_L_times_moments);

  // Compute net global leakage
  double val = d_L_times_moments.dot(d_global_leakage);

  // \todo Could put warning for negative leakage
  return val;
}



} // end namespace erme

//---------------------------------------------------------------------------//
//              end of file LeakageOperator.cc
//---------------------------------------------------------------------------//