#ifndef GRABBER_EXPORT_H
#define GRABBER_EXPORT_H

#include <QtGlobal>

#if defined(cursorGrabber_SHARED_LIBRARY)
#  define GRABBER_SHARED_EXPORT Q_DECL_EXPORT
#else
#  define GRABBER_SHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // GRABBER_EXPORT_H
