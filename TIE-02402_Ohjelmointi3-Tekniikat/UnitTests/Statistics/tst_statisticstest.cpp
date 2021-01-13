#include <QtTest>
#include "statistics.hh"

class Statisticstest : public QObject
{
    Q_OBJECT

public:
    Statisticstest();
    ~Statisticstest();

private slots:
    void setPassengers();
    void setNysses();
    void passengerDied();
    void passengerDied_data();
    void morePassengers();
    void nysseRemoved();
    void newNysse();
    void nysseLeft();
    void pointsStartFromZero();
    void givePoints();
    void givePoints_data();
    void enemyDestroyed();
    void nysseDestroyed();
};

Statisticstest::Statisticstest()
{

}

Statisticstest::~Statisticstest()
{

}

void Statisticstest::setPassengers()
{
    int passengers = 99;
    Statistics statistics = Statistics();
    statistics.setPassengers(passengers);
    QCOMPARE(statistics.getPassengers(), 99);

    int negativePassengers = -1;
    statistics.setPassengers(negativePassengers);
    QCOMPARE(statistics.getPassengers(), 0);
}

void Statisticstest::setNysses()
{
    int nysses = 62;
    Statistics statistics = Statistics();
    statistics.setNysses(nysses);
    QCOMPARE(statistics.getNysses(), 62);

    int negativeNysses = -145;
    statistics.setNysses(negativeNysses);
    QCOMPARE(statistics.getNysses(), 0);
}

void Statisticstest::passengerDied()
{
    QFETCH(int, passengersDied);
    QFETCH(int, passengers);
    QFETCH(int, passengersRemaining);

    Statistics statistics = Statistics();
    statistics.setPassengers(passengers);
    statistics.passengerDied(passengersDied);
    QCOMPARE(statistics.getPassengers(), passengersRemaining);
}

void Statisticstest::passengerDied_data()
{
    QTest::addColumn<int>("passengers");
    QTest::addColumn<int>("passengersDied");
    QTest::addColumn<int>("passengersRemaining");

    QTest::newRow("") << 5 << 2 << 3;
    QTest::newRow("") << 12 << 234 << 0;
    QTest::newRow("") << 0 << 4 << 0;
}

void Statisticstest::morePassengers()
{
    int passengers = 56;
    int num = 33;
    Statistics statistics = Statistics();
    statistics.setPassengers(passengers);
    statistics.morePassengers(num);
    QCOMPARE(statistics.getPassengers(), 89);
}

void Statisticstest::nysseRemoved()
{
    int nysses = 1111;
    Statistics statistics = Statistics();
    statistics.setNysses(nysses);
    statistics.nysseRemoved();
    QCOMPARE(statistics.getNysses(), 1110);

    int noNysses = 0;
    statistics.setNysses(noNysses);
    statistics.nysseRemoved();
    QCOMPARE(statistics.getNysses(), 0);
}

void Statisticstest::newNysse()
{
    int nysses = 276;
    Statistics statistics = Statistics();
    statistics.setNysses(nysses);
    statistics.newNysse();
    QCOMPARE(statistics.getNysses(), 277);
}

void Statisticstest::nysseLeft()
{
    int nysses = 128;
    Statistics statistics = Statistics();
    statistics.setNysses(nysses);
    statistics.nysseRemoved();
    QCOMPARE(statistics.getNysses(), 127);

    int noNysses = 0;
    statistics.setNysses(noNysses);
    statistics.nysseLeft();
    QCOMPARE(statistics.getNysses(), 0);
}

void Statisticstest::pointsStartFromZero()
{
    Statistics statistics = Statistics();
    QCOMPARE(statistics.givePoints(), 0);
}

void Statisticstest::givePoints()
{
    QFETCH(int, passengersDied);
    QFETCH(int, passengersDied2);
    QFETCH(int, passengers);
    QFETCH(int, nysses);
    QFETCH(int, passengersAdded);
    QFETCH(int, points);

    // Vain tapetut matkustajat vaikuttavat pisteisiin
    Statistics statistics = Statistics();
    statistics.setNysses(nysses);
    statistics.setPassengers(passengers);
    statistics.nysseLeft();
    statistics.passengerDied(passengersDied);
    statistics.newNysse();
    statistics.passengerDied(passengersDied2);
    statistics.nysseRemoved();
    statistics.morePassengers(passengersAdded);
    QCOMPARE(statistics.givePoints(), points);
}

void Statisticstest::givePoints_data()
{
    QTest::addColumn<int>("passengersDied");
    QTest::addColumn<int>("passengersDied2");
    QTest::addColumn<int>("passengers");
    QTest::addColumn<int>("nysses");
    QTest::addColumn<int>("passengersAdded");
    QTest::addColumn<int>("points");

    QTest::newRow("") << 5 << 10 << 20 << 30 << 2 << 15;
    QTest::newRow("") << 0 << 0 << 5 << 5 << 5 << 0;
    QTest::newRow("") << 10 << 10 << 5 << 5 << 7 << 20;
}

void Statisticstest::enemyDestroyed()
{
    Statistics statistics = Statistics();
    statistics.enemyDestroyed();
    QCOMPARE(statistics.getDestroyedEnemys(), 1);

    statistics.enemyDestroyed();
    statistics.enemyDestroyed();
    QCOMPARE(statistics.getDestroyedEnemys(), 3);

    statistics.morePassengers(321);
    statistics.nysseDestroyed();
    statistics.passengerDied(123);
    statistics.newNysse();
    statistics.nysseRemoved();
    statistics.nysseLeft();
    QCOMPARE(statistics.getDestroyedEnemys(), 3);
}

void Statisticstest::nysseDestroyed()
{
    Statistics statistics = Statistics();
    statistics.nysseDestroyed();
    QCOMPARE(statistics.getDestroyedNysses(), 1);

    statistics.nysseDestroyed();
    statistics.nysseDestroyed();
    QCOMPARE(statistics.getDestroyedNysses(), 3);

    statistics.morePassengers(321);
    statistics.enemyDestroyed();
    statistics.passengerDied(123);
    statistics.newNysse();
    statistics.nysseRemoved();
    statistics.nysseLeft();
    QCOMPARE(statistics.getDestroyedNysses(), 3);
}

QTEST_APPLESS_MAIN(Statisticstest)

#include "tst_statisticstest.moc"
