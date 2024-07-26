#ifndef WARNING_IGNORE_HPP
#define WARNING_IGNORE_HPP

#ifdef __clang__
#define DO_PRAGMA(x) _Pragma(#x)
#define PRAGMA_DIAGNOSTIC(x) DO_PRAGMA(clang diagnostic x)
#elifdef __GNUC__
#define PRAGMA_DIAGNOSTIC(x) DO_PRAGMA(GCC diagnostic x)
#endif
#define WARNING_IGNORE_HEADER(type) \
PRAGMA_DIAGNOSTIC(push) \
PRAGMA_DIAGNOSTIC(ignored #type)
#define WARNING_IGNORE_TAIL PRAGMA_DIAGNOSTIC(pop)

#endif /* WARNING_IGNORE_HPP */
