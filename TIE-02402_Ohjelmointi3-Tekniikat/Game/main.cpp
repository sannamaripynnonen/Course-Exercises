#define EXIT_FAILURE
#include <QApplication>
#include <../CourseLib/core/logic.hh>
#include <../CourseLib/errors/initerror.hh>
#include "../CourseLib/errors/gameerror.hh"

#include "gamewindow.hh"
#include "engine.hh"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Q_INIT_RESOURCE(offlinedata);

    std::shared_ptr<GameWindow> window;
    std::shared_ptr<CourseSide::Logic> logic;
    Engine engine;

    try
    {
        window = std::make_shared<GameWindow>(new GameWindow());
        logic = std::make_shared<CourseSide::Logic>(new CourseSide::Logic());
        engine.start(window, logic);
    }
    catch (Interface::InitError const& error)
    {
        std::cerr << "Fatal error in game initializing" << std::endl;
        std::cerr << error.what() << std::endl;
        std::cerr << error.giveMessage().toStdString() << std::endl;
        return EXIT_FAILURE;
    }
    catch (Interface::GameError const& error)
    {
        std::cerr << "Fatal error during the game" << std::endl;
        std::cerr << error.what() << std::endl;
        std::cerr << error.giveMessage().toStdString() << std::endl;
        return EXIT_FAILURE;
    }
    catch(std::bad_alloc const& error)
    {
        std::cerr << "Out of memeory" << std::endl;
        std::cerr << error.what() << std::endl;
        return EXIT_FAILURE;
    }
    catch (...)
    {
        std::cerr << "Unexpected error" << std::endl;
        return EXIT_FAILURE;
    }
    return a.exec();
}
