[![Build Status](https://travis-ci.org/RipcordSoftware/libjsapi.svg?branch=master)](https://travis-ci.org/RipcordSoftware/libjsapi)
[![Coverage Status](https://coveralls.io/repos/RipcordSoftware/libjsapi/badge.svg)](https://coveralls.io/r/RipcordSoftware/libjsapi)

# libjsapi
A SpiderMonkey 31 (Mozilla) JSAPI wrapper for C++ 11.

The JSAPI interface to the SpiderMonkey JavaScript VM is difficult to integrate into 
applications without an intermediate abstraction layer managing object creation and 
type mapping. This library is an attempt to hide the complexity of dealing with SpiderMonkey
from modern C++ 11 applications. 

The SM API is very complex, with many obscure types and functions which are not very well 
documented. In a number of places you will be exposed directly to the SM type system - this is
something we'd like to avoid and may be able to engineer out in future releases.

##Examples:

The simplest thing that could possibly work:
```c++
#include <iostream>
#include "libjsapi.h"

int main() {
    // create the runtime which hosts spidermonkey
    rs::jsapi::Runtime rt;
    
    // execute a script in the context of the runtime, getting the result
    rs::jsapi::Result result(rt);
    rt.Evaluate("(function(){return 42;})();", result);
    
    // output the result to the console
    auto val = result.toNumber();
    std::cout << val << std::endl;
    return 0;
}
```

Among other things we can expose C++ lambdas (and methods) to JS:
```c++
#include <iostream>
#include "libjsapi.h"

int main() {
    // create the runtime which hosts spidermonkey
    rs::jsapi::Runtime rt;
    
    // define a function in global scope implemented by a C++ lambda
    rs::jsapi::Object::DefineGlobalFunction(rt, "getTheAnswer", 
        [](JSContext* cx, unsigned argc, JS::Value* vp) { 
            JS::CallArgsFromVp(argc, vp).rval().setInt32(42); 
            return true; 
    });
    
    // call the native function from JS
    rs::jsapi::Result result(rt);
    rt.Evaluate("(function(){return getTheAnswer();})();", result);
    
    // output the result to the console
    auto val = result.toNumber();
    std::cout << val << std::endl;
    return 0;
}
```

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
