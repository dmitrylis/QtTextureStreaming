#ifndef STREAMSOURCE_H
#define STREAMSOURCE_H

#include <QQuickItem>

class StreamSource : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(QString streamId READ streamId WRITE setStreamId NOTIFY streamIdChanged)

public:
    explicit StreamSource(QQuickItem* parent = nullptr);
    ~StreamSource() override;

    QString streamId() const;

public slots:
    void setStreamId(const QString &streamId);

signals:
    void streamIdChanged(const QString &streamId);

protected:
    QSGNode *updatePaintNode(QSGNode *oldNode, UpdatePaintNodeData *updatePaintNodeData) override;

private:
    QString m_streamId;
};

#endif // STREAMSOURCE_H
