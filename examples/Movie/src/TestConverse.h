#pragma once
#include "test.h"

class TestConverse: public Test
{
public:

    spMovieSprite       movie;
    spSprite sp;

    TestConverse()
    {
        sp = new Sprite();
        sp->setResAnim(gameResources.getResAnim("from_game"));
        sp->setPosition(175.0f, 176.0f);
        sp->attachTo(content);

        movie = MovieSprite::create();
        movie->setMovie("movies/trap.ogv", true);
        movie->setLooped(true);
        movie->play();
        movie->pause();
        movie->setPosition(-10.0f, -10.0f);
        movie->attachTo(content);
        movie->setVisible(false);

        addButton("swap", "show/hide movie");
    }

    void clicked(string id)
    {
        if (id == "swap")
        {
            movie->setVisible(!movie->getVisible());
            sp->setVisible(!movie->getVisible());
        }
    }
};
