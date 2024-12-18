//
// Created by Dor Shukrun on 27/08/2024.
//

#include "model/spaceships/TIEBomber.h"
#include <iostream>
#include <stdexcept>
#include "model/Position.h"

TIEBomber::TIEBomber(const Position &pos, const std::string &identifier, float speed,
                     const std::shared_ptr<Commander> &pilot,
                     const std::vector<std::shared_ptr<SpaceObject>> &sites)
        : Spaceship(pos, identifier, sites), pilot(pilot){
    if (!pilot) {
        throw std::invalid_argument("Pilot cannot be null");
    }
    this->setSpeed(speed); // Set the speed of the spaceship
    logCreation("TIE Bomber", identifier, speed);
    flyToClosestSpaceSite();
    firstSite = closestSite;


}

void TIEBomber::update() {
    Spaceship::update();
    if (position == destination) interact(closestSite);
    if (destination != closestSite->getPosition() && method == flightMethod::DESTINATION) { // if the destinationCMD changed
        visitedSites.clear();
        firstSite = sitesMap[destination];
    }
}

std::shared_ptr<SpaceObject> TIEBomber::alpabeticalOrderCase(const std::shared_ptr<SpaceObject>& site) {
    std::string siteName = site->getId();
    std::string closestSiteName = closestSite->getId();
    if (siteName < closestSiteName) {
        return site;
    } else {
        return closestSite;
    }
}

void TIEBomber::findClosestSpaceSite() {
    closestSite = nullptr;
    float minDistance = MAX_DISTANCE;
    float distance;
    for (const auto &site: sites) {
        if (visitedSites.find(site) == visitedSites.end()) { // If the site has not been visited
            distance = Position::distance(position, site->getPosition());
            if (distance < minDistance) {
                minDistance = distance;
                closestSite = site;
            } else if (distance == minDistance) closestSite = alpabeticalOrderCase(site);
        }
    }
}

void TIEBomber::flyToClosestSpaceSite() {
    if (visitedSites.size() == sites.size()) {
        visitedSites.clear(); // Reset visited sites if all sites have been visited
        move(firstSite->getPosition()); // start the routine again
    }

    findClosestSpaceSite(); // Find the closest site and update the closestSite property
    move(closestSite->getPosition());

}

void TIEBomber::interact(std::shared_ptr<SpaceObject> other) {
    visitedSites.insert(other);
    flyToClosestSpaceSite();
}


