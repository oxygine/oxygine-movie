#include "oxygine-framework.h"
#include <functional>
#include "MovieSprite.h"
#include "test.h"
#include "TestCommon.h"
#include "TestStress.h"
#include "TestConverse.h"
#include "TestPrerender.h"
using namespace oxygine;

//it is our resources
//in real project you would have more than one Resources declarations.
//It is important on mobile devices with limited memory and you would load/unload them
Resources gameResources;

class TestMovie : public Test
{
public:
    TestMovie()
    {
        addButton("common", "Common");
        addButton("stress", "Stress");
        addButton("check_converse", "Color conversion");
        addButton("prerender", "prerender");

        //clicked("prerender");
    }
    void clicked(string id)
    {
        if (id == "common")
        {
            setVisible(false);
            getStage()->addChild(new TestCommon);
        }

        if (id == "stress")
        {
            setVisible(false);
            getStage()->addChild(new TestStress);
        }

        if (id == "check_converse")
        {
            setVisible(false);
            getStage()->addChild(new TestConverse);
        }

        if (id == "prerender")
        {
            setVisible(false);
            getStage()->addChild(new TestPrerender);
        }
    }
};

void example_preinit() {}

//called from entry_point.cpp
void example_init()
{
    //load xml file with resources definition
    gameResources.loadXML("res.xml");
    spSprite bg = new Sprite;
    bg->attachTo(getStage());
    bg->setResAnim(gameResources.getResAnim("bg"));
    bg->setBlendMode(blend_disabled);
    bg->setScale(getStage()->getSize().div(bg->getSize()));

    Test::init();

    bool highQualityShader = false;
#ifdef WIN32
    //use it only if you need correct color conversion from YUV to RGB
    highQualityShader = true;
#endif
    MovieSprite::init(highQualityShader);

    Test::instance = new TestMovie;
    getStage()->addChild(Test::instance);

    /*
    //lets create our client code simple actor
    //spMainActor was defined above as smart intrusive pointer (read more: http://www.boost.org/doc/libs/1_57_0/libs/smart_ptr/intrusive_ptr.html)
    spMainActor actor = new MainActor;

    //and add it to Stage as child
    getStage()->addChild(actor);
    */
}


//called each frame from entry_point.cpp
void example_update()
{
}

//called each frame from entry_point.cpp
void example_destroy()
{
    //free previously loaded resources
    gameResources.free();
    MovieSprite::free();

    Test::free();
}
