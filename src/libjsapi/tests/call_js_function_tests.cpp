/**
 * The MIT License (MIT)
 *
 * Copyright (c) 2015-2016 Ripcord Software Ltd
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

#include <gtest/gtest.h>

#include "../libjsapi.h"

class CallJSFunctionTests : public ::testing::Test {
protected:
    virtual void SetUp() {
        
    }
    
    virtual void TearDown() {
        
    }
};

TEST_F(CallJSFunctionTests, test1) {
    rs::jsapi::Context cx;
    cx.Evaluate("var myfunc=function(){return 42;};");
    
    rs::jsapi::Value result(cx);
    cx.Call("myfunc", result);
    
    ASSERT_TRUE(result.isNumber());
    ASSERT_EQ(42, result.toNumber());
}

TEST_F(CallJSFunctionTests, test2) {
    rs::jsapi::Context cx;
    cx.Evaluate("var myfunc1=function(){return 42;};");
    cx.Evaluate("var myfunc2=function(){return 69;};");
    
    rs::jsapi::Value result1(cx);
    cx.Call("myfunc1", result1);
    
    ASSERT_TRUE(result1.isNumber());
    ASSERT_EQ(42, result1.toNumber());
    
    rs::jsapi::Value result2(cx);
    cx.Call("myfunc2", result2);
    
    ASSERT_TRUE(result2.isNumber());
    ASSERT_EQ(69, result2.toNumber());            
}

TEST_F(CallJSFunctionTests, test3) {
    rs::jsapi::Context cx;
    
    rs::jsapi::Value result1(cx);
    cx.Evaluate("var myfunc=function(){return 42;};(function(){return myfunc()+1;})();", result1);    
    
    ASSERT_TRUE(result1.isNumber());
    ASSERT_EQ(43, result1.toNumber());
    
    rs::jsapi::Value result2(cx);
    cx.Call("myfunc", result2);            
    
    ASSERT_TRUE(result2.isNumber());
    ASSERT_EQ(42, result2.toNumber());
}

TEST_F(CallJSFunctionTests, test4) {
    rs::jsapi::Context cx;
    
    cx.Evaluate("var count=7;var inc=function(){count++;};var get=function(){return count;};");        
    
    rs::jsapi::Value result1(cx);
    cx.Call("get", result1);
    
    ASSERT_TRUE(result1.isNumber());
    ASSERT_EQ(7, result1.toNumber());
    
    cx.Call("inc");
    
    rs::jsapi::Value result2(cx);
    cx.Call("get", result2);            
    
    ASSERT_TRUE(result2.isNumber());
    ASSERT_EQ(8, result2.toNumber());
}

TEST_F(CallJSFunctionTests, test5) {
    rs::jsapi::Context cx;
    cx.Evaluate("var myfunc=function(n){return n;};");
    
    rs::jsapi::FunctionArguments args(cx);
    args.Append(3.14159);
    
    rs::jsapi::Value result(cx);
    cx.Call("myfunc", args, result);
    
    ASSERT_TRUE(result.isNumber());
    ASSERT_FLOAT_EQ(3.14159, result.toNumber());    
}

TEST_F(CallJSFunctionTests, test5b) {
    rs::jsapi::Context cx;
    cx.Evaluate("var myfunc=function(n){return n;};");
    
    rs::jsapi::FunctionArguments args(cx);
    args.Append(3);
    
    rs::jsapi::Value result(cx);
    cx.Call("myfunc", args, result);
    
    ASSERT_TRUE(result.isInt32());
    ASSERT_EQ(3, result.toInt32());       
}

TEST_F(CallJSFunctionTests, test5c) {
    rs::jsapi::Context cx;
    cx.Evaluate("var myfunc=function(n){return n;};");
    
    rs::jsapi::FunctionArguments args(cx);
    args.Append(7u);
    
    rs::jsapi::Value result(cx);
    cx.Call("myfunc", args, result);
    
    ASSERT_TRUE(result.isNumber());
    ASSERT_EQ(7, result.toNumber());
}

TEST_F(CallJSFunctionTests, test6) {
    rs::jsapi::Context cx;
    cx.Evaluate("var myfunc=function(n){return n;};");
    
    rs::jsapi::FunctionArguments args(cx);
    args.Append("hello");
    
    rs::jsapi::Value result(cx);
    cx.Call("myfunc", args, result);       
    
    ASSERT_TRUE(result.isString());
    ASSERT_STRCASEEQ("hello", result.ToString().c_str());
}

TEST_F(CallJSFunctionTests, test7) {
    rs::jsapi::Context cx;
    cx.Evaluate("var myfunc=function(n){return n;};");
    
    rs::jsapi::FunctionArguments args(cx);
    args.Append(true);
    
    rs::jsapi::Value result(cx);
    cx.Call("myfunc", args, result);       
    
    ASSERT_TRUE(result.isBoolean());
    ASSERT_TRUE(result.toBoolean());
}

TEST_F(CallJSFunctionTests, test8) {
    rs::jsapi::Context cx;
    cx.Evaluate("var myfunc=function(n){return n;};");
    
    rs::jsapi::FunctionArguments args(cx);
    args.Append(false);
    
    rs::jsapi::Value result(cx);
    cx.Call("myfunc", args, result);       
    
    ASSERT_TRUE(result.isBoolean());
    ASSERT_FALSE(result.toBoolean());
    
    args.Clear();
    ASSERT_TRUE(args.Empty());
    
    args.Append(true);    
    cx.Call("myfunc", args, result);       
    
    ASSERT_TRUE(result.isBoolean());
    ASSERT_TRUE(result.toBoolean());    
}