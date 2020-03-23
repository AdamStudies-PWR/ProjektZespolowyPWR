#ifndef HTTP_GLOBAL_H
#define HTTP_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(HTTP_LIBRARY)
#  define HTTP_EXPORT Q_DECL_EXPORT
#else
#  define HTTP_EXPORT Q_DECL_IMPORT
#endif

#endif // HTTP_GLOBAL_H
