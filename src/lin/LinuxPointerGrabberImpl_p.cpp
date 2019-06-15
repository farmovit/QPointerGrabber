#include "LinuxPointerGrabberImpl_p.h"
#include "FiniteTimer_p.h"
#include <X11/Xlib.h>
#include <QX11Info>

using namespace std::literals;
namespace {
constexpr auto grabRetryTimeout = 20ms;
constexpr auto grabDefaultTryDuration = 4000ms;
} // namespace

namespace grabber {
QPointerGrabberImpl::QPointerGrabberImpl(QWidget *widget)
    : APointerGrabberImpl(widget),
      mFiniteTimer(new FiniteTimer(grabDefaultTryDuration, this)) {
}

void QPointerGrabberImpl::ungrabPointer() {
    stopTimer();
    if (QX11Info::display() == nullptr
            || !isPointerGrabbed()) {
        return;
    }
    XUngrabPointer(QX11Info::display(), CurrentTime);
    XFlush(QX11Info::display());
    setIsPointerGrabbed(false);
}

void QPointerGrabberImpl::stopTimer() {
    mFiniteTimer->stop();
    disconnect(mFiniteTimer, &FiniteTimer::timeout, nullptr, nullptr);
    disconnect(mFiniteTimer, &FiniteTimer::durationEnded, nullptr, nullptr);
}

void QPointerGrabberImpl::grabPointer() {
    if (QX11Info::display() == nullptr
            || !isValid() || isPointerGrabbed()) {
        return;
    }
    stopTimer();
    connect(mFiniteTimer, &FiniteTimer::durationEnded, this, &QPointerGrabberImpl::grabFailed);
    connect(mFiniteTimer, &FiniteTimer::timeout, this, &QPointerGrabberImpl::grabPointerImpl);
    mFiniteTimer->setInterval(grabRetryTimeout);
    mFiniteTimer->start();
}

void QPointerGrabberImpl::grabPointerImpl() {
    if (QX11Info::display() == nullptr
            || !isValid() || isPointerGrabbed()) {
        return;
    }
    const auto &result = XGrabPointer(QX11Info::display(), QX11Info::appRootWindow(), True,
                               None, GrabModeAsync, GrabModeAsync, windowId(),
                               None, CurrentTime);
    if (result == GrabSuccess) {
        stopTimer();
        setIsPointerGrabbed(true);
        emit grabSuccessful();
    }
}
} // namespace grabber
