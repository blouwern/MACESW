#include "MACE/PhaseI/SimMACEPhaseI/Action/PrimaryGeneratorAction.h++"
#include "MACE/PhaseI/SimMACEPhaseI/Messenger/PrimaryGeneratorActionMessenger.h++"

#include "G4UIcmdWithoutParameter.hh"

namespace MACE::PhaseI::SimMACEPhaseI::inline Messenger {

PrimaryGeneratorActionMessenger::PrimaryGeneratorActionMessenger() :
    SingletonMessenger{},
    fSwitchToGPSX{},
    fSwitchToEcoMug{},
    fSwitchToFromDataPrimaryGenerator{} {

    fSwitchToGPSX = std::make_unique<G4UIcmdWithoutParameter>("/MACE/Generator/SwitchToGPSX", this);
    fSwitchToGPSX->SetGuidance("If set then the G4GeneralParticleSource will be used.");
    fSwitchToGPSX->AvailableForStates(G4State_Idle);

    fSwitchToEcoMug = std::make_unique<G4UIcmdWithoutParameter>("/MACE/Generator/SwitchToEcoMug", this);
    fSwitchToEcoMug->SetGuidance("If set then the EcoMug generator will be used.");
    fSwitchToEcoMug->AvailableForStates(G4State_Idle);

    fSwitchToFromDataPrimaryGenerator = std::make_unique<G4UIcmdWithoutParameter>("/MACE/Generator/SwitchToFromDataPrimaryGenerator", this);
    fSwitchToFromDataPrimaryGenerator->SetGuidance("If set then the generator from data will be used.");
    fSwitchToFromDataPrimaryGenerator->AvailableForStates(G4State_Idle);
}

PrimaryGeneratorActionMessenger::~PrimaryGeneratorActionMessenger() = default;

void PrimaryGeneratorActionMessenger::SetNewValue(G4UIcommand* command, G4String) {
    if (command == fSwitchToGPSX.get()) {
        Deliver<PrimaryGeneratorAction>([&](auto&& r) {
            r.SwitchToGPSX();
        });
    } else if (command == fSwitchToEcoMug.get()) {
        Deliver<PrimaryGeneratorAction>([&](auto&& r) {
            r.SwitchToEcoMug();
        });
    } else if (command == fSwitchToFromDataPrimaryGenerator.get()) {
        Deliver<PrimaryGeneratorAction>([&](auto&& r) {
            r.SwitchToFromDataPrimaryGenerator();
        });
    }
}

} // namespace MACE::PhaseI::SimMACEPhaseI::inline Messenger
