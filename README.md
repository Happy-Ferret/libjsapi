[![Build Status](https://travis-ci.org/RipcordSoftware/libjsapi.svg?branch=master)](https://travis-ci.org/RipcordSoftware/libjsapi)
[![Coverage Status](https://coveralls.io/repos/RipcordSoftware/libjsapi/badge.svg)](https://coveralls.io/r/RipcordSoftware/libjsapi)
[![License](http://img.shields.io/:license-mit-blue.svg)](http://doge.mit-license.org)

# libjsapi
A SpiderMonkey 50 (Mozilla) JSAPI wrapper for C++ 11.

The JSAPI interface to the SpiderMonkey JavaScript VM can be difficult to integrate into 
applications without an intermediate abstraction layer managing object creation, object lifetimes and 
type mapping. This library is an attempt to hide the complexity of dealing with SpiderMonkey
from modern C++ 11 applications. 

With `libjsapi` you will be able to:
* Execute any valid JavaScript
* Invoke JavaScript methods from C++
* Expose C++ methods to JavaScript
* Expose C++ objects to JavaScript
* Consume JavaScript objects in C++
* Handle errors with C++ exceptions
* Create any number of Runtimes and Contexts - simultaneously on multiple threads
 
##Gratuitous Screenshot

The image below shows `libjsapi` hosting a GTK+ application which emulates enough browser bits to render a funky JavaScript Mandelbrot application ported from https://github.com/cslarsen/mandelbrot-js.

![A JS generated Mandelbrot running under libjsapi](https://pbs.twimg.com/media/CEVOZlRWAAAt6-w.png:large)

The window on the left is Firefox rendering a Mandelbrot fractal, on the right is the `libjsapi` application running (mainly) the same JavaScript code.

##Examples:

The simplest thing that could possibly work:
```c++
#include <iostream>
#include "libjsapi.h"

int main() {
    // create the context which hosts spidermonkey
    rs::jsapi::Context cx;
    
    // execute a script in the context of the runtime, getting the result
    rs::jsapi::Value result(cx);
    cx.Evaluate("(function(){return 42;})();", result);
    
    // output the result to the console
    std::cout << result << std::endl;
}
```

Among other things we can expose C++ lambdas (and methods) to JS:
```c++
#include <iostream>
#include "libjsapi.h"

int main() {
    // create the context which hosts spidermonkey
    rs::jsapi::Context cx;
    
    // define a function in global scope implemented by a C++ lambda
    rs::jsapi::Global::DefineFunction(cx, "getTheAnswer", 
        [](const std::vector<rs::jsapi::Value>& args, rs::jsapi::Value& result) { 
            result = 42; 
    });
    
    // call the native function from JS
    rs::jsapi::Value result(cx);
    cx.Evaluate("(function(){return getTheAnswer();})();", result);
    
    // output the result to the console
    std::cout << result << std::endl;
}
```

The [wiki](https://github.com/RipcordSoftware/libjsapi/wiki) contains more background on JSAPI, libjsapi and further examples.

# Building
Requires:
* GCC 4.8.1+
* GNU Make
* lcov and Ruby (for test coverage)
* valgrind (for memory analysis)

To build type:
```bash
$ make
```

The first `libjsapi` build may take a long time to complete since it will invoke a build of SpiderMonkey and GoogleTest. Subsequent builds do not require this step and will be much faster.

To build tests with coverage:
```bash
$ make test
```

To create a coverage report:
```bash
$ ./coverage.sh
```

To create a valgrind report:
```bash
$ ./grind.sh
```

You will find examples in the `examples` directory. You can build these after building libjsapi by running:
```bash
$ cd examples
$ make
```

If building is slow on your system then you can speed it up by stripping the debugging information from the mozjs library by running `./strip_mozjs.sh`.

The [wiki](https://github.com/RipcordSoftware/libjsapi/wiki) contains details on building on different systems.
