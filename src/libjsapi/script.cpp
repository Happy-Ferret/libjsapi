/**
 * The MIT License (MIT)
 *
 * Copyright (c) 2015 Ripcord Software Ltd
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
**/

#include "script.h"

#include "context.h"
#include "value.h"

rs::jsapi::Script::Script(Context& cx, const char* code) : 
    cx_(cx), code_(code), script_(cx) {
}

rs::jsapi::Script::~Script() {
}

bool rs::jsapi::Script::Compile() {
    JSAutoRequest ar(cx_);
    JS::CompileOptions options(cx_);
    if (!JS_CompileScript(cx_, cx_.getGlobal(), code_.c_str(), code_.length(), options, &script_)) {    
        auto error = cx_.getError();
        if (!!error) {
            throw *error;
        }
    }
    
    return script_;
}

bool rs::jsapi::Script::Execute() {
    JSAutoRequest ar(cx_);
    if (!script_) {
        Compile();
    }
    
    auto status = JS_ExecuteScript(cx_, cx_.getGlobal(), script_);
    
    auto error = cx_.getError();
    if (!!error) {
        throw *error;
    }
    
    return status;
}

bool rs::jsapi::Script::Execute(Value& result) {
    JSAutoRequest ar(cx_);
    if (!script_) {
        Compile();
    }
    
    auto status = JS_ExecuteScript(cx_, cx_.getGlobal(), script_, result);    
    
    auto error = cx_.getError();
    if (!!error) {
        throw *error;
    }
    
    return status;
}