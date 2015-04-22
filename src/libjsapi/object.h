#ifndef RS_JSAPI_OBJECT_H
#define	RS_JSAPI_OBJECT_H

#include <jsapi.h>

#include <initializer_list>
#include <functional>

namespace rs {
namespace jsapi {
    
class Context;
class Value;

class Object final {
public:
    typedef std::function<bool(const char* name, Value& value)> GetCallback;
    typedef std::function<bool(const char* name, const Value& value)> SetCallback;
    typedef std::pair<const char*, JSNative> Function;
    
    Object(Context& cx) = delete;
    Object(const Object&) = delete;
    
    static bool Create(Context& cx, 
        std::initializer_list<const char*> properties,
        GetCallback getter, SetCallback setter,
        std::initializer_list<Function> functions,
        Value& obj);
    
private:
    struct ClassCallbacks { GetCallback getter; SetCallback setter; };
    
    static bool Get(JSContext*, JS::HandleObject, JS::HandleId, JS::MutableHandleValue);
    static bool Set(JSContext*, JS::HandleObject, JS::HandleId, bool, JS::MutableHandleValue);
    static void Finalize(JSFreeOp* fop, JSObject* obj);

    static ClassCallbacks* GetObjectCallbacks(JSObject* obj);
    static void SetObjectCallbacks(JSObject* obj, ClassCallbacks* callbacks);
    
    static JSClass class_;
};

}}

#endif	/* RS_JSAPI_OBJECT_H */

