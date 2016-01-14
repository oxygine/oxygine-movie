#pragma once
#include "MovieSprite.h"
#include "core/file.h"
#include "pthread.h"
#include "core/ThreadMessages.h"

namespace oxygine
{
    class OggDecoder;
    class OggDecoder2;

    class MovieSpriteTheora: public MovieSprite
    {
    public:
        MovieSpriteTheora();
        ~MovieSpriteTheora();

    protected:
        static void* _thread(void* This);
        void _threadThis();

        void _initPlayer() OVERRIDE;
        void _play() OVERRIDE;
        void _pause() OVERRIDE;
        void _resume() OVERRIDE;
        void _setVolume(float v)  OVERRIDE;
        void _stop() OVERRIDE;
        bool _isPlaying() const  OVERRIDE;
        void _clear() OVERRIDE;
        void _update(const UpdateState&) OVERRIDE;

        OggDecoder* _decoder;
        file::handle _file;
        pthread_t _threadID;

        ThreadMessages _msg;
    };
}