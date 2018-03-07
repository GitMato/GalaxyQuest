/* --GALAXY QUEST 2017--------------------------------------
 * "Have you tried turning it off and on again"
 *     Hanna Enqvist (276930) hanna.enqvist@student.tut.fi
 *     Tomi Mannila  (211950) tomi.mannila@student.tut.fi
 * ---------------------------------------------------------*/

#ifndef STATISTICS_HH
#define STATISTICS_HH

#include "istatistics.hh"
#include <QtDebug>
#include "stateexception.hh"

/**
 * @file
 * @brief Handles all the statistics of the game
 */

namespace Student {

/**
 * @brief The Statistics class handles and stores
 * all the statistics of the game.
 *
 * More detailed definitions are available in IStatistics.
 */
class Statistics : public Common::IStatistics
{
public:
    /**
     * @brief Constructor.
     */
    Statistics();

    /**
     * @brief Add 1 to savedShipCounter_.
     */
    void addSavedShip();
    /**
     * @brief Return the amount of saved ships.
     * @return the amount of saved ships.
     * @post Exception guarantee: nothrow
     */
    unsigned getSavedShips() const;

    /**
     * @brief Add 1 to lostShipCounter_.
     * @post Exception guarantee: nothrow
     */
    void addLostShip();
    /**
     * @brief Return the amount of lost ships.
     * @return the current amount of lost ships.
     * @post Exception guarantee: nothrow
     */
    unsigned getLostShips() const;

    /**
     * @brief Add points to statistics.
     * @param amount the amount of points to add.
     * @post Exception guarantee: nothrow
     */
    void addPoints(unsigned amount);
    /**
     * @brief Reduce points from statistics.
     * @param amount the amount of points to reduce.
     * @exception StateException, if current amount of points would be < 0
     * @post Exception guarantee: strong
     */
    void reducePoints(unsigned amount);
    /**
     * @brief Return the amount of points.
     * @return The current amount of points.
     * @post Exception guarantee: nothrow
     */
    unsigned getPoints() const;

    /**
     * @brief Add credits to statistics.
     * @param amount The amount of credits to add.
     * @post Exception guarantee: nothrow
     */
    void addCredits(unsigned amount);
    /**
     * @brief Reduce credits from statistics.
     * @param amount The amount of credits to reduce.
     * @exception StateException, if the current amount of
     * credits < MAX_LOAN_ALLOWANCE_.
     * @post Exception guarantee: strong
     */
    void reduceCredits(unsigned amount);
    /**
     * @brief Return the amount of credits.
     * @return The current amount of credits
     * @post Exception guarantee: nothrow
     */
    int getCreditBalance() const;

private:
     /**
      * @brief Max amount of loan the player can have.
      */
     int MAX_LOAN_ALLOWANCE_;
     /**
      * @brief The current amount of credits the player has.
      */
     int credits_;
     /**
      * @brief The current amount of ships the player has saved.
      */
     unsigned int savedShipCounter_;
     /**
      * @brief The current amount of ships which are lost (abandoned).
      */
     unsigned int lostShipCounter_;
     /**
      * @brief The current amount of points.
      */
     unsigned int points_;

     /**
      * @brief The class invariant which is defined in IGalaxy
      */
     void statisticsInvariant() const;

};
}//Student

#endif // STATISTICS_HH
