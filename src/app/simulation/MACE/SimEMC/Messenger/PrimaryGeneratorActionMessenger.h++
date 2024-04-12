#pragma once

#include "MACE/Extension/Geant4X/SingletonMessenger.h++"

#include <memory>

class G4UIcommand;

namespace MACE::SimEMC {

inline namespace Action {
class PrimaryGeneratorAction;
} // namespace Action

inline namespace Messenger {

class PrimaryGeneratorActionMessenger final : public Geant4X::SingletonMessenger<PrimaryGeneratorActionMessenger,
                                                                                 PrimaryGeneratorAction> {
    friend Env::Memory::SingletonInstantiator;

private:
    PrimaryGeneratorActionMessenger();
    ~PrimaryGeneratorActionMessenger();

public:
    auto SetNewValue(G4UIcommand* command, G4String value) -> void override;

private:
    std::unique_ptr<G4UIcommand> fSwitchToGPSX;
    std::unique_ptr<G4UIcommand> fSwitchToEcoMug;
};

} // namespace Messenger

} // namespace MACE::SimEMC
