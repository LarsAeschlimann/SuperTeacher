#include"Level.h"

using namespace std;

bool level_execute(level_str* level_info, sf::RenderWindow* window)
{
    auto resource = make_shared<ResourceManager>();
    auto config = resource->get_json("conf.json");
    auto style = sf::Style::Default;
    bool win = false;

    Ground ground(resource, level_info->name);
    Object people = {};
    Object front_print = {};
    Interactives interact(resource, level_info->name);
    int levelJump = 0;

    auto level = resource->get_json("levels/"+ level_info->name+".json");
    View view = (sf::FloatRect((float)0,
        (float)(SCREEN_Y_PXSIZE - ((int)(*level)["background"]["world"]["y"]) * BLOCK_PXSIZE),
        (float)(((int)(*level)["background"]["world"]["x"]) * BLOCK_PXSIZE),
        (float)(((int)(*level)["background"]["world"]["y"]) * BLOCK_PXSIZE)));
    Background background(resource, level_info->name, sf::IntRect(0,
        0,
        ((int)(*level)["background"]["world"]["x"]) * BLOCK_PXSIZE,
        ((int)(*level)["background"]["world"]["y"]) * BLOCK_PXSIZE));
    auto font = resource->get_font(MATHLETE);
    auto song = resource->get_music(SONG_1);
    int ground_level = (*level)["ground"]["level"];

    song->setLoop(true);
    Text text((string)"SuperTeacher", sf::Vector2f(-60, -25) + view.GetView().getCenter(), font);

    std::shared_ptr<sf::Text> timetext = make_shared<sf::Text>("Clock: " + to_string(Timer::get_time_ms()), *font, 100);

    text.Add_Text(timetext, sf::Vector2f(-1500, -25) + view.GetView().getCenter());


    std::array<std::array<int, 18>, 32> ColisionDetect = {};
    const int SOLID = 1;

    window->setFramerateLimit(50);
    HIManager user_input = { window };

<<<<<<< HEAD

    user_input.HIEvent_sig.connect([level_info](HIEvent event)->void {
=======
    user_input.HIEvent_sig.connect([level_info,&view](HIEvent event)->void {
>>>>>>> BFH-E1D-2015-2016/master
        switch (event) {
        case HIEvent::CLOSE:
            level_info->end = true;
            break;
<<<<<<< HEAD
=======
        case HIEvent::DOWN_DOWN:
            if (view.GetView().getSize().x == SCREEN_X_PXSIZE)
            {
                view.SetSize(sf::Vector2f(1.2*SCREEN_X_PXSIZE, 1.2*SCREEN_Y_PXSIZE));
            }
            else
            {
                view.SetSize(sf::Vector2f(1*SCREEN_X_PXSIZE, 1*SCREEN_Y_PXSIZE));
            }
            break;
>>>>>>> BFH-E1D-2015-2016/master
        default:
            break;
        }
    });



    std::shared_ptr<sf::Text> score = make_shared<sf::Text>("Points: ", *font, 50);

    text.Add_Text(score, sf::Vector2f(-900, -25) + view.GetView().getCenter());

    std::shared_ptr<sf::Text> live = make_shared<sf::Text>("Lives: ", *font, 50);

    text.Add_Text(live, sf::Vector2f(-60, -75) + view.GetView().getCenter());

    for (int y = 17; y >= ground_level; y--) {
        for (int x = 0; x < 32; x++) {
            ColisionDetect[x][y] = SOLID;
        }
    }

    std::string gr_name = (*level)["ground"]["name"];


    auto character = Character(resource, "level", ground_level);

    character.addPencil((*level)["init"]["pencil"]);

    std::shared_ptr<sf::Text> pencil = make_shared<sf::Text>("Pencils: " + to_string(character.getNbPencil()), *font, 50);
    text.Add_Text(pencil, sf::Vector2f(-900, -75) + view.GetView().getCenter());

    user_input.HIEvent_sig.connect([&character](HIEvent event)->void {
        character.process_event(event);
    });


    if ((bool)(*config)["audio"]) {
        song->play();
    }
    colision col = { true,true,ground_level*BLOCK_PXSIZE,0 };
    while (!level_info->end)
    {
        *level_info = interact.update(character, score, ground_level*BLOCK_PXSIZE, &col,&level_info->score);
        if (level_info->end && level_info->live > 0)
        {
            win = true;
        }
        user_input.process();
        
        character.write_collision(col);
        character.update();

        window->clear(sf::Color::Blue);
        view.process(character.get_rectangle());
        window->setView(view.GetView());

        auto tmp_time = Timer::get_time_s();
        timetext->setString("Time: " + to_string(tmp_time) + " sec");
        pencil->setString("Pencils: " + to_string(character.getNbPencil()));
        live->setString("Lives: " + to_string(character.getLive()));

<<<<<<< HEAD
        text.update(view.GetView().getCenter());
=======
        text.update(view.GetView());
>>>>>>> BFH-E1D-2015-2016/master

        // Dessin

        for (auto n : background.get_drawables())
        {
            window->draw(*n);
        }
        for (auto n : ground.get_drawables())
        {
            window->draw(*n);
        }
        for (auto n : interact.get_drawables())
        {
            window->draw(*n);
        }
        for (auto n : character.get_drawables())
        {
            window->draw(*n);
        }
        for (auto n : front_print.get_drawables())
        {
            window->draw(*n);
        }
        for (auto n : text.get_texts())
        {
            window->draw(*n);
        }
        window->display();
        window->clear();
    }
    user_input.HIEvent_sig.disconnect_all_slots();
    return win;
}