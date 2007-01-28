/*
 *  $Id$
 */

#ifndef __NUMTHTESTSUITE_H
#define __NUMTHTESTSUITE_H

#include "ZTest.h"
#include "KernelTest.h"
#include "RSATest.h"
#include "qtunit/TestSuite.h"

namespace com_uwyn_qtunit
{
	class NumthTestSuite : public TestSuite
	{
	public:
		NumthTestSuite();
	
	private:
		ZTest zTest_;
    KernelTest kernelTest_;
    RSATest rsaTest_;

	};
}

#endif
