#include "StreamTarget.h"
#include "TextureProvidersStorage.h"

#include <QSGTextureProvider>
#include <QSGSimpleTextureNode>

StreamTarget::StreamTarget(QQuickItem* parent)
    : QQuickItem(parent)
    , m_textureProvider(nullptr)
{
    setFlag(ItemHasContents, true); // Important

    m_watchDog.setInterval(33);

    connect(this, &StreamTarget::startWatchDog, &m_watchDog, QOverload<>::of(&QTimer::start));
    connect(&m_watchDog, &QTimer::timeout, this, &StreamTarget::fetchTextureProvider);
    connect(this, &StreamTarget::stopWatchDog, &m_watchDog, &QTimer::stop);
}

StreamTarget::~StreamTarget()
{
}

QString StreamTarget::streamId() const
{
    return m_streamId;
}

void StreamTarget::setStreamId(const QString &streamId)
{
    if (m_streamId == streamId)
    {
        return;
    }

    m_streamId = streamId;
    emit streamIdChanged(m_streamId);

    forceFetchTextureProvider();
}

void StreamTarget::forceFetchTextureProvider()
{
    m_textureProvider = TextureProvidersStorage::instance().textureProvider(m_streamId);

    if (m_textureProvider)
    {
        update();
    }
}

void StreamTarget::fetchTextureProvider()
{
    if (!m_textureProvider)
    {
        forceFetchTextureProvider();
    }
}

QSGNode *StreamTarget::updatePaintNode(QSGNode* oldNode, UpdatePaintNodeData* updatePaintNodeData)
{
    Q_UNUSED(updatePaintNodeData)

    if (!m_textureProvider)
    {
        if (!m_watchDog.isActive())
        {
            emit startWatchDog();
        }

        return oldNode;
    }
    else if (m_watchDog.isActive())
    {
        emit stopWatchDog();
    }

    QSGSimpleTextureNode *node = dynamic_cast<QSGSimpleTextureNode *>(oldNode);
    if (!node)
    {
        node = new QSGSimpleTextureNode();
        node->setRect(boundingRect());
        node->setTexture(m_textureProvider->texture());
        node->markDirty(QSGNode::DirtyMaterial);

        connect(m_textureProvider, &QSGTextureProvider::textureChanged, this, &QQuickItem::update);
    }
    else
    {
        node->markDirty(QSGNode::DirtyMaterial);
    }

    return node;
}
