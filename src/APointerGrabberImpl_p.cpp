#include "APointerGrabberImpl_p.h"
#include "WindowEventsWatcher_p.h"

namespace grabber {

APointerGrabberImpl::APointerGrabberImpl(QWidget *widget)
    : mIsGrabbed(false),
      mWindowId({}),
      mWindowEventsWatcher(std::make_unique<WindowEventsWatcher>()) {
    initialize(widget);
}

APointerGrabberImpl::APointerGrabberImpl(APointerGrabberImpl &&other) noexcept
    : mIsGrabbed(other.mIsGrabbed),
      mWindowId(other.mWindowId),
      mWindowEventsWatcher(std::move(other.mWindowEventsWatcher)) {
}

APointerGrabberImpl &APointerGrabberImpl::operator=(APointerGrabberImpl &&other) noexcept {
    mIsGrabbed = other.mIsGrabbed;
    mWindowId = other.mWindowId;
    mWindowEventsWatcher = std::move(other.mWindowEventsWatcher);
    return *this;
}

APointerGrabberImpl::~APointerGrabberImpl() = default;

void APointerGrabberImpl::initialize(QWidget *widget) noexcept {
    if (widget == nullptr) {
        return;
    }
    connect(mWindowEventsWatcher.get(), &WindowEventsWatcher::windowViewable,
            this, &APointerGrabberImpl::grabPointer);
    connect(mWindowEventsWatcher.get(), &WindowEventsWatcher::windowUnviewable,
            this, &APointerGrabberImpl::ungrabPointer);
    widget->installEventFilter(mWindowEventsWatcher.get());
    mWindowId = widget->winId();
    if (widget->hasFocus()) {
        grabPointer();
    }
}

bool APointerGrabberImpl::isPointerGrabbed() const noexcept {
    return mIsGrabbed;
}

bool APointerGrabberImpl::isValid() const noexcept {
    return mWindowId.has_value();
}

void APointerGrabberImpl::setIsPointerGrabbed(bool isGrabbed) noexcept {
    mIsGrabbed = isGrabbed;
}

WId APointerGrabberImpl::windowId() const noexcept {
    try {
        return mWindowId.value();
    } catch (const std::exception &e) {
        Q_UNUSED(e)
        return 0;
    }
}

} // namespace grabber
