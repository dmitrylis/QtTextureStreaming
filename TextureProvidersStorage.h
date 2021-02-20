#ifndef TEXTUREPROVIDERSSTORAGE_H
#define TEXTUREPROVIDERSSTORAGE_H

#include <QMap>

class StreamSource;
class QSGTextureProvider;

class TextureProvidersStorage
{
public:
    static TextureProvidersStorage &instance();

    bool registerTextureProvider(StreamSource *streamSource);
    QSGTextureProvider *textureProvider(const QString &streamId) const;

private:
    explicit TextureProvidersStorage() {}

private:
    QMap<QString, QSGTextureProvider *> m_textureProvidersMap;
};

#endif // TEXTUREPROVIDERSSTORAGE_H
