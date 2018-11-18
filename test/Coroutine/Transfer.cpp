//
//  Transfer.cpp
//  This file is part of the "Coroutine" project and released under the MIT License.
//
//  Created by Samuel Williams on 10/5/2018.
//  Copyright, 2018, by Samuel Williams. All rights reserved.
//

#include <UnitTest/UnitTest.hpp>

#include <Coroutine/Context.h>

namespace Coroutine
{
	using namespace UnitTest::Expectations;
	
	COROUTINE test(CoroutineContext * from, CoroutineContext * self, void * argument)
	{
		from = coroutine_transfer(self, from);
		coroutine_transfer(self, from);
		
		abort();
	}
	
	UnitTest::Suite TransferTestSuite {
		"coroutine_transfer",
		
		{"it can transfer execution context",
			[](UnitTest::Examiner & examiner) {
				CoroutineContext main_fiber = {NULL}, test_fiber;
				
				std::size_t size = 1024*2;
				void * base_pointer = malloc(size);
				
				coroutine_initialize(&test_fiber, &test, nullptr, (char*)base_pointer+size, size);
				
				{
					CoroutineContext * from = coroutine_transfer(&main_fiber, &test_fiber);
					examiner.expect(from).to(be == &test_fiber);
				}
				
				{
					CoroutineContext * from = coroutine_transfer(&main_fiber, &test_fiber);
					examiner.expect(from).to(be == &test_fiber);
				}
			}
		},
	};
}
