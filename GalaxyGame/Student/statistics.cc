/* --GALAXY QUEST 2017--------------------------------------
 * "Have you tried turning it off and on again"
 *     Hanna Enqvist (276930) hanna.enqvist@student.tut.fi
 *     Tomi Mannila  (211950) tomi.mannila@student.tut.fi
 * ---------------------------------------------------------*/

#include "statistics.hh"

Student::Statistics::Statistics()
{

    MAX_LOAN_ALLOWANCE_ = -10000;
    credits_ = 0;
    savedShipCounter_ = 0;
    lostShipCounter_ = 0;
    points_ = 0;

    statisticsInvariant();

}

void Student::Statistics::addSavedShip()
{

    statisticsInvariant();
    savedShipCounter_++;
    statisticsInvariant();

}

unsigned Student::Statistics::getSavedShips() const
{

    statisticsInvariant();
    return savedShipCounter_;

}

void Student::Statistics::addLostShip()
{

    statisticsInvariant();
    lostShipCounter_++;
    statisticsInvariant();

}

unsigned Student::Statistics::getLostShips() const
{

    statisticsInvariant();
    return lostShipCounter_;

}

void Student::Statistics::addPoints(unsigned amount)
{

    statisticsInvariant();
    points_ = points_ + amount;
    statisticsInvariant();

}

void Student::Statistics::reducePoints(unsigned amount)
{

    statisticsInvariant();

    if ((int)points_ - (int)amount < 0){
        throw Common::StateException("Negative points.");
        return;
    }

    points_ -= amount;
    statisticsInvariant();

}

unsigned Student::Statistics::getPoints() const
{

    return points_;

}

void Student::Statistics::addCredits(unsigned amount)
{

    statisticsInvariant();
    credits_ = credits_ + amount;
    statisticsInvariant();

}

void Student::Statistics::reduceCredits(unsigned amount)
{

    statisticsInvariant();

    // If int is negative while comparing unsigned and int, the int is
    // transformed to positive and the compare doesn't work.
    // Adding (int) transforms unsigned to int and the comparing is
    // again possible as it should be.
    if (credits_ - (int)amount < MAX_LOAN_ALLOWANCE_){
        throw Common::StateException("MAX_LOAN_ALLOWANCE > credits.");
        return;
    }

    credits_ -= amount;
    statisticsInvariant();

}

int Student::Statistics::getCreditBalance() const
{

    return credits_;

}

void Student::Statistics::statisticsInvariant() const
{

    Q_ASSERT(this->getPoints() >= 0);
    Q_ASSERT(this->getCreditBalance() >= MAX_LOAN_ALLOWANCE_);

}

