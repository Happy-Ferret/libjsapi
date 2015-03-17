#include "runtime.h"
#include "context.h"

std::atomic<int> rs::jsapi::Runtime::Instance::count_;
std::mutex rs::jsapi::Runtime::Instance::m_;

rs::jsapi::Runtime::Instance::Instance() {
    if (count_ == 0) {
        std::lock_guard<std::mutex> lk(m_);
        if (count_ == 0) {
            JS_Init();
            count_ += 1;
        }
    } else {
        count_ += 1;
    }   
}

rs::jsapi::Runtime::Instance::~Instance() {
    count_ -= 1;
    
    if (count_ == 0) {
        JS_ShutDown();
    }
}

rs::jsapi::Runtime::Runtime() :
    rt_(JS_NewRuntime(8L * 1024L * 1024L, JSUseHelperThreads::JS_USE_HELPER_THREADS)),
    cx_(*this) {
}

rs::jsapi::Runtime::~Runtime() {
    cx_.DestroyContext();
    JS_DestroyRuntime(rt_);
}

std::unique_ptr<rs::jsapi::Context> rs::jsapi::Runtime::NewContext() {
    return std::unique_ptr<Context>(new Context(*this));
}

bool rs::jsapi::Runtime::HasError() {
    return cx_.HasError();
}

const std::string& rs::jsapi::Runtime::getError() {
    return cx_.getError();
}

bool rs::jsapi::Runtime::ClearError() {
    return cx_.ClearError();
}