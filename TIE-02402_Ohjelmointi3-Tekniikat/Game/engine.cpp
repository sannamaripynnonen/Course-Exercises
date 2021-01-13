#include <QImage>
#include <QDebug>
#include <iostream>
#include <fstream>
#include <../CourseLib/errors/initerror.hh>
#include <../CourseLib/errors/gameerror.hh>
#include <../CourseLib/actors/nysse.hh>
#include "startdialog.hh"
#include "resultdialog.hh"
#include "engine.hh"
#include "player.hh"


Engine::Engine(QObject *parent) :
    QObject(parent)
{

}

Engine::~Engine()
{

}

// Pelin kulku

void Engine::start(std::shared_ptr<GameWindow> window, std::shared_ptr<CourseSide::Logic> logic)
{
    mainWindow_ = window;
    logic_ = logic;
    player_ = std::make_shared<Player>(Player());

    StartDialog dialog;
    connect(&dialog, &StartDialog::gameTimeGiven, this, &Engine::setGameLenght);
    connect(&dialog, &StartDialog::nameGiven, this, &Engine::setPlayerName);
    dialog.exec();

    createCity();

    mainWindow_->show();
    connect(mainWindow_.get(), &GameWindow::gameStarted, this, &Engine::startGame);
    connect(mainWindow_.get(), &GameWindow::playerCollisionWithEnemy, this, &Engine::takeDamage);
    connect(mainWindow_.get(), &GameWindow::buyHp, this, &Engine::buyHp);
    connect(mainWindow_.get(), &GameWindow::buyMaxHp, this, &Engine::buyMaxHp);
    connect(mainWindow_.get(), &GameWindow::buyOrUseDrone, this, &Engine::buyOrUseDrone);
    connect(mainWindow_.get(), &GameWindow::buyOrUseCar, this, &Engine::buyOrUseCar);
    connect(mainWindow_.get(), &GameWindow::useBike, this, &Engine::useBike);
    connect(mainWindow_.get(), &GameWindow::playerMoved, this, &Engine::movePlayer);
    connect(mainWindow_.get(), &GameWindow::nysseDestroyed, this, &Engine::nysseDestroyed);
    connect(mainWindow_.get(), &GameWindow::enemyShot, this, &Engine::shootEnemy);

    mainWindow_->updateHp(player_->getHp());
    mainWindow_->updateMaxHp(player_->getMaxHp());
}

void Engine::createCity()
{
    auto city = std::make_shared<City>(City(mainWindow_));
    QImage smallBackground = QImage( ":/offlinedata/offlinedata/kartta_pieni_500x500.png");
    QImage bigBackground = QImage( ":/offlinedata/offlinedata/kartta_pieni_500x500.png");
    try
    {
        city->setBackground(smallBackground, bigBackground);
    }
    catch (Interface::InitError const& error)
    {
        std::cerr << error.what() << std::endl;
        std::cerr << error.giveMessage().toStdString() << std::endl;
    }
    city_ = city;
}

void Engine::startGame()
{
    statistics_ = std::make_shared<Statistics>(Statistics());

    logic_->takeCity(city_);
    logic_->fileConfig();
    unsigned short hours = QTime::currentTime().hour();
    unsigned short minutes = QTime::currentTime().minute();
    logic_->setTime(hours, minutes);

    timer_ = new QTimer(this);
    connect(timer_, &QTimer::timeout, this, &Engine::endGame);
    int tick = minutes_ * 60 * 1000 + seconds_ * 1000;

    enemyTimer_ = new QTimer(this);
    connect(enemyTimer_, &QTimer::timeout, this, &Engine::spawnEnemy);
    int enemyTick = 3000;
    enemyTimer_->start(enemyTick);

    timeDisplayTimer_ = new QTimer(this);
    connect(timeDisplayTimer_, &QTimer::timeout, this, &Engine::updateTime);
    int displayTick = 1000;

    try {
        logic_->finalizeGameStart();

        timer_->start(tick);
        enemyTimer_->start(enemyTick);
        timeDisplayTimer_->start(displayTick);
    }
    catch(...)
    {
        //Jos logic-luokka epäonnistuu jossakin, ei engine oikein voi tehdä mitään tilanteen pelastamiseksi.
        //throw Interface::InitError("Game initialization failed");
        //Tätä ei kuitenkaan ilmeisesti saada kiinnin mainissa, koska kyseessä on slotti, jota kutsutaan signaalin
        //seurauksena. Kurssin puitteissa jäi vähän epäselväksi, miten poikkeuskäsittely slotti/signaali-systeemissä
        //toimii.
        std::cerr << "Fatal error in game initializing" << std::endl;

        city_->endGame();
        mainWindow_->stopTimer();
        timer_->stop();
        enemyTimer_->stop();
        timeDisplayTimer_->stop();
    }
}

void Engine::setGameLenght(int seconds, int minutes)
{
    seconds_ = seconds;
    minutes_ = minutes;
    timeLeft_ = minutes_ * 60 + seconds_;
    updateTime();
}

void Engine::endGame()
{
    timer_->stop();
    enemyTimer_->stop();
    timeDisplayTimer_->stop();
    city_->endGame();
    mainWindow_->stopTimer();
    handleResults();
}

void Engine::setPlayerName(QString name)
{
    player_->setName(name);
}

void Engine::handleResults()
{
    int time = minutes_ * 60 + seconds_;
    std::string fileName = "results.txt";
    std::string name = player_->getName().toStdString();
    int pointsInt = statistics_->givePoints();

    double pointsScaled;
    if (time > 0)
    {
        pointsScaled = (double(pointsInt) / double(time)) * 10;
    }
    else
    {
        pointsScaled = 0;
    }
    std::string points = std::to_string(pointsScaled);
    std::string result = name + ">" + points;
    std::list<std::string> results;

    std::ifstream readFile(fileName);
    if (!readFile)
    {
        std::cerr << "File does not exist or open." << std::endl;
        results.push_back(result);
    }
    else
    {
        std::string line;
        while(getline(readFile, line))
        {
            results.push_back(line);
        }
        readFile.close();

        bool resultAdded = false;
        std::list<std::string>::iterator it = results.begin();
        for (std::string data : results)
        {
            int pos = data.find(">");
            std::string pointsFromFile = data.substr(pos+1);

            if (pointsScaled >= std::stod(pointsFromFile))
            {
                results.insert(it, result);
                resultAdded = true;
                break;
            }
            else
            {
                it++;
            }
        }
        if (!resultAdded)
        {
            results.insert(it, result);
        }
        unsigned topSize = 10;
        if (results.size() > topSize)
        {
            results.pop_back();
        }
    }

    std::ofstream writeFile(fileName, std::ios::trunc);
    if (!writeFile)
    {
        std::cerr << "Error..." << std::endl;
    }
    else
    {
        for (std::string data : results)
        {
            writeFile << data << std::endl;
        }
        writeFile.close();
    }

    ResultDialog resultDialog(nullptr, results);
    resultDialog.exec();
}

void Engine::spawnEnemy()
{
    int maxCoordX = mainWindow_->getWidth();
    int maxCoordY = mainWindow_->getHeight();
    int minCoordX = 0;
    int minCoordY = 30;
    int x = rand() % maxCoordX + minCoordX;
    int y = rand() % maxCoordY + minCoordY;
    auto enemy = std::make_shared<Enemy>(Enemy());
    std::shared_ptr<Interface::IActor> e = std::dynamic_pointer_cast<Interface::IActor> (enemy);
    mainWindow_->addEnemyItem(x, y, enemy);
}

void Engine::updateTime()
{
    mainWindow_->updateTime(timeLeft_);
    timeLeft_--;
}


// Pelaajan toimet

void Engine::nysseDestroyed(std::shared_ptr<Interface::IActor> nysse)
{
    // Törmäyksissä kohteiden tyyppi ilmeisesti tunnistetaan välillä väärin, joten tarkistetaan että dynamic cast onnistuu.
    CourseSide::Nysse* bus = dynamic_cast<CourseSide::Nysse*>(nysse.get());
    if (bus == nullptr)
    {
        std::cerr << "Destroyed object was not a nysse." << std::endl;
    }
    else
    {
        std::vector<std::shared_ptr<Interface::IPassenger>> passengers = bus->getPassengers();
        int count = passengers.size();
        statistics_->passengerDied(count);
        statistics_->nysseDestroyed();

        for (int i = 0; i < count; i++)
        {
            try
            {
                city_->removeActor(passengers.at(i));
            }
            catch (Interface::GameError const& error)
            {
                std::cerr << error.what() << std::endl;
                std::cerr << error.giveMessage().toStdString() << std::endl;
            }

        }
        try
        {
            city_->removeActor(nysse);
        }
        catch (Interface::GameError const& error)
        {
            std::cerr << error.what() << std::endl;
            std::cerr << error.giveMessage().toStdString() << std::endl;
        }

        int points = statistics_->givePoints();
        int destroyedNysses = statistics_->getDestroyedNysses();
        mainWindow_->updateScore(points);
        mainWindow_->updateDestroyedNysses(destroyedNysses);
    }

}

void Engine::shootEnemy(std::shared_ptr<Interface::IActor> enemy)
{
    // Törmäyksissä kohteiden tyyppi ilmeisesti tunnistetaan välillä väärin, joten tarkistetaan että dynamic cast onnistuu.
    Enemy* shotEnemy = dynamic_cast<Enemy*>(enemy.get());
    if (shotEnemy == nullptr)
    {
        std::cerr << "Destroyed object was not an enemy." << std::endl;
    }
    else
    {
        int damage = player_->getDamage();
        shotEnemy->takeDamage(damage);
        bool isDestroyed = enemy->isRemoved();
        if (isDestroyed)
        {
            const int VALUE = 25;
            player_->addMoney(VALUE);
            int money = player_->getMoney();
            mainWindow_->updateMoney(money);
            mainWindow_->deleteEnemy(enemy);
            statistics_->enemyDestroyed();
            int enemys = statistics_->getDestroyedEnemys();
            mainWindow_->updateDestroyedEnemys(enemys);
        }
    }
}

void Engine::takeDamage()
{
    int damage;
    if (player_->isUsingCar())
    {
        damage = 10;
    }
    else
    {
      damage = 50;
    }
    player_->takeDamage(damage);
    int hp = player_->getHp();
    mainWindow_->updateHp(hp);

    int value = 25;
    player_->addMoney(value);
    int money = player_->getMoney();
    mainWindow_->updateMoney(money);

    bool isDestroyed = player_->isRemoved();
    if (isDestroyed)
    {
        endGame();
    }
}

void Engine::movePlayer(int direction)
{
    int speed = player_->getMovementSpeed();
    mainWindow_->movePlayer(speed, direction);
}


// Kauppa

void Engine::buyMaxHp()
{
    const int HP = 25;
    const int cost = 50;
    player_->buyMaxHp(HP, cost);
    int hp = player_->getMaxHp();
    mainWindow_->updateMaxHp(hp);

    int money = player_->getMoney();
    mainWindow_->updateMoney(money);
}

void Engine::buyHp()
{
    const int HP = 25;
    const int cost = 20;
    player_->buyHp(HP, cost);
    int hp = player_->getHp();
    mainWindow_->updateHp(hp);

    int money = player_->getMoney();
    mainWindow_->updateMoney(money);
}

void Engine::buyOrUseDrone()
{
    if (!player_->hasDrone())
    {
        player_->buyDrone();
        int money = player_->getMoney();
        mainWindow_->updateMoney(money);
    }
    player_->setDrone();
    QString text = "USING DRONE";
    mainWindow_->updateVehicle(text);
}

void Engine::buyOrUseCar()
{
    if (!player_->hasCar())
    {
        player_->buyCar();
        int money = player_->getMoney();
        mainWindow_->updateMoney(money);
    }
    player_->setCar();
    QString text = "USING CAR";
    mainWindow_->updateVehicle(text);
}

void Engine::useBike()
{
    player_->setBike();
    QString text = "USING BIKE";
    mainWindow_->updateVehicle(text);
}
