//
//  Coroutine.h
//  File file is part of the "Coroutine" project and released under the MIT License.
//
//  Created by Samuel Williams on 10/5/2018.
//  Copyright, 2018, by Samuel Williams. All rights reserved.
//

#pragma once

/* Select the appropriate header */

#if defined(_WIN64)
	#include "win64.h"
#elif defined(_WIN32)
	#include "win32.h"
#elif defined(__amd64)
	#include "amd64.h"
#endif
