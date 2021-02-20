#include "FpsCounter.h"

#include <QQuickWindow>

FpsCounter::FpsCounter(QQuickItem *parent) :
    QQuickItem(parent),
    m_counter(0),
    m_interval(1000)
{
    connect(this, &FpsCounter::windowChanged, this, &FpsCounter::handleWindowChanged);
}

int FpsCounter::fps() const
{
    return m_fps;
}

void FpsCounter::setFps(int fps)
{
    if (m_fps == fps)
    {
        return;
    }

    m_fps = fps;
    emit fpsChanged();
}

int FpsCounter::interval() const
{
    return m_interval;
}

void FpsCounter::setInterval(int msec)
{
    if (m_interval == msec)
    {
        return;
    }

    m_interval = msec;
    emit intervalChanged();
}

void FpsCounter::handleAfterRendering()
{
    const int elapsedMsec = static_cast<int>(m_timer.elapsed());

    m_counter++;

    if (elapsedMsec >= m_interval)
    {
        setFps(static_cast<int>(m_counter / (elapsedMsec / 1000.0)));

        m_counter = 0;
        m_timer.restart();
    }
}

void FpsCounter::handleWindowChanged(QQuickWindow *window)
{
    if (m_windowConnection)
    {
        this->disconnect(m_windowConnection);
    }

    if (window)
    {
        m_timer.restart();
        m_windowConnection = connect(window, &QQuickWindow::afterRendering, this, &FpsCounter::handleAfterRendering);
    }
}
