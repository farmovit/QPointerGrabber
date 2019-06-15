#ifndef WINDOWEVENTSWATCHER_P_H
#define WINDOWEVENTSWATCHER_P_H

#include <QObject>
#include "grabber_export.h"

namespace grabber {
class GRABBER_SHARED_EXPORT WindowEventsWatcher : public QObject
{
    Q_OBJECT
public:
    explicit WindowEventsWatcher(QObject *parent = nullptr);
    bool eventFilter(QObject *obj, QEvent *event) override;
signals:
    void windowViewable();
    void windowUnviewable();
};
} // namespace grabber

#endif // WINDOWEVENTSWATCHER_P_H
