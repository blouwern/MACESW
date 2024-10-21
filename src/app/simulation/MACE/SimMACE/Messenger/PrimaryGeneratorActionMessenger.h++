#pragma once

#include "Mustard/Extension/Geant4X/Interface/SingletonMessenger.h++"

#include <memory>

class G4UIcmdWithoutParameter;

namespace MACE::SimMACE {

inline namespace Action {
class PrimaryGeneratorAction;
} // namespace Action

inline namespace Messenger {

class PrimaryGeneratorActionMessenger final : public Mustard::Geant4X::SingletonMessenger<PrimaryGeneratorActionMessenger,
                                                                                          PrimaryGeneratorAction> {
    friend Mustard::Env::Memory::SingletonInstantiator;

private:
    PrimaryGeneratorActionMessenger();
    ~PrimaryGeneratorActionMessenger();

public:
    auto SetNewValue(G4UIcommand* command, G4String value) -> void override;

private:
    std::unique_ptr<G4UIcmdWithoutParameter> fSwitchToGPSX;
    std::unique_ptr<G4UIcmdWithoutParameter> fSwitchToFromDataPrimaryGenerator;
};

} // namespace Messenger

} // namespace MACE::SimMACE
