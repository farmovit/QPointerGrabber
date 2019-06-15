#include "FiniteTimer_p.h"

namespace grabber {
FiniteTimer::FiniteTimer(std::chrono::milliseconds duration, QObject *parent)
    : QTimer(parent),
      mDuration(duration) {
}

void FiniteTimer::start() {
    disconnect(this, &QTimer::timeout, nullptr, nullptr);
    const auto timePointUntil = std::chrono::steady_clock::now() + mDuration;
    connect(this, &QTimer::timeout, this, [=]() {
        if (std::chrono::steady_clock::now() >= timePointUntil) {
            stop();
            emit durationEnded();
        }
        emit timeout();
    });
    QTimer::start();
}
} // namespace grabber
