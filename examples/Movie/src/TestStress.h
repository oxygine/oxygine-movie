#pragma once
#include "test.h"

//declare spMainActor as intrusive_ptr holder of MainActor
typedef oxygine::intrusive_ptr<MoviePlayer> spMainActor;

class TestStress: public Test
{
public:

    Atlas2 _atlas;

    vector<const char*> moviesWithAlpha;

    TestStress()
    {
        srand(time(0));
        _atlas.init(getWidth(), getHeight());
        addButton("add", "add");
        addButton("clear", "clear");


        for (int i = 0; i < NumMovies; ++i)
        {
            if (moviesAlpha[i] && !strstr(movies[i], "t2p"))
                moviesWithAlpha.push_back(movies[i]);
        }

        num = 0;
        clicked("add");
    }

    int num;

    void clicked(string id)
    {
        if (id == "clear")
        {
            num = 0;
            _atlas.clean();
            _atlas.init(getWidth(), getHeight());
            _content->removeChildren();
        }
        if (id == "add")
        {
            spMovieSprite movie = MovieSprite::create();
            movie->setMovie(moviesWithAlpha[num % moviesWithAlpha.size()], true);
            movie->setLooped(true);
            movie->play();


            float scale = 0.5f;// 1.0f - std::min(0.5f, num / 10.0f);
            while (true)
            {
                Vector2 sz = movie->getSize()  * scale;
                ImageData dt;
                dt.w = sz.x;
                dt.h = sz.y;
                Rect src;
                Point offset(0, 0);
                if (_atlas.add(0, dt, src, offset))
                {
                    movie->setPosition(src.getLeftTop());
                    movie->setScale(scale);
                    _content->addChild(movie);
                    ++num;
                    break;
                }
                scale *= 0.8f;
            }
        }
    }
};
