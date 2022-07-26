# Coroutine

A high-performance cross-platform implementation of coroutines.

## Setup

The build tool [teapot] needs to be installed (which requires [Ruby]):

	$ gem install teapot

[teapot]: https://teapot.nz/
[Ruby]: https://www.ruby-lang.org/en/downloads/

### Dependencies

Fetch all the necessary project dependencies:

	$ cd coroutine
	$ teapot fetch

### Tests

Run the tests to confirm basic functionality:

	$ cd coroutine
	$ teapot Test/Coroutine

## Usage

There are several implementations. You will need to compile the relevant file for your platform.

Here is a simple example.

```c
#include <Coroutine/Coroutine.h>

COROUTINE test(CoroutineContext * from, CoroutineContext * self)
{
	from = coroutine_transfer(self, from);
	coroutine_transfer(self, from);
	
	abort();
}

int main(int argc, const char * argv[]) {
	CoroutineContext main_fiber = {NULL}, test_fiber;
	
	std::size_t size = 1024*2;
	void * base_pointer = malloc(size);

	coroutine_initialize(&test_fiber, &test, NULL, (char*)base_pointer+size, size);

	coroutine_transfer(&main_fiber, &test_fiber);
	coroutine_transfer(&main_fiber, &test_fiber);

	return 0;
}
```

You may like to augment the `struct CoroutineContext` to include additional fields, but the stack pointer must always remain the first one.

## Contributing

Please feel free to submit other implementations. Try to keep the implementations isolated.

1. Fork it.
2. Create your feature branch (`git checkout -b my-new-feature`).
3. Commit your changes (`git commit -am 'Add some feature'`).
4. Push to the branch (`git push origin my-new-feature`).
5. Create new Pull Request.

## License

Released under the MIT license.

Copyright, 2018, by Samuel Williams. All rights reserved.

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
