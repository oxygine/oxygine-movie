#include "MovieSprite.h"

#include "vlc/libvlc.h"
#include "vlc/libvlc_media.h"
#include "vlc/libvlc_media_player.h"


#define PLAYER_NOT_NULL(rt)  OX_ASSERT(_player); if (!_player) return rt;

namespace oxygine
{
    libvlc_instance_t* libvlc = 0;

    typedef struct libvlc_media_player_t libvlc_media_player_t;
    typedef struct libvlc_media_t libvlc_media_t;


    void MovieSprite::init()
    {
        OX_ASSERT(libvlc == 0);

        char const* argv[] =
        {
            //"--no-audio", /* skip any audio track */
            "--no-xlib", /* tell VLC to not use Xlib */
        };

        libvlc = libvlc_new(sizeof(argv) / sizeof(*argv), argv);

        OX_ASSERT(libvlc);
    }

    void MovieSprite::free()
    {
        OX_ASSERT(libvlc);

        libvlc_release(libvlc);
        libvlc = 0;
    }


    class MovieSpriteVLC : public MovieSprite
    {
    public:
        MovieSpriteVLC() : _player(0), _media(0) {}
        ~MovieSpriteVLC()
        {
            _clear();
        }
        /*
        Point getMovieSize() const
        {
            PLAYER_NOT_NULL(Point(1, 1));

            unsigned int w = 0, h = 0;
            int r = libvlc_video_get_size(_player, 0, &w, &h);

            return Point(w, h);
        }
        */

        Point _getMovieSize() const OVERRIDE
        {
            PLAYER_NOT_NULL(Point(1, 1));

            Point size = _bufferSize;

            if (!_bufferSize.x)
            {
                unsigned int w = 0, h = 0;
                int r = libvlc_video_get_size(_player, 0, &w, &h);
                size = Point(w, h);
            }

            return size;
        }


        void _setVolume(float v) OVERRIDE
        {
            PLAYER_NOT_NULL(void());
            libvlc_audio_set_volume(_player, v);
        }


        void _play() OVERRIDE
        {
            PLAYER_NOT_NULL(void());

            _init();

            libvlc_media_player_play(_player);
        }

        void _initPlayer() OVERRIDE
        {
            libvlc_video_set_callbacks(_player, lock, unlock, display, this);
            const char* f = "RV16";
            switch (_format)
            {
                case oxygine::TF_R8G8B8A8:
                    f = "RV32";
                    break;
                case oxygine::TF_R5G6B5:
                    f = "RV16";
                    break;
                default:
                    OX_ASSERT(!"unsupported format");
            }

            libvlc_video_set_format(_player, f, _mt.getWidth(), _mt.getHeight(), _mt.lock().pitch);
            libvlc_audio_set_volume(_player, _volume);
        }

        void _pause() OVERRIDE
        {
            PLAYER_NOT_NULL(void());
            libvlc_media_player_pause(_player);
        }

        void _stop() OVERRIDE
        {
            PLAYER_NOT_NULL(void());
            libvlc_media_player_stop(_player);
        }

        bool _isPlaying() const OVERRIDE
        {
            PLAYER_NOT_NULL(false);
            return libvlc_media_player_is_playing(_player) == 1;
        }

        void _clear() OVERRIDE
        {
            if (_player)
                libvlc_media_player_release(_player);
            _player = 0;

            if (_media)
                libvlc_media_release(_media);
            _media = 0;
        }

        void _setMovie(const std::string& movie) OVERRIDE
        {
            _media = libvlc_media_new_path(libvlc, movie.c_str());
            libvlc_media_parse(_media);

            _player = libvlc_media_player_new_from_media(_media);
        }


        void _update(const UpdateState& us) OVERRIDE
        {
            if (!_media)
                return;

            if (!_completeDispatched)
            {
                libvlc_state_t state = libvlc_media_get_state(_media);
                if (state == libvlc_Ended)
                {
                    _completeDispatched = true;

                    Event ev(COMPLETE);
                    dispatchEvent(&ev);
                }
            }
        }

    private:

        libvlc_media_player_t* _player;
        libvlc_media_t* _media;
    };


    spMovieSprite MovieSprite::create()
    {
        return new MovieSpriteVLC;
    }
}