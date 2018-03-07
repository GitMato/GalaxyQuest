/* --GALAXY QUEST 2017--------------------------------------
 * "Have you tried turning it off and on again"
 *     Hanna Enqvist (276930) hanna.enqvist@student.tut.fi
 *     Tomi Mannila  (211950) tomi.mannila@student.tut.fi
 * ---------------------------------------------------------*/

#ifndef GALAXY_HH
#define GALAXY_HH
#include "igalaxy.hh"
#include "ship.hh"
#include "starsystem.hh"
#include "ieventhandler.hh"
#include "stateexception.hh"
#include "objectnotfoundexception.hh"
#include <QtDebug>
#include <map>


/**
 * @file
 * @brief Galaxy contains all the necessary functions for adding,
 * removing and 'searching' ships and starsystems in the galaxy.
 * Most of the function definitions are found in IGalaxy documentation.
 */

namespace Student {
/**
 * @brief The Galaxy class contains all the necessary functions for adding,
 * removing and 'searching' ships and starsystems in the galaxy.
 * Inherited from IGalaxy.
 */
class Galaxy : public Common::IGalaxy,
        public std::enable_shared_from_this<Galaxy>
{
public:
    /**
     * @brief Constructor
     */
    Galaxy();
    /**
     * @brief Destructor
     */
    ~Galaxy();

    //IGalaxy
    /**
     * @brief Add ship to galaxy.
     * @param ship The ship which is added to the galaxy.
     * @post Ship is added to the galaxy.
     * @exception StateException If the galaxy contains the
     * ship object already.
     * @post Exception guarantee: strong
     */
    virtual void addShip(std::shared_ptr<Common::Ship> ship);
    /**
     * @brief Remove ship from the galaxy.
     * @param ship The ship which will be removed.
     * @post Ship is removed from the galaxy
     * @exception ObjectNotFoundException, if the ship does not exist
     * @post Exception guarantee: strong
     */
    virtual void removeShip(std::shared_ptr<Common::Ship> ship);
    /**
     * @brief Adds a StarSystem to the galaxy.
     * @param starSystem StarSystem to be added to the galaxy.
     * @post StarSystem is added to the galaxy.
     * @exception StateException, if a StarSystem with the same name,
     * id or location already exists in the galaxy.
     * @post Exception guarantee: strong
     */
    virtual void addStarSystem(
            std::shared_ptr<Common::StarSystem> starSystem);

    /**
     * @brief Return all the ships in the galaxy.
     * @return Shared pointer to a vector which contains all
     * the ships in the galaxy.
     * @post Exception guarantee: nothrow
     */
    virtual std::shared_ptr<ShipVector> getShips();
    /**
     * @brief Return StarSystems which are in range.
     * @param origin StarSystem which acts as an origin
     * @param range How far will we get the StarSystems
     * @exception Throws an ObjectNotFoundException, if the
     * StarSystem is not in the galaxy.
     * @return StarSystemVector which contains all the StarSystems
     * in range (empty if no StarSystems in range).
     * @post Exception guarantee: strong
     */
    virtual Common::StarSystem::StarSystemVector getSystemsInRange
    (std::shared_ptr<Common::StarSystem> origin, int range);
    /**
     * @brief Return random system form the galaxy.
     * @return Shared pointer to the random StarSystem.
     * @exception ObjectNotFoundException, if the galaxy has no StarSystems.
     * @post Exception guarantee: strong
     */
    virtual std::shared_ptr<Common::StarSystem> getRandomSystem();

    /**
     * @brief Return all the ships in certain StarSystem.
     * @param name The name of the StarSystem.
     * @return ShipVector which contains all the ships in the StarSystem.
     * @exception ObjectNotFoundException, if the StarSystem with
     * the name does not exist.
     * @post Exception guarantee: strong
     */
    ShipVector getShipsInStarSystem(std::string name);

    /**
     * @brief Return the StarSystem with a certain name.
     * @param name The name of the wanted StarSystem.
     * @return Pointer to the wanted StarSystem.
     * @exception ObjectNotFoundException, if the StarSystem with a
     * certain name does not exist.
     * @post Exception guarantee: strong
     */
    std::shared_ptr<Common::StarSystem> getStarSystemByName(std::string name);
    /**
     * @brief Return StarSystem with a certain Id.
     * @param id The Id of the wanted StarSystem.
     * @return Shared pointer to the wanted StarSystem.
     * @exception ObjectNotFoundException, if the StarSystem with the
     * certain Id does not exist.
     * @post Exception guarantee: strong
     */
    std::shared_ptr<Common::StarSystem> getStarSystemById(unsigned id);

    // Not in IGalaxy
    /**
     * @return a vector which contains all the starsystems in the galaxy
     * @post Exception guarantee: nothrow
     */
    Common::StarSystem::StarSystemVector getStarsystems();

private:

    /**
     * @brief shipsInGalaxy_ Common::IGalaxy::ShipVector which contains
     * all ships in the galaxy.
     */
    Common::IGalaxy::ShipVector shipsInGalaxy_;

    /**
     * @brief starsystemsInGalaxy_ Vector which contains all the shared
     * pointers to star systems.
     */
    std::vector<std::shared_ptr<Common::StarSystem>> starsystemsInGalaxy_;

    void galaxyInvariant() const;
    /**
     * @brief Checks all the ships in the galaxy for dublicate ships
     * @return true - if no dublicate ships are found.
     * false - if dublicate ship is found.
     */
    bool checkDuplicateShips() const;
    /**
     * @brief Checks all the star systems in the galaxy
     * for dublicate star systems
     * @return true - if no dublicate star systems are found.
     * false - if dublicate star system is found.
     */
    bool checkDuplicateStarsystems() const;

};
}//Student

#endif // GALAXY_HH
