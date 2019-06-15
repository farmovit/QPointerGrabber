#include "WinPointerGrabberImpl_p.h"
#include <windef.h>
#include <winuser.h>

namespace grabber {
QPointerGrabberImpl::QPointerGrabberImpl(QWidget *widget) {
    initialize(widget);
}

void QPointerGrabberImpl::grabPointer() noexcept {
    if (!isValid()) {
        return;
    }
    RECT lpRect;
    if (!GetWindowRect(reinterpret_cast<HWND>(windowId()), &lpRect)) {
        emit grabFailed();
        return;
    }
    if (ClipCursor(&lpRect)) {
        setIsPointerGrabbed(true);
        emit grabSuccessful();
    } else {
        emit grabFailed();
    }
}

void QPointerGrabberImpl::ungrabPointer() noexcept {
    if (isPointerGrabbed() && ClipCursor(nullptr)) {
        setIsPointerGrabbed(false);
    }
}

}// namespace grabber
