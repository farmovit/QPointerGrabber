#ifndef QPOINTERGRABBER_H
#define QPOINTERGRABBER_H

#include <QWidget>
#include <memory>
#include "grabber_export.h"

namespace grabber {
class APointerGrabberImpl;
class GRABBER_SHARED_EXPORT QPointerGrabber final : public QObject
{
    Q_OBJECT
public:
    /**
     * @brief Constructs a QPointerGrabber and grabs the pointer by widget.
     * The pointer will be ungrabbed when it loses focus or the widget is destroyed.
     * The pointer will be grabbed again when it gets focus.
     * If widget is nullptr, QPointerGrabber is not valid and does nothing.
     */
    explicit QPointerGrabber(QWidget *widget);
    /**
     * @brief Destroys the QPointerGrabber
     */
    ~QPointerGrabber() override;
    /**
     * @brief Return if the pointer is grabbed by the QPointerGrabber
     */
    [[ nodiscard ]] bool isPointerGrabbed() const noexcept;
    /**
     * @brief Return if the QPointerGrabber is valid. It is not valid only when ctor gets nullptr
     */
    [[ nodiscard ]] bool isValid() const noexcept;
signals:
    /**
     * @brief Will be emitted when the pointer is successfully grabbed
     */
    void grabSuccessful();
    /**
     * @brief Will be emitted when the pointer grabbing is failed
     */
    void grabFailed();
private:
    Q_DISABLE_COPY(QPointerGrabber)
    QPointerGrabber(QPointerGrabber &&other) noexcept;
    QPointerGrabber &operator=(QPointerGrabber &&other) noexcept;
private:
    std::unique_ptr<APointerGrabberImpl> mPointerGrabberImpl;
};
} // namespace grabber

#endif // QPOINTERGRABBER_H
