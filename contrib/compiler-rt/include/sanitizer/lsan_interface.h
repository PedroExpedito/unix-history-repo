//===-- sanitizer/lsan_interface.h ------------------------------*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file is a part of LeakSanitizer.
//
// Public interface header.
//===----------------------------------------------------------------------===//
#ifndef SANITIZER_LSAN_INTERFACE_H
#define SANITIZER_LSAN_INTERFACE_H

#include <sanitizer/common_interface_defs.h>

#ifdef __cplusplus
extern "C" {
#endif
  // Allocations made between calls to __lsan_disable() and __lsan_enable() will
  // be treated as non-leaks. Disable/enable pairs may be nested.
  void __lsan_disable();
  void __lsan_enable();

  // The heap object into which p points will be treated as a non-leak.
  void __lsan_ignore_object(const void *p);

  // Memory regions registered through this interface will be treated as sources
  // of live pointers during leak checking. Useful if you store pointers in
  // mapped memory.
  // Points of note:
  // - __lsan_unregister_root_region() must be called with the same pointer and
  // size that have earlier been passed to __lsan_register_root_region()
  // - LSan will skip any inaccessible memory when scanning a root region. E.g.,
  // if you map memory within a larger region that you have mprotect'ed, you can
  // register the entire large region.
  // - the implementation is not optimized for performance. This interface is
  // intended to be used for a small number of relatively static regions.
  void __lsan_register_root_region(const void *p, size_t size);
  void __lsan_unregister_root_region(const void *p, size_t size);

  // Check for leaks now. This function behaves identically to the default
  // end-of-process leak check. In particular, it will terminate the process if
  // leaks are found and the exit_code flag is non-zero.
  // Subsequent calls to this function will have no effect and end-of-process
  // leak check will not run. Effectively, end-of-process leak check is moved to
  // the time of first invocation of this function.
  // By calling this function early during process shutdown, you can instruct
  // LSan to ignore shutdown-only leaks which happen later on.
  void __lsan_do_leak_check();

  // Check for leaks now. Returns zero if no leaks have been found or if leak
  // detection is disabled, non-zero otherwise.
  // This function may be called repeatedly, e.g. to periodically check a
  // long-running process. It prints a leak report if appropriate, but does not
  // terminate the process. It does not affect the behavior of
  // __lsan_do_leak_check() or the end-of-process leak check, and is not
  // affected by them.
  int __lsan_do_recoverable_leak_check();

  // The user may optionally provide this function to disallow leak checking
  // for the program it is linked into (if the return value is non-zero). This
  // function must be defined as returning a constant value; any behavior beyond
  // that is unsupported.
  int __lsan_is_turned_off();

  // This function may be optionally provided by the user and should return
  // a string containing LSan suppressions.
  const char *__lsan_default_suppressions();
#ifdef __cplusplus
}  // extern "C"

namespace __lsan {
class ScopedDisabler {
 public:
  ScopedDisabler() { __lsan_disable(); }
  ~ScopedDisabler() { __lsan_enable(); }
};
}  // namespace __lsan
#endif

#endif  // SANITIZER_LSAN_INTERFACE_H
