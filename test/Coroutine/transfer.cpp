//
//  transfer.cpp
//  This file is part of the "Coroutine" project and released under the MIT License.
//
//  Created by Samuel Williams on 10/5/2018.
//  Copyright, 2018, by Samuel Williams. All rights reserved.
//

#include <UnitTest/UnitTest.hpp>

#include <Coroutine/Coroutine.h>

namespace Coroutine
{
	using namespace UnitTest::Expectations;
	
	COROUTINE test(coroutine_context * from, coroutine_context * self)
	{
		from = coroutine_transfer(self, from);
		coroutine_transfer(self, from);
	}
	
	UnitTest::Suite transferTestSuite {
		"coroutine_transfer",
		
		{"it can transfer execution context",
			[](UnitTest::Examiner & examiner) {
				coroutine_context main_fiber, test_fiber;
				
				std::size_t size = 1024*2;
				void * base_pointer = malloc(size);

				coroutine_initialize(&main_fiber, nullptr, nullptr, 0);
				coroutine_initialize(&test_fiber, &test, (char*)base_pointer+size, size);
				
				{
					coroutine_context * from = coroutine_transfer(&main_fiber, &test_fiber);
					examiner.expect(from).to(be == &test_fiber);
				}
				
				{
					coroutine_context * from = coroutine_transfer(&main_fiber, &test_fiber);
					examiner.expect(from).to(be == &test_fiber);
				}
			}
		},
	};
}
