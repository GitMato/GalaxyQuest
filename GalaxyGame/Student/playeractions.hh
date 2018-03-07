/* --GALAXY QUEST 2017--------------------------------------
 * "Have you tried turning it off and on again"
 *     Hanna Enqvist (276930) hanna.enqvist@student.tut.fi
 *     Tomi Mannila  (211950) tomi.mannila@student.tut.fi
 * ---------------------------------------------------------*/

#ifndef PLAYERACTIONS_HH
#define PLAYERACTIONS_HH

#include "statistics.hh"
#include "ship.hh"

/**
 * @file
 * @brief PlayerActions defines all possible events
 * a player can cause in the game.
 */
namespace Student
{
/**
 * @brief PlayerActions class defines all possible events
 * a player can cause in the game.
 */
class PlayerActions
{
public:
    /**
     * @brief Constructor.
     * @param statistics Pointer to Statistics object.
     */
    PlayerActions(Student::Statistics *statistics);

    /**
     * @brief Save the ship and call statistics to add points, credits,
     * shipSaved.
     * @param ship Shared pointer to the ship which will be saved.
     * @post The ships engine is repaired.
     */
    void shipSaved(std::shared_ptr<Common::Ship> ship);

    /**
     * @brief Condition of winning the game.
     * @return true if the win condition is met, false if it is not.
     * @post Exception guarantee: nothrow
     */
    bool winCondition();
    /**
     * @brief Condition of losing the game.
     * @return true if the loss condition is met, false if it is not.
     * @post Exception guarantee: nothrow
     */
    bool lossCondition();

private:
    /**
     * @brief Pointer to Statistics object.
     */
    Student::Statistics *statistics_;
};
}
#endif // PLAYERACTIONS_HH
