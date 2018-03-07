/* --GALAXY QUEST 2017--------------------------------------
 * "Have you tried turning it off and on again"
 *     Hanna Enqvist (276930) hanna.enqvist@student.tut.fi
 *     Tomi Mannila  (211950) tomi.mannila@student.tut.fi
 * ---------------------------------------------------------*/

#include <QString>
#include <QtTest>
#include <memory>
#include "statistics.hh"

/**
  * @file
  * @brief Contains tests for statistics class.
  */

/**
 * @brief The StatisticsTest class contains tests for statistics class
 */
class StatisticsTest : public QObject
{
    Q_OBJECT

public:
    /**
     * @brief The default constructor
     */
    StatisticsTest();

private Q_SLOTS:
    /**
     * @brief Reset statistics before each test.
     */
    void init();
    /**
     * @brief Test constructor to have all private value as 0.
     */
    void testConstructor();
    /**
     * @brief Test addPoints() and reducePoints() functions
     * by calling them several times and checking the status
     * of statistics with getPoints() function.
     * This test should not throw an exception.
     */
    void testPoints();
    /**
     * @brief Test addCredits() and reduceCredits() functions by calling
     * them several times and checking the status of statistics
     * with getCredits() function.
     * This test should not throw an exception.
     */
    void testCredits();
    /**
     * @brief Test addSavedShip function by calling it several times
     * and checking the status of statistics with getSavedShips() function.
     */
    void testAddSavedShips();
    /**
     * @brief Test addLostShip function by calling it several times
     * and checking the status of statistics with getLostShips() function.
     */
    void testAddLostShips();
    /**
     * @brief Test especially reducePoints() function by reducing
     * the amount of points below 0. This should throw an exception
     * and the last valid point amount should be preserved.
     */
    void testReducePoints();
    /**
     * @brief Test especially reduceCredits() function by reducing
     * the amount of credits below MAX_LOAN_ALLOWANCE. This should
     * throw an exception and the last valid credit amount should be
     * preserved.
     */
    void testReduceCredits();

private:
    /**
     * @brief statistics_ shared pointer to Statistics object.
     */
    std::shared_ptr<Student::Statistics> statistics_;

};

StatisticsTest::StatisticsTest()
{
}


void StatisticsTest::init()
{
    statistics_.reset();
    statistics_ = std::make_shared<Student::Statistics>();
}

void StatisticsTest::testConstructor()
{
    QVERIFY2(statistics_->getPoints() == 0,
             "Points should be 0 at the start of the game.");
    QVERIFY2(statistics_->getCreditBalance() == 0,
             "Credit should be 0 at the start of the game.");
    QVERIFY2(statistics_->getSavedShips() == 0,
             "SavedShips should be 0 at the start of the game.");
    QVERIFY2(statistics_->getLostShips() == 0,
             "LostShips should be 0 at the start of the game.");
}

void StatisticsTest::testPoints()
{
    statistics_->addPoints(17);
    statistics_->addPoints(5);
    statistics_->addPoints(22);

    QVERIFY2(statistics_->getPoints() == 44,
             "Wrong number of points. Should have been 44.");

    statistics_->reducePoints(14);
    statistics_->reducePoints(20);

    QVERIFY2(statistics_->getPoints() == 10,
             "Wrong number of points after reducing. Should Have been 10.");
}

void StatisticsTest::testCredits()
{
    statistics_->addCredits(100);
    statistics_->addCredits(235);
    statistics_->addCredits(55);

    QVERIFY2(statistics_->getCreditBalance() == 390,
             "Not the right amount of credits. Should have beeen 390");

    statistics_->reduceCredits(150);
    statistics_->reduceCredits(40);

    QVERIFY2(statistics_->getCreditBalance() == 200,
             "Not the right amount of credits after reducing. "
             "Should have been 200");
}

void StatisticsTest::testAddSavedShips()
{
    statistics_->addSavedShip();
    statistics_->addSavedShip();
    statistics_->addSavedShip();
    statistics_->addSavedShip();

    QVERIFY2(statistics_->getSavedShips() == 4,
             "Not the right amount of saved ships. Should have been 4");

}

void StatisticsTest::testAddLostShips()
{
    statistics_->addLostShip();
    statistics_->addLostShip();
    statistics_->addLostShip();
    statistics_->addLostShip();
    statistics_->addLostShip();

    QVERIFY2(statistics_->getLostShips() == 5,
             "Not the right amount of saved ships. Should have been 5");

}

void StatisticsTest::testReducePoints()
{
    statistics_->addPoints(100);
    statistics_->addPoints(50);
    statistics_->reducePoints(150);

    QVERIFY2(statistics_->getPoints() == 0,
             "Function 'getPoints' should return 0.");

    QVERIFY_EXCEPTION_THROWN(statistics_->reducePoints(100);,
            Common::StateException);

    QVERIFY2(statistics_->getPoints() == 0,
             "Function 'getPoints' should return 0");
}

void StatisticsTest::testReduceCredits()
{
    statistics_->addCredits(100);
    QVERIFY2(statistics_->getCreditBalance() == 100,
             "Not the right amount of credits. Should have been 100");

    statistics_->reduceCredits(100);
    QVERIFY2(statistics_->getCreditBalance() == 0,
             "Not the right amount of credits after reducing. "
             "Should have been 0");

    statistics_->reduceCredits(1000);
    QVERIFY2(statistics_->getCreditBalance() == -1000,
             "Not the right amount of credits after reducing. "
             "Should have been -1000");

    statistics_->reduceCredits(9000);
    QVERIFY2(statistics_->getCreditBalance() == -10000,
             "Not the right amount of credits after reducing. "
             "Should have been -10000");

    QVERIFY_EXCEPTION_THROWN(statistics_->reduceCredits(1);,
            Common::StateException);

    QVERIFY2(statistics_->getCreditBalance() == -10000,
             "Not the right amount of credits after reducing. "
             "Should have been -10000");

}

QTEST_APPLESS_MAIN(StatisticsTest)

#include "statisticstest.moc"

