#ifndef FPSCOUNTER_H
#define FPSCOUNTER_H

#include <QQuickItem>
#include <QElapsedTimer>
#include <QMetaObject>

class QQuickWindow;

class FpsCounter : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(int fps READ fps NOTIFY fpsChanged)
    Q_PROPERTY(int interval READ interval WRITE setInterval NOTIFY intervalChanged)

public:
    explicit FpsCounter(QQuickItem *parent = nullptr);

    int fps() const;
    void setFps(int fps);
    int interval() const;
    void setInterval(int msec);

signals:
    void fpsChanged();
    void intervalChanged();

public slots:
    void handleAfterRendering();
    void handleWindowChanged(QQuickWindow *window);

protected:
    QMetaObject::Connection m_windowConnection;
    QElapsedTimer m_timer;
    int m_fps;
    int m_counter;
    int m_interval;
};

#endif // FPSCOUNTER_H
