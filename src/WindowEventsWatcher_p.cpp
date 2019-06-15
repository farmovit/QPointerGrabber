#include "WindowEventsWatcher_p.h"
#include <QEvent>

namespace grabber {
WindowEventsWatcher::WindowEventsWatcher(QObject *parent)
    : QObject(parent) {
}

bool WindowEventsWatcher::eventFilter(QObject *obj, QEvent *event) {
    Q_UNUSED(obj)
    if (event->type() == QEvent::FocusIn
            || event->type() == QEvent::WindowActivate
            || event->type() == QEvent::Resize) {
        emit windowViewable();
    }
    else if (event->type() == QEvent::FocusOut
             || event->type() == QEvent::WindowDeactivate) {
        emit windowUnviewable();
    }
    return false;
}
} // namespace grabber
