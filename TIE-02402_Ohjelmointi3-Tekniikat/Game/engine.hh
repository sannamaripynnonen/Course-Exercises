#ifndef ENGINE_HH
#define ENGINE_HH

#include <QObject>
#include <../CourseLib/graphics/simplemainwindow.hh>
#include <../CourseLib/core/logic.hh>
#include "city.hh"
#include "player.hh"
#include "statistics.hh"
#include "enemy.hh"

/**
 * @brief Handles the game starting, running and ending. Reacts to game events.
 */


class Engine : public QObject
{
    Q_OBJECT

public:
    /**
     * @brief Engine constructor.
     * @param parent Parent object.
     */
    Engine(QObject *parent = nullptr);

    /**
     * @brief ~Engine destructor.
     */
    virtual ~Engine();

    // Pelin kulku
    /**
     * @brief start "Starts" the engine and does initialization actions. Sets game window and logic, creates player and start dialog.
     * Calls createCity.
     * @param window Game window.
     * @param logic Logic handling course side events.
     * @pre -
     * @post Engine is initilizated and start dialog opens. After exiting start dialog, game window is shown.
     */
    void start(std::shared_ptr<GameWindow> window, std::shared_ptr<CourseSide::Logic> logic);

    /**
     * @brief createCity creates the city and sets the city for engine.
     * @pre mainWindow has been set for engine.
     * @post City is set for engine.
     */
    void createCity();

public slots:
    /**
     * @brief startGame starts the game.
     * @pre start has been called.
     * @post Game is running. If exception is thrown, starting the game is terminated.
     */
    void startGame();

    /**
     * @brief setGameLenght sets the game lenght as minutes and seconds for the engine. Calls updateGame.
     * @param seconds Given seconds.
     * @param minutes Given minutes.
     * @pre -
     * @post Minutes and seconds are set for engine.
     */
    void setGameLenght(int seconds, int minutes);

    /**
     * @brief endGame ends the game. Calls handleResults.
     * @pre start and startGame have been called.
     * @post Game is over.
     */
    void endGame();

    /**
     * @brief setPlayerName sets the player's name.
     * @param name Given name.
     * @pre start has been called.
     * @post Player's name is set.
     */
    void setPlayerName(QString name);

    /**
     * @brief handleResults reads results from a file, writes them to the file and gives them to the result window.
     * @pre start, startGame and endGame have been called.
     * @post Results are written in the file.
     */
    void handleResults();

    /**
     * @brief spawnEnemy creates enemy, calculates enemy's position and gives enemy to game window.
     * @pre start has been called.
     * @post Enemy is added to the game window.
     */
    void spawnEnemy();

    /**
     * @brief updateTime updates game time in the engine and gives new value to the game window..
     * @pre start and startGame have been called.
     * @post Game time is updated.
     */
    void updateTime();


    // Pelaajan toimet
    /**
     * @brief nysseDestroyed handles required actions when player destroys a nysse. Updates statistics,
     * removes nysse from the city and gives new values to the game window.
     * @param nysse Destroyed nysse.
     * @pre start and startGame have been called.
     * @post All actions are completed.
     */
    void nysseDestroyed(std::shared_ptr<Interface::IActor> nysse);

    /**
     * @brief shootEnemy handles required actions when player shoots an enemy. Adds money
     * to the player if enemy is destroyed and gives new values to the game window.
     * @param enemy Destroyed enemy.
     * @pre start and startGame have been called.
     * @post All actions are completed.
     */
    void shootEnemy(std::shared_ptr<Interface::IActor> enemy);

    /**
     * @brief takeDamage handles required actions when player takes damage. Gives new values to the game window.
     * If player is destroyed, calls endGame.
     * @pre start has been called.
     * @post Player's hp is updated. If player is destroyed, endGame is called.
     */
    void takeDamage();

    /**
     * @brief movePlayer gives player's speed to game window.
     * @param direction Direction in which the player is moving.
     * @pre start has been called.
     * @post Player's speed is given to the game window.
     */
    void movePlayer(int direction);

    // Kauppa

    /**
     * @brief buyMaxHp updates player's max HP and money and gives new values to the game window.
     * @pre start has been called.
     * @post Playr's max HP and money are updated.
     */
    void buyMaxHp();

    /**
     * @brief buyHp updates player's HP and money and gives new values to the game window.
     * @pre start has been called.
     * @post Player's HP and money are updated.
     */
    void buyHp();

    /**
     * @brief buyOrUseDrone adds drone for player if player has enough money or/and changes current vehicle to drone. Updates money.
     * Gives new values to the game window.
     * @pre start has been called.
     * @post If player has enough money or already had drone, player is using drone. Money is updated.
     */
    void buyOrUseDrone();

    /**
     * @brief buyOrUseCar adds car for player if player has enough money or/and changes current vehicle to car. Updates money.
     * Gives new values to the game window.
     * @pre start has been called.
     * @post If player has enough money or already had car, player is using car. Money is updated.
     */
    void buyOrUseCar();

    /**
     * @brief useBike changes player's current vehicle to bike.
     * @pre start has been called.
     * @post Player is using bike.
     */
    void useBike();

private:
    std::shared_ptr<GameWindow> mainWindow_;
    std::shared_ptr<Statistics> statistics_;
    std::shared_ptr<City> city_;
    std::shared_ptr<Player> player_;
    std::shared_ptr<CourseSide::Logic> logic_;
    int minutes_ = 0;
    int seconds_ = 0;
    QTimer *timer_;
    QTimer *enemyTimer_;
    QTimer *timeDisplayTimer_;
    int timeLeft_;
};

#endif // ENGINE_HH
