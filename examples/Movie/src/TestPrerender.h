
#pragma once
#include "test.h"

class TestPrerender: public Test
{
public:

    spSprite sp;

    TestPrerender()
    {
        ResAnim* rs = createResAnimFromMovie("movies/t2p.ogv", Point(1024, 1024));

        sp = new Sprite();
        sp->addTween(TweenAnim(rs), 2000, -1);
        sp->setPosition(175.0f, 176.0f);
        sp->attachTo(content);

        addButton("swap", "show/hide movie");
    }

    void clicked(string id)
    {
        if (id == "swap")
        {
            ////movie->setVisible(!movie->getVisible());
            //sp->setVisible(!movie->getVisible());
        }
    }
};
