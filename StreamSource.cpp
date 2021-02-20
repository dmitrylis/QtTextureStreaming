#include "StreamSource.h"
#include "TextureProvidersStorage.h"

StreamSource::StreamSource(QQuickItem* parent) : QQuickItem(parent)
{
    setFlag(ItemHasContents, true); // Important
}

StreamSource::~StreamSource()
{
}

QString StreamSource::streamId() const
{
    return m_streamId;
}

void StreamSource::setStreamId(const QString &streamId)
{
    if (m_streamId == streamId)
    {
        return;
    }

    m_streamId = streamId;
    emit streamIdChanged(m_streamId);
}

QSGNode *StreamSource::updatePaintNode(QSGNode* oldNode, UpdatePaintNodeData* updatePaintNodeData)
{
    Q_UNUSED(updatePaintNodeData)

    TextureProvidersStorage::instance().registerTextureProvider(this);
    return oldNode;
}
