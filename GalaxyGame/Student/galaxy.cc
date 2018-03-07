/* --GALAXY QUEST 2017--------------------------------------
 * "Have you tried turning it off and on again"
 *     Hanna Enqvist (276930) hanna.enqvist@student.tut.fi
 *     Tomi Mannila  (211950) tomi.mannila@student.tut.fi
 * ---------------------------------------------------------*/

#include "galaxy.hh"

Student::Galaxy::Galaxy()
{
}

Student::Galaxy::~Galaxy()
{
}

void Student::Galaxy::addShip(std::shared_ptr<Common::Ship> ship)
{

    Student::Galaxy::galaxyInvariant();

    // Finding duplicates
    int duplicateFound = 0;
    for (unsigned int i = 0; i < shipsInGalaxy_.size(); i++){
        if(shipsInGalaxy_[i] == ship){

            throw Common::StateException("Ship is already in the vector");
            duplicateFound += 1;
            return; // if duplicate ship is found, no changes are made
        }
    }

    std::vector<std::shared_ptr<Common::Ship>>
            shipsInGalaxy_temp = shipsInGalaxy_;
    shipsInGalaxy_temp.push_back(ship);

    shipsInGalaxy_.swap(shipsInGalaxy_temp);

    // Post
    Q_ASSERT(shipsInGalaxy_[shipsInGalaxy_.size() - 1] == ship);

    Student::Galaxy::galaxyInvariant();

}

void Student::Galaxy::removeShip(std::shared_ptr<Common::Ship> ship)
{

    Student::Galaxy::galaxyInvariant();

    for (unsigned int i = 0; i < shipsInGalaxy_.size(); i++){
        // Compare ships
        if (shipsInGalaxy_[i] == ship){
            shipsInGalaxy_.erase(shipsInGalaxy_.begin() + i);
            return;
        }
        // if vector reaches its final cell and the ships don't match,
        // throw the exception
        if (i == shipsInGalaxy_.size()-1){
            throw Common::ObjectNotFoundException(
                        "That ship does not exist.");
            return;
        }
    }

    //Post
    for (unsigned int j = 0; j < shipsInGalaxy_.size(); j++){
        Q_ASSERT(shipsInGalaxy_[j] != ship);
    }
    Student::Galaxy::galaxyInvariant();

}

void Student::Galaxy::addStarSystem(
        std::shared_ptr<Common::StarSystem> starSystem)
{

    Student::Galaxy::galaxyInvariant();

    int starSystemId = starSystem->getId();
    std::string starSystemName = starSystem->getName();
    int coord_x = starSystem->getCoordinates().x;
    int coord_y = starSystem->getCoordinates().y;

    // These variables are short from compare_id etc.
    int comp_id;
    std::string comp_name;
    int comp_x;
    int comp_y;

    if(starsystemsInGalaxy_.size() != 0){

        // Compare information with each star system in galaxy
        for(unsigned int i = 0; i < starsystemsInGalaxy_.size(); i++){

            comp_id = starsystemsInGalaxy_[i]->getId();
            comp_name = starsystemsInGalaxy_[i]->getName();
            comp_x = starsystemsInGalaxy_[i]->getCoordinates().x;
            comp_y = starsystemsInGalaxy_[i]->getCoordinates().y;

            if(comp_id == starSystemId || comp_name == starSystemName ||
                    ( coord_x == comp_x && coord_y == comp_y)){

                throw Common::StateException(
                            "Starsystem is already in the vector");
                return;
            }
        }
    }

    starsystemsInGalaxy_.push_back(starSystem);

    // Post
    Q_ASSERT(starsystemsInGalaxy_[starsystemsInGalaxy_.size()-1] ==
            starSystem);
    Student::Galaxy::galaxyInvariant();

}

std::shared_ptr<Common::IGalaxy::ShipVector> Student::Galaxy::getShips()
{

    Student::Galaxy::galaxyInvariant();
    std::shared_ptr<Common::IGalaxy::ShipVector> shipsInGalaxy_ptr =
            std::make_shared<Common::IGalaxy::ShipVector>(shipsInGalaxy_);
    return shipsInGalaxy_ptr;
}

Common::StarSystem::StarSystemVector Student::Galaxy::getSystemsInRange(
        std::shared_ptr<Common::StarSystem> origin, int range)
{

    Student::Galaxy::galaxyInvariant();
    Common::StarSystem::StarSystemVector starSystemsInRange;

    int match = 0;
    for(unsigned int o = 0; o < starsystemsInGalaxy_.size(); o++){
        if (starsystemsInGalaxy_[o] == origin){
            match +=1;
            break;
        }
    }
    if (match == 0){
        throw Common::ObjectNotFoundException(
                    "Origin starsystem not found in the galaxy.");
        return starSystemsInRange;
    }

    int originX = origin->getCoordinates().x;
    int originY = origin->getCoordinates().y;

    // comp_x is a short from compare_x value
    int comp_x;
    int comp_y;
    double distance;

    for (unsigned int i = 0; i < starsystemsInGalaxy_.size(); i++){

        distance = 0;
        comp_x = starsystemsInGalaxy_[i]->getCoordinates().x;
        comp_y = starsystemsInGalaxy_[i]->getCoordinates().y;

        // can be observed in utility.cc (Course)
        distance = Common::distance(originX, originY, comp_x, comp_y);

        if (distance < range && distance != 0){
            starSystemsInRange.push_back(starsystemsInGalaxy_[i]);
        }

    }
    Student::Galaxy::galaxyInvariant();
    return starSystemsInRange;

}

std::shared_ptr<Common::StarSystem> Student::Galaxy::getRandomSystem()
{

    Student::Galaxy::galaxyInvariant();

    int randomIndex = 0;
    if (starsystemsInGalaxy_.size() != 0){

        // randomIndex is generated in utility.cc (Course)
        randomIndex = Common::randomMinMax(0, starsystemsInGalaxy_.size()-1);

    } else {
        throw Common::ObjectNotFoundException("No systems in the galaxy.");
        return nullptr; // if there is no systems in galaxy, return nullptr
    }
    Student::Galaxy::galaxyInvariant();
    return starsystemsInGalaxy_[randomIndex];

}

Common::IGalaxy::ShipVector Student::Galaxy::getShipsInStarSystem(
        std::__cxx11::string name)
{

    Student::Galaxy::galaxyInvariant();
    Common::IGalaxy::ShipVector shipsInStarSystem;

    for (unsigned int i = 0; i < starsystemsInGalaxy_.size(); i++){
        Common::StarSystem starsystem = *starsystemsInGalaxy_[i];
        if (starsystem.getName() == name){
            for (unsigned int j = 0; j < shipsInGalaxy_.size(); j++){
                Common::Ship& ship = *shipsInGalaxy_[j];
                if (ship.getLocation() == starsystemsInGalaxy_[i]){
                    shipsInStarSystem.push_back(shipsInGalaxy_[j]);
                }
            }
            // No need to continue the for-loop in starsystemsInGalaxy_ if
            // names already matched.
            break;

        } else if (starsystem.getName() != name &&
                   i == starsystemsInGalaxy_.size()-1){
            // If names didn't match and starsystemsInGalaxy_ reaches
            // its final item, shipsInStarSystem vector is empty.
            throw Common::ObjectNotFoundException(
                        "Starsystem with that name doesn't exist.");
        }
    }
    return shipsInStarSystem;

}

std::shared_ptr<Common::StarSystem> Student::Galaxy::getStarSystemByName(
        std::__cxx11::string name)
{

    Student::Galaxy::galaxyInvariant();

    for (unsigned int i = 0; i < starsystemsInGalaxy_.size(); i++){
        if (starsystemsInGalaxy_[i]->getName() == name){
            return starsystemsInGalaxy_[i];
        }
    }
    throw Common::ObjectNotFoundException(
                "Starsystem with that name doesn't exist.");
    return nullptr;

}

std::shared_ptr<Common::StarSystem> Student::Galaxy::getStarSystemById(
        unsigned id)
{

    Student::Galaxy::galaxyInvariant();
    std::shared_ptr<Common::StarSystem> starsystemWithTheID;

    for (unsigned int i = 0; i < starsystemsInGalaxy_.size(); i++){
        if(starsystemsInGalaxy_[i]->getId() == id){
            starsystemWithTheID = starsystemsInGalaxy_[i];
            break;
        }
        if (i == starsystemsInGalaxy_.size()-1){
            throw Common::ObjectNotFoundException(
                        "Starsystem with the id doesn't exist.");
        }
    }
    return starsystemWithTheID;

}

Common::StarSystem::StarSystemVector Student::Galaxy::getStarsystems()
{

    Student::Galaxy::galaxyInvariant();
    return starsystemsInGalaxy_;

}

void Student::Galaxy::galaxyInvariant() const
{

    Q_ASSERT(this->checkDuplicateStarsystems());
    Q_ASSERT(this->checkDuplicateShips());

}

// Check for possible duplicates in shipsInGalaxy_
bool Student::Galaxy::checkDuplicateShips() const
{

    // Go to for-loop only if there are more than 1 ships
    // (Do not compare the same index to its self)
    if (shipsInGalaxy_.size() > 1){
        unsigned int j;
        for (unsigned int i = 0; i < shipsInGalaxy_.size(); i++){

            for (j = i+1 ; j < shipsInGalaxy_.size(); j++){

                if (shipsInGalaxy_[i] == shipsInGalaxy_[j]){
                    return false;
                }
            }
        }
    }
    return true;

}


// Check for possible duplicates in starsystemsInGalaxy_
// (name, Id, coordinates)
bool Student::Galaxy::checkDuplicateStarsystems() const
{

    // Do not compare the same index to its self
    if (starsystemsInGalaxy_.size() > 1){
        unsigned int j;
        for (unsigned int i = 0; i < starsystemsInGalaxy_.size(); i++){
            for (j = i+1; j < starsystemsInGalaxy_.size(); j++){
                if (starsystemsInGalaxy_[i]->getName() ==
                        starsystemsInGalaxy_[j]->getName()){
                    return false;
                } else if (starsystemsInGalaxy_[i]->getId() ==
                           starsystemsInGalaxy_[j]->getId()){
                    return false;
                } else if (starsystemsInGalaxy_[i]->getCoordinates() ==
                           starsystemsInGalaxy_[j]->getCoordinates()){
                    return false;
                }
            }
        }
    }
    return true;
}

