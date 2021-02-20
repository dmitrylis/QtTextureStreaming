#include "TextureProvidersStorage.h"
#include "StreamSource.h"

#include <QSGTextureProvider>

TextureProvidersStorage &TextureProvidersStorage::instance()
{
    static TextureProvidersStorage textureStorage;
    return textureStorage;
}

bool TextureProvidersStorage::registerTextureProvider(StreamSource *streamSource)
{
    if (!streamSource || !streamSource->isTextureProvider() || streamSource->streamId().isEmpty())
    {
        return false;
    }

    m_textureProvidersMap.insert(streamSource->streamId(), streamSource->textureProvider());
    return true;
}

QSGTextureProvider *TextureProvidersStorage::textureProvider(const QString &streamId) const
{
    return m_textureProvidersMap.value(streamId, nullptr);
}
