#include "QPointerGrabber.h"
#ifdef _WIN32
#include "win/WinPointerGrabberImpl_p.h"
#endif
#ifdef linux
#include "lin/LinuxPointerGrabberImpl_p.h"
#endif

namespace grabber {
QPointerGrabber::QPointerGrabber(QWidget *widget)
    : QObject(nullptr),
      mPointerGrabberImpl(new QPointerGrabberImpl(widget)) {
    connect(mPointerGrabberImpl.get(), &QPointerGrabberImpl::grabSuccessful,
            this, &QPointerGrabber::grabSuccessful);
    connect(mPointerGrabberImpl.get(), &QPointerGrabberImpl::grabFailed,
            this, &QPointerGrabber::grabFailed);
}

bool QPointerGrabber::isPointerGrabbed() const noexcept {
    return mPointerGrabberImpl->isPointerGrabbed();
}

bool QPointerGrabber::isValid() const noexcept {
    return mPointerGrabberImpl->isValid();
}

QPointerGrabber::QPointerGrabber(QPointerGrabber &&other) noexcept
    : mPointerGrabberImpl(std::move(other.mPointerGrabberImpl)) {
}

QPointerGrabber &QPointerGrabber::operator=(QPointerGrabber &&other) noexcept {
    mPointerGrabberImpl = std::move(other.mPointerGrabberImpl);
    return *this;
}

QPointerGrabber::~QPointerGrabber() = default;

} // namespace grabber 
