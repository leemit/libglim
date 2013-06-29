#include <functional>
namespace glim {

// http://stackoverflow.com/questions/2121607/any-raii-template-in-boost-or-c0x/

/** RAII helper. Keeps the functor and runs it in the destructor. */
template<typename Fun> struct RAIIFun {
  Fun _fun;
  RAIIFun (RAIIFun&&) = default;
  RAIIFun (const RAIIFun&) = default;
  template<typename FunArg> RAIIFun (FunArg fun): _fun (std::forward<Fun> (fun)) {}
  ~RAIIFun() {_fun();}
};

/**
 * Runs the given functor when going out of scope.
 * Example: \code
 *   auto closeFd = raiiFun ([&]() {close (fd);});
 *   auto unmap = raiiFun ([&]() {munmap (fd, size);});
 * \endcode
 */
template<typename Fun> RAIIFun<Fun> raiiFun (const Fun& fun) {return RAIIFun<Fun> (fun);}

/**
 * Runs the given functor when going out of scope.
 * Example: \code
 *   auto closeFd = raiiFun ([&]() {close (fd);});
 *   auto unmap = raiiFun ([&]() {munmap (fd, size);});
 * \endcode
 */
template<typename Fun> RAIIFun<Fun> raiiFun (Fun&& fun) {return RAIIFun<Fun> (std::move (fun));}

}
