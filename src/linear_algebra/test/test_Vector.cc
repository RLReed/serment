//----------------------------------*-C++-*----------------------------------//
/*!
 * \file   test_Vector.cc
 * \author Jeremy Roberts
 * \date   Aug 19, 2012
 * \brief  Test of Vector class.
 * \note   Copyright (C) 2012 Jeremy Roberts. 
 */
//---------------------------------------------------------------------------//

// LIST OF TEST FUNCTIONS
#define TEST_LIST         \
        FUNC(test_Vector)

// Detran test
#include "TestDriver.hh"

#include "Vector.hh"

#include <iostream>

// Setup

using namespace linear_algebra;
using namespace detran_test;

int main(int argc, char *argv[])
{
  RUN(argc, argv);
}

//----------------------------------------------//
// TEST DEFINITIONS
//----------------------------------------------//

int test_Vector_actual();

// Test of basic public interface
int test_Vector(int argc, char *argv[])
{
  // Initialize PETSc
  PetscInitialize(&argc, &argv, PETSC_NULL, PETSC_NULL);

  // Call actual test.
  int result = test_Vector_actual();

  // Finalize PETSc
  PetscFinalize();

  return result;
}

// Test of basic public interface
int test_Vector_actual()
{
  // Create vector
  Vector X(10);
  TEST(X.global_size() == 10);

  double value = 1.0;
  int count = 1;
  for (int i = 0; i < 10; i++)
  {
    X.insert_values(count, &i, &value);
  }
  X.assemble();

  value = X.dot(X);
  TEST(detran::soft_equiv(value, 10.0));

  X.display();

  return 0;
}

//---------------------------------------------------------------------------//
//              end of test_Vector.cc
//---------------------------------------------------------------------------//
