#ifndef STREAMTARGET_H
#define STREAMTARGET_H

#include <QQuickItem>
#include <QTimer>

class QSGTextureProvider;

class StreamTarget : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(QString streamId READ streamId WRITE setStreamId NOTIFY streamIdChanged)

public:
    explicit StreamTarget(QQuickItem* parent = nullptr);
    ~StreamTarget() override;

    QString streamId() const;

signals:
    void streamIdChanged(const QString &streamId);
    void startWatchDog() const;
    void stopWatchDog() const;

public slots:
    void setStreamId(const QString &streamId);

protected:
    void forceFetchTextureProvider();
    void fetchTextureProvider();

    QSGNode *updatePaintNode(QSGNode *, UpdatePaintNodeData *) override;

private:
    QString m_streamId;
    QSGTextureProvider *m_textureProvider;
    QTimer m_watchDog;
};

#endif // STREAMTARGET_H
