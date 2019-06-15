#ifndef QPOINTERGRABBERIMPL_P_H
#define QPOINTERGRABBERIMPL_P_H

#include "APointerGrabberImpl_p.h"
#include "grabber_export.h"

namespace grabber {
class GRABBER_SHARED_EXPORT QPointerGrabberImpl final : public APointerGrabberImpl
{
    Q_OBJECT
    friend class QPointerGrabber;
private:
    explicit QPointerGrabberImpl(QWidget *widget);
protected slots:
    void grabPointer() noexcept override;
    void ungrabPointer() noexcept override;
};
} // namespace grabber

#endif // QPOINTERGRABBERIMPL_P_H
