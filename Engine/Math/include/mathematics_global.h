#ifndef MATHEMATICS_GLOBAL_H
#define MATHEMATICS_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(MATHEMATICS_LIBRARY)
#  define MATHEMATICSSHARED_EXPORT Q_DECL_EXPORT
#else
#  define MATHEMATICSSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // MATHEMATICS_GLOBAL_H
