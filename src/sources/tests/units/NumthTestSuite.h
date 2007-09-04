/*
 *  $Id$
 */

#ifndef __NUMTHTESTSUITE_H
#define __NUMTHTESTSUITE_H

#include "ZTest.h"
#include "Z_nTest.h"
#include "ZM_nTest.h"
#include "KernelTest.h"
#include "RSATest.h"
#include "RandomTest.h"
#include "PrimesTest.h"
#include "MatrixZTest.h"
#include "MatrixRTest.h"
#include "VectorZTest.h"
#include "VectorRTest.h"
#include "MethodsFactoryTest.h"
#include "OpenMPTest.h"
#include "ReductionTest.h"
#include "ExponentiationTest.h"
#include "qtunit/TestSuite.h"

namespace com_uwyn_qtunit
{
	class NumthTestSuite : public TestSuite
	{
	public:
		NumthTestSuite();
	
	private:
		ZTest _zTest;
    Z_nTest _z_nTest;
    ZM_nTest _zM_nTest;
    KernelTest _kernelTest;
    RSATest _rsaTest;
    RandomTest _randomTest;
    MatrixZTest _matrixZTest;
//    MatrixRTest _matrixRTest;
    VectorZTest _vectorZTest;
    VectorRTest _vectorRTest;
    MethodsFactoryTest _functionsTest;
#ifdef _OPENMP
    OpenMPTest _openMPTest;
#endif
    ReductionTest _reductionTest;
    ExponentiationTest _exponentiationTest;
    PrimesTest _primesTest;

	};
}

#endif
