#ifndef FINITETIMER_P_H
#define FINITETIMER_P_H

#include <QTimer>

namespace grabber {
class FiniteTimer : public QTimer
{
    Q_OBJECT
public:
    explicit FiniteTimer(std::chrono::milliseconds duration, QObject *parent = nullptr);
signals:
    void durationEnded();
    void timeout();
public slots:
    void start();
private:
    std::chrono::milliseconds mDuration;
};
} // namespace grabber
#endif // FINITETIMER_P_H
