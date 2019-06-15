#ifndef QPOINTERGRABBERIMPL_P_H
#define QPOINTERGRABBERIMPL_P_H

#include "APointerGrabberImpl_p.h"
#include "grabber_export.h"

namespace grabber {
class FiniteTimer;
class GRABBER_SHARED_EXPORT QPointerGrabberImpl final: public APointerGrabberImpl
{
    Q_OBJECT
    friend class QPointerGrabber;
private:
    explicit QPointerGrabberImpl(QWidget *widget);
protected slots:
    void grabPointer();
    void ungrabPointer();
private slots:
    void stopTimer();
    void grabPointerImpl();
private:
    FiniteTimer *mFiniteTimer;
};
} // namespace grabber

#endif // QPOINTERGRABBERIMPL_P_H
