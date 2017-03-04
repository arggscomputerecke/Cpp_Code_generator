#ifndef platform_h__
#define platform_h__
#include <memory>
#ifdef WIN32 
#ifndef __CINT__
#define DllExport   __declspec( dllexport )
#define __OVERIDE__ override
#else
#define DllExport   
#define __OVERIDE__ 
#endif // __CINT__
#else 
#define DllExport   
#define __OVERIDE__ 
#endif // WIN32

#define Unew __unew_start << new 
enum _unew_ {
  __unew_start
};

template <typename T>
auto operator<<(_unew_, T* in_) {
  return std::unique_ptr<T>(in_);
}




#endif // platform_h__
