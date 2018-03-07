/* --GALAXY QUEST 2017--------------------------------------
 * "Have you tried turning it off and on again"
 *     Hanna Enqvist (276930) hanna.enqvist@student.tut.fi
 *     Tomi Mannila  (211950) tomi.mannila@student.tut.fi
 * ---------------------------------------------------------*/

#include "playeractions.hh"

Student::PlayerActions::PlayerActions(Student::Statistics *statistics)
{
    statistics_ = statistics;

}

void Student::PlayerActions::shipSaved(std::shared_ptr<Common::Ship> ship)
{

    // Get ship's engine
    std::shared_ptr<Common::ShipEngine> engine = ship->getEngine();

    // Calculate missing health
    int maxhealth = engine->getMaxHealth();
    int currenthealth = engine->getHealth();
    int repairedhealth = maxhealth - currenthealth;

    // Ship will turn distress signal off when repaired
    engine->repair(repairedhealth);

    statistics_->addSavedShip();
    statistics_->addPoints(repairedhealth);
    statistics_->addCredits(50);
    Q_ASSERT(engine->getHealth() == engine->getMaxHealth());
}

bool Student::PlayerActions::winCondition()
{
    if (statistics_->getSavedShips() >= 10){
        return true;
    } else {
        return false;
    }
}

bool Student::PlayerActions::lossCondition()
{
    if (statistics_->getLostShips() >= 10){
        return true;
    } else {
        return false;
    }
}
