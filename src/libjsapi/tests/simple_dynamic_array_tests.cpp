#include <gtest/gtest.h>

#include "../libjsapi.h"

rs::jsapi::Runtime rt_;

class SimpleDynamicArrayTests : public ::testing::Test {
protected:
    virtual void SetUp() {
        
    }
    
    virtual void TearDown() {
        
    }            
};

TEST_F(SimpleDynamicArrayTests, test1) {
    auto context = rt_.NewContext();
    
    rs::jsapi::Value array(*context);    
    rs::jsapi::DynamicArray::Create(*context,
        [](int index, rs::jsapi::Value& value) { value.set(42); return true; },
        nullptr,
        []() { return 1; },
        nullptr,
        array);
    ASSERT_TRUE(!!array);
    
    rs::jsapi::Value value(*context);
    ASSERT_TRUE(JS_GetElement(*context, array, 0, value));
    ASSERT_EQ(42, value.toInt32());
    
    uint32_t length = -1;
    ASSERT_TRUE(JS_GetArrayLength(*context, array, &length));
    ASSERT_EQ(1, length);    
}

TEST_F(SimpleDynamicArrayTests, test2) {
    auto context = rt_.NewContext();
    
    rs::jsapi::Value array(*context);    
    rs::jsapi::DynamicArray::Create(*context,
        [](int index, rs::jsapi::Value& value) { value.set(index); return true; },
        nullptr,
        []() { return 10; },
        nullptr,
        array);
    ASSERT_TRUE(!!array);
    
    uint32_t length = -1;
    ASSERT_TRUE(JS_GetArrayLength(*context, array, &length));
    ASSERT_EQ(10, length);
    
    for (int i = 0; i < 10; ++i) {
        rs::jsapi::Value value(*context);
        ASSERT_TRUE(JS_GetElement(*context, array, i, value));
        ASSERT_EQ(i, value.toInt32());
    }
}

TEST_F(SimpleDynamicArrayTests, test3) {
    auto context = rt_.NewContext();
    
    rs::jsapi::Value array(*context);    
    rs::jsapi::DynamicArray::Create(*context,
        [](int index, rs::jsapi::Value& value) { value.set(index); return true; },
        nullptr,
        []() { return 10; },
        nullptr,
        array);
    ASSERT_TRUE(!!array);
    
    rt_.Evaluate("var myfunc = function(arr, n) { return arr[n]; };");
   
    for (int i = 0; i < 10; ++i) {
        rs::jsapi::FunctionArguments args(*context);
        args.Append(array);
        args.Append(i);
        
        rs::jsapi::Value result(*context);
        rt_.Call("myfunc", args, result);
        
        ASSERT_TRUE(result.isInt32());
        ASSERT_EQ(i, result.toInt32());
    }
}

TEST_F(SimpleDynamicArrayTests, test4) {
    auto context = rt_.NewContext();    
    rs::jsapi::Value array(*context);
    
    context->Evaluate("var myfunc = function(arr) { return arr.length; };");
    
    for (int i = 0; i < 100; ++i) {
        rs::jsapi::DynamicArray::Create(*context,
            [](int index, rs::jsapi::Value& value) { value.set(index); return true; },
            nullptr,
            [&]() { return i; },
            nullptr,
            array);
        ASSERT_TRUE(!!array);

        rs::jsapi::FunctionArguments args(*context);
        args.Append(array);
        
        rs::jsapi::Value result(*context);
        context->Call("myfunc", args, result);

        ASSERT_TRUE(result.isInt32());
        ASSERT_EQ(i, result.toInt32());
    }
}

TEST_F(SimpleDynamicArrayTests, test5) {    
    auto count = 0;
    
    if (true) {
        auto context = rt_.NewContext();
        
        rs::jsapi::Value obj(*context);
        rs::jsapi::DynamicArray::Create(
            *context, 
            nullptr, 
            nullptr, 
            nullptr,
            [&]() { ++count; },
            obj);
        ASSERT_TRUE(!!obj);
    }
    
    ASSERT_EQ(1, count);
}

TEST_F(SimpleDynamicArrayTests, test6) {
    auto context = rt_.NewContext();
    
    rs::jsapi::Value array(*context);    
    rs::jsapi::DynamicArray::Create(*context,
        [](int index, rs::jsapi::Value& value) { value.set(index); return true; },
        nullptr,
        []() { return 10; },
        nullptr,
        array);
    ASSERT_TRUE(!!array);
    
    rt_.Evaluate("var myfunc = function(arr, n) { return arr[n]; };");
   
    for (int i = 0; i < 10; ++i) {
        rs::jsapi::FunctionArguments args(*context);
        args.Append(array);
        args.Append(std::to_string(i));
        
        rs::jsapi::Value result(*context);
        rt_.Call("myfunc", args, result);
        
        ASSERT_TRUE(result.isInt32());
        ASSERT_EQ(i, result.toInt32());
    }
}

TEST_F(SimpleDynamicArrayTests, test7) {
    auto context = rt_.NewContext();
    
    rs::jsapi::Value array(*context);    
    rs::jsapi::DynamicArray::Create(*context,
        [](int index, rs::jsapi::Value& value) { value.set(index); return true; },
        nullptr,
        []() { return 10; },
        nullptr,
        array);
    ASSERT_TRUE(!!array);
    
    rt_.Evaluate("var myfunc = function(arr, n) { return arr[n]; };");
   
    for (int i = 0; i < 10; ++i) {
        rs::jsapi::FunctionArguments args(*context);
        args.Append(array);
        args.Append("abc");
        
        rs::jsapi::Value result(*context);
        rt_.Call("myfunc", args, result);
        
        ASSERT_TRUE(result.isUndefined());
    }
}