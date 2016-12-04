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

#ifndef RS_JSAPI_CONTEXT_THREAD_GUARD_H
#define RS_JSAPI_CONTEXT_THREAD_GUARD_H

#include <atomic>
#include <thread>
#include <mutex>
#include <vector>

namespace rs {
namespace jsapi {

class ContextThreadGuard {
public:
    ContextThreadGuard() : ContextThreadGuard(std::this_thread::get_id()) {}
    ContextThreadGuard(std::thread::id id);
    
    ~ContextThreadGuard() {
        RemoveThread();
    }
    
    static bool AddThread(std::thread::id id);
    static bool RemoveThread(std::thread::id id);
    static bool RemoveThread();
    
private:
    static std::vector<std::thread::id> activeThreads_;
    static std::mutex activeThreadsLock_;    
};

}}

#endif	/* RS_JSAPI_CONTEXT_THREAD_GUARD_H */

