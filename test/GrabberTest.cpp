#include "QPointerGrabber.h"
#include <QtTest>
#include <QPushButton>

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

namespace {
constexpr auto firstWidgetSize = QSize(200, 200);
constexpr auto firstWidgetGeometry = QRect(QPoint(100, 100), firstWidgetSize);
constexpr auto firstWidgetOutsidePoint = QPoint(400, 100);
constexpr auto secondWidgetSize = firstWidgetSize;
constexpr auto secondWidgetGeometry = QRect(QPoint(500, 100), secondWidgetSize);
constexpr auto secondWidgetOutsidePoint = QPoint(800, 100);
constexpr auto outsidePoint = QPoint(500, 500);
constexpr auto waitSpyTimeMs = 3000;
} // namespace

GrabberTest::GrabberTest(QObject *parent)
    : QObject(parent),
      mFirstButton(std::make_unique<QPushButton>(QStringLiteral("firstWidget"))),
      mSecondButton(std::make_unique<QPushButton>(QStringLiteral("secondWidget"))),
      mFirstGrabber(mFirstButton.get()) {
    mFirstButton->setGeometry(firstWidgetGeometry);
    mFirstButton->setWindowFlag(Qt::FramelessWindowHint);
    mSecondGrabber = std::make_unique<grabber::QPointerGrabber>(mSecondButton.get());
    mSecondButton->setGeometry(secondWidgetGeometry);
    mSecondButton->setWindowFlag(Qt::FramelessWindowHint);
}

void GrabberTest::checkIfCursorIsGrabbed(QPushButton *button, const QPoint &limitPoint, const grabber::QPointerGrabber *grabber) {
    QEventLoop blockThread;
    QTimer::singleShot(20, this, [=]() {
        QVERIFY2(grabber->isPointerGrabbed(), QByteArrayLiteral("Cursor is not grabbed but must be"));
        QVERIFY2(!button->geometry().contains(button->mapToGlobal(limitPoint)), QByteArrayLiteral("Geometry contains outside point"));
        QCursor::setPos(limitPoint);
        QVERIFY2(button->geometry().contains(QCursor::pos()), QByteArrayLiteral("Geometry does not contain cursor"));
        QSignalSpy buttonClickedSpy(button, &QPushButton::clicked);
        QTest::mouseClick(button, Qt::LeftButton, Qt::NoModifier, QPoint(0, 0));
        QCOMPARE(buttonClickedSpy.count(), 1);
    });
    QTimer::singleShot(25, &blockThread, &QEventLoop::quit);
    blockThread.exec();
}

void GrabberTest::checkIfCursorIsNotGrabbed(QPushButton *button, const QPoint &limitPoint, const grabber::QPointerGrabber *grabber) {
    QEventLoop blockThread;
    QTimer::singleShot(20, this, [=]() {
        QVERIFY2(!grabber->isPointerGrabbed(), QByteArrayLiteral("Cursor is grabbed but must not"));
        QVERIFY2(!button->geometry().contains(button->mapToGlobal(limitPoint)), QByteArrayLiteral("Geometry contains outside point"));
        QCursor::setPos(limitPoint);
        QVERIFY2(!button->geometry().contains(QCursor::pos()), QByteArrayLiteral("Geometry contains cursor"));
    });
    QTimer::singleShot(25, &blockThread, &QEventLoop::quit);
    blockThread.exec();
}

void GrabberTest::grabTest() {
    QVERIFY2(!mFirstGrabber.isPointerGrabbed(), QByteArrayLiteral("Cursor is grabbed but must not"));
    QCursor::setPos(mFirstButton->mapToGlobal(firstWidgetOutsidePoint));
    mFirstButton->show();
    if (!mFirstGrabber.isPointerGrabbed()) {
        QSignalSpy successfulGrabSignalSpy(&mFirstGrabber, &grabber::QPointerGrabber::grabSuccessful);
        QVERIFY2(successfulGrabSignalSpy.wait(waitSpyTimeMs), QByteArrayLiteral("Cannot wait for grabSuccessful signal"));
        QVERIFY(successfulGrabSignalSpy.count() >= 1);
    }
    checkIfCursorIsGrabbed(mFirstButton.get(), firstWidgetOutsidePoint, &mFirstGrabber);
}

void GrabberTest::ungrabTest() {
    mFirstButton->hide();
    mSecondButton->hide();
    checkIfCursorIsNotGrabbed(mFirstButton.get(), firstWidgetOutsidePoint, &mFirstGrabber);
    checkIfCursorIsNotGrabbed(mSecondButton.get(), secondWidgetOutsidePoint, mSecondGrabber.get());
}

void GrabberTest::multiWidgetsGrabTest() {
    mFirstButton->hide();
    mSecondButton->hide();
    checkIfCursorIsNotGrabbed(mFirstButton.get(), firstWidgetOutsidePoint, &mFirstGrabber);
    checkIfCursorIsNotGrabbed(mSecondButton.get(), secondWidgetOutsidePoint, mSecondGrabber.get());
    QCursor::setPos(mFirstButton->mapToGlobal(firstWidgetOutsidePoint));
    mFirstButton->show();
    if (!mFirstGrabber.isPointerGrabbed()) {
        QSignalSpy firstSuccessfulGrabSignalSpy(&mFirstGrabber, &grabber::QPointerGrabber::grabSuccessful);
        QVERIFY2(firstSuccessfulGrabSignalSpy.wait(waitSpyTimeMs), QByteArrayLiteral("Cannot wait for grabSuccessful signal"));
        QVERIFY(firstSuccessfulGrabSignalSpy.count() >= 1);
    }
    checkIfCursorIsGrabbed(mFirstButton.get(), firstWidgetOutsidePoint, &mFirstGrabber);
    checkIfCursorIsNotGrabbed(mSecondButton.get(), secondWidgetOutsidePoint, mSecondGrabber.get());
    mSecondButton->show();
    mSecondButton->setFocus();
    if (!mSecondGrabber->isPointerGrabbed()) {
        QSignalSpy secondSuccessfulGrabSignalSpy(mSecondGrabber.get(), &grabber::QPointerGrabber::grabSuccessful);
        QVERIFY2(secondSuccessfulGrabSignalSpy.wait(waitSpyTimeMs), QByteArrayLiteral("Cannot wait for grabSuccessful signal"));
        QVERIFY(secondSuccessfulGrabSignalSpy.count() >= 1);
    }
    checkIfCursorIsNotGrabbed(mFirstButton.get(), firstWidgetOutsidePoint, &mFirstGrabber);
    checkIfCursorIsGrabbed(mSecondButton.get(), secondWidgetOutsidePoint, mSecondGrabber.get());
    mSecondButton->hide();
    checkIfCursorIsNotGrabbed(mSecondButton.get(), secondWidgetOutsidePoint, mSecondGrabber.get());
    checkIfCursorIsGrabbed(mFirstButton.get(), firstWidgetOutsidePoint, &mFirstGrabber);
    mFirstButton->hide();
    checkIfCursorIsNotGrabbed(mFirstButton.get(), firstWidgetOutsidePoint, &mFirstGrabber);
    checkIfCursorIsNotGrabbed(mSecondButton.get(), secondWidgetOutsidePoint, mSecondGrabber.get());
    QCursor::setPos(outsidePoint);
    QVERIFY2(QCursor::pos() == outsidePoint, QByteArrayLiteral("Cursor is still grabbed"));
}

QTEST_MAIN(GrabberTest)

#include "GrabberTest.moc"
