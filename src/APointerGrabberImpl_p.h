#ifndef APOINTERGRABBERIMPL_P_H
#define APOINTERGRABBERIMPL_P_H

#include <QWidget>
#include <qwindowdefs.h>
#include <memory>
#include "grabber_export.h"

namespace grabber {
class WindowEventsWatcher;
class GRABBER_SHARED_EXPORT APointerGrabberImpl : public QObject
{
    Q_OBJECT
public:
    bool isPointerGrabbed() const noexcept;
    bool isValid() const noexcept;
protected slots:
    virtual void grabPointer() = 0;
    virtual void ungrabPointer() = 0;
protected:
    void initialize(QWidget *widget) noexcept;
    void setIsPointerGrabbed(bool isGrabbed) noexcept;
    WId windowId() const noexcept;
public:
    explicit APointerGrabberImpl(QWidget *widget);
    ~APointerGrabberImpl() override;
    Q_DISABLE_COPY(APointerGrabberImpl)
    APointerGrabberImpl(APointerGrabberImpl &&other) noexcept;
    APointerGrabberImpl &operator=(APointerGrabberImpl &&other) noexcept;
signals:
    void grabSuccessful();
    void grabFailed();
private:
    bool mIsGrabbed;
    std::optional<WId> mWindowId;
    std::unique_ptr<WindowEventsWatcher> mWindowEventsWatcher;
};
} // namespace grabber

#endif // APOINTERGRABBERIMPL_P_H
