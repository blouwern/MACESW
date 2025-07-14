#include "MACE/PhaseI/SimMACEPhaseI/PhysicsList.h++"

#include "Mustard/Extension/Geant4X/Physics/MuonBiasedDecayPhysics.h++"
#include "Mustard/Extension/Geant4X/Physics/MuoniumSMAndLFVDecayPhysics.h++"

namespace MACE::PhaseI::SimMACEPhaseI {

PhysicsList::PhysicsList() :
    PassiveSingleton{this},
    StandardPhysicsListBase{} {
    // RegisterPhysics(new Mustard::Geant4X::MuonBiasedDecayPhysics{verboseLevel});
    RegisterPhysics(new Mustard::Geant4X::MuoniumSMAndLFVDecayPhysics{verboseLevel});
}

} // namespace MACE::PhaseI::SimMACEPhaseI
