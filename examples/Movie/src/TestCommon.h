#pragma once
#include "test.h"

const char* movies[]        = { "movies/movie.ogv", "movies/t2p.ogv",  "movies/journal.ogv", "movies/poweder.ogv", "movies/Wheel_.ogv", "movies/mine_wagon_.ogv", "movies/bridge_wheel_.ogv", "movies/Wrench_right.ogv", "movies/Bridge.ogv", "movies/Scredriver.ogv", "movies/key_in.ogv" };
const bool  moviesAlpha[]   = { false,               true,                  true ,                    true ,             true ,               true ,                          true ,          true ,                        true ,             true ,                      true };
const int NumMovies = 11;

extern Resources gameResources;


class Control : public Sprite
{
public:
    Control(int col)
    {
        setResAnim(gameResources.getResAnim("controls"), col);
        setBlendMode(blend_add);
        setAnchor(0.5f, 0.5f);
        addEventListener(TouchEvent::CLICK, [&](Event*)
        {
            setColor(Color::White);
            addTween(Sprite::TweenColor(Color::Black), 300, 1, true);
        });
    }
};


class MoviePlayer : public Actor
{
public:
    spTextField _text;
    spSprite    _button;

    spMovieSprite _movie;

    int         _current;
    Test* test;

    MoviePlayer(Test* t) : _current(0), test(t)
    {
        _current = 0;
        _movie = MovieSprite::create();
        _movie->setInputEnabled(false);

        setSize(getStage()->getSize());

        playNext();

        addChild(_movie);
        //_movie->setPriority(1);

        _movie->addEventListener(MovieSprite::COMPLETE, [&](Event*)
        {
            test->notify("done");
            //play next video when it's done
            //playNext();
        });



        //create buttons
        spSprite  play = new Control(1);

        Vector2 pos = Vector2(getWidth() / 2 - 200, getHeight() - play->getHeight());

        play->setPosition(pos);
        play->attachTo(this);
        play->addEventListener(TouchEvent::CLICK, [&](Event*)
        {
            _movie->play();
        });

        pos.x += play->getWidth();
        spSprite  pause = new Control(2);
        pause->setPosition(pos);
        pause->attachTo(this);
        pause->addEventListener(TouchEvent::CLICK, [&](Event*)
        {
            _movie->pause();
        });

        pos.x += play->getWidth();
        spSprite stop = new Control(3);
        stop->setPosition(pos);
        stop->attachTo(this);
        stop->addEventListener(TouchEvent::CLICK, [&](Event*)
        {
            _movie->stop();
        });

        pos.x += play->getWidth();
        spSprite next = new Control(4);
        next->setPosition(pos);
        next->attachTo(this);
        next->addEventListener(TouchEvent::CLICK, [&](Event*)
        {
            playNext();
        });
    }

    void playNext()
    {
        int n = _current % NumMovies;
        _movie->setMovie(movies[n], moviesAlpha[n]);
        //_movie->setMovie(movies[n], false);
        //_movie->setLooped(true);
        _movie->play();
        Vector2 pos = getSize() / 2 - _movie->getSize() / 2;
        _movie->setPosition(int(pos.x), int(pos.y));

        _current++;
    }
};



class TestCommon: public Test
{
public:
    spMovieSprite _movie;
    TestCommon()
    {
        content->addChild(new MoviePlayer(this));
    }
};