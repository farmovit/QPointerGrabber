#ifndef GRABBERTEST_H
#define GRABBERTEST_H

#include <QPushButton>
#include "QPointerGrabber.h"

class GrabberTest : public QObject
{
    Q_OBJECT
public:
    explicit GrabberTest(QObject *parent = nullptr);
private slots:
    void grabTest();
    void ungrabTest();
    void multiWidgetsGrabTest();
private:
    void checkIfCursorIsGrabbed(QPushButton *button, const QPoint &limitPoint, const grabber::QPointerGrabber *grabber);
    void checkIfCursorIsNotGrabbed(QPushButton *button, const QPoint &limitPoint, const grabber::QPointerGrabber *grabber);
private:
    std::unique_ptr<QPushButton> mFirstButton;
    std::unique_ptr<QPushButton> mSecondButton;
    grabber::QPointerGrabber mFirstGrabber;
    std::unique_ptr<grabber::QPointerGrabber> mSecondGrabber;
};

#endif // GRABBERTEST_H
