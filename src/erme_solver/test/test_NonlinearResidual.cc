//----------------------------------*-C++-*-----------------------------------//
/**
 *  @file  test_NonlinearResidual.cc
 *  @brief Test of GlobalSolverPicard class
 *  @note  Copyright (C) 2013 Jeremy Roberts
 */
//----------------------------------------------------------------------------//

// LIST OF TEST FUNCTIONS
#define TEST_LIST                     \
        FUNC(test_NonlinearResidual)

#include "utilities/TestDriver.hh"
#include "erme_solver/ManagerERME.hh"
#include "erme_solver/NonlinearResidual.hh"
#include "erme_geometry/test/nodelist_fixture.hh"
#include <iostream>

using namespace serment_comm;
using namespace erme_solver;
using namespace erme_geometry;
using namespace detran_test;
using detran_utilities::soft_equiv;
using std::cout;
using std::endl;

int main(int argc, char *argv[])
{
  RUN(argc, argv);
}

//----------------------------------------------------------------------------//
// TEST DEFINITIONS
//----------------------------------------------------------------------------//

int test_NonlinearResidual(int argc, char *argv[])
{
  // Parameter database
  ManagerERME::SP_db db = detran_utilities::InputDB::Create();

  // Setup the manager and comm
  ManagerERME manager(argc, argv);
  int ng = Comm::size() == 1 ? 1 : 2;
  db->put<int>("comm_local_groups", ng);
  db->put<int>("dimension", 1);
  manager.build_comm(db);

  // Get nodes, build problem, and retrieve responses
  NodeList::SP_nodelist nodes = cartesian_node_dummy_list_1d();
  manager.build_erme(nodes);
  manager.get_server()->update(1.0);
  ManagerERME::SP_responsecontainer r = manager.get_responses();

  if (Comm::is_global())
  {
    serment_comm::Comm::set(global);

    // Update the responses
    r->R->update();
    r->F->update();
    r->A->update();
    r->L->update();

    // Build the residual
    NonlinearResidual residual(r->R, r->M, r->F, r->A, r->L);
    r->R->display(r->R->BINARY, "nlr_R.out");
    r->M->display(r->M->BINARY, "nlr_M.out");
    r->F->display(r->F->BINARY, "nlr_F.out");
    r->A->display(r->A->BINARY, "nlr_A.out");
    r->L->display(r->L->BINARY, "nlr_L.out");

    double f_ref[] =
      {-2.041241452319315e-01, -2.041241452319315e-01,
       -2.041241452319315e-01,  7.348461063383726e+04,  7.348461063383726e+04,
        7.348461063383726e+04,  7.348461063383726e+04,  7.348461063383726e+04,
        7.348461063383726e+04,  7.348461063383726e+04,  7.348461063383726e+04,
        7.348461063383726e+04,  7.348461063383726e+04,  7.348461063383726e+04,
        7.348461063383726e+04,  7.348461063383726e+04,  7.348461063383726e+04,
        7.348461063383726e+04,  7.348461063383726e+04,  7.348461063383726e+04,
        7.348461063383726e+04, -2.041241452319315e-01, -2.041241452319315e-01,
       -2.041241452319315e-01, -1.469708665082851e+05, -1.110223024625157e-16};
    double norm_f_ref = 3.446740773579676e+05;

    int m = r->R->number_local_rows();
    if (Comm::is_last()) m += 2;
    linear_algebra::Vector x(m, 0.2041241452319315);
    if (Comm::is_last())
    {
      x[m-2] = 1.0;
      x[m-1] = 1.0;
    }
    linear_algebra::Vector J(x, r->R->number_local_rows());
    linear_algebra::Vector f(m, 0.0);
    residual.evaluate(x, f);

    double norm_f = residual.compute_norm(x);
    TEST(soft_equiv(norm_f, norm_f_ref));
    norm_f = residual.compute_norm(J, 1.0, 1.0);
    TEST(soft_equiv(norm_f, norm_f_ref));
    for (int i = 0; i < f.local_size(); ++i)
    {
      TEST(soft_equiv(f[i], f_ref[i+f.lower_bound()]));
    }

    serment_comm::Comm::set(world);
  }

  Comm::global_barrier();
  return 0;
}

//----------------------------------------------------------------------------//
//              end of file test_NonlinearResidual.cc
//----------------------------------------------------------------------------//