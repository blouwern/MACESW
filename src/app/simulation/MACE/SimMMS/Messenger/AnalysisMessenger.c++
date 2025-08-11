#include "MACE/SimMMS/Action/PrimaryGeneratorAction.h++"
#include "MACE/SimMMS/Action/TrackingAction.h++"
#include "MACE/SimMMS/Analysis.h++"
#include "MACE/SimMMS/Messenger/AnalysisMessenger.h++"

#include "G4UIcmdWithABool.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIdirectory.hh"

#include <string_view>

namespace MACE::SimMMS::inline Messenger {

AnalysisMessenger::AnalysisMessenger() :
    SingletonMessenger{},
    fDirectory{},
    fSavePrimaryVertexData{},
    fSaveDecayVertexData{},
    fSaveTTCHitData{},
    fSaveTTCSiPMHitData{},
    fSaveCDCHitData{} {

    fDirectory = std::make_unique<G4UIdirectory>("/MACE/Analysis/");
    fDirectory->SetGuidance("MACE::SimMMS::Analysis controller.");

    fSavePrimaryVertexData = std::make_unique<G4UIcmdWithABool>("/MACE/Analysis/SavePrimaryVertexData", this);
    fSavePrimaryVertexData->SetGuidance("Save primary vertex data if enabled.");
    fSavePrimaryVertexData->SetParameterName("mode", false);
    fSavePrimaryVertexData->AvailableForStates(G4State_Idle);

    fSaveDecayVertexData = std::make_unique<G4UIcmdWithABool>("/MACE/Analysis/SaveDecayVertexData", this);
    fSaveDecayVertexData->SetGuidance("Save decay vertex data if enabled.");
    fSaveDecayVertexData->SetParameterName("mode", false);
    fSaveDecayVertexData->AvailableForStates(G4State_Idle);

    fSaveTTCHitData = std::make_unique<G4UIcmdWithABool>("/MACE/Analysis/SaveTTCHitData", this);
    fSaveTTCHitData->SetGuidance("Save good TTC hit data if enabled.");
    fSaveTTCHitData->SetParameterName("mode", false);
    fSaveTTCHitData->AvailableForStates(G4State_Idle);

    fSaveTTCSiPMHitData = std::make_unique<G4UIcmdWithABool>("/MACE/Analysis/SaveTTCSiPMHitData", this);
    fSaveTTCSiPMHitData->SetGuidance("Save TTCSiPM hit data if enabled.");
    fSaveTTCSiPMHitData->SetParameterName("mode", false);
    fSaveTTCSiPMHitData->AvailableForStates(G4State_Idle);

    fSaveCDCHitData = std::make_unique<G4UIcmdWithABool>("/MACE/Analysis/SaveCDCHitData", this);
    fSaveCDCHitData->SetGuidance("Save CDC hit data if enabled.");
    fSaveCDCHitData->SetParameterName("mode", false);
    fSaveCDCHitData->AvailableForStates(G4State_Idle);
}

AnalysisMessenger::~AnalysisMessenger() = default;

auto AnalysisMessenger::SetNewValue(G4UIcommand* command, G4String value) -> void {
    if (command == fSavePrimaryVertexData.get()) {
        Deliver<PrimaryGeneratorAction>([&](auto&& r) {
            r.SavePrimaryVertexData(fSavePrimaryVertexData->GetNewBoolValue(value));
        });
    } else if (command == fSaveDecayVertexData.get()) {
        Deliver<TrackingAction>([&](auto&& r) {
            r.SaveDecayVertexData(fSaveDecayVertexData->GetNewBoolValue(value));
        });
    } else if (command == fSaveTTCHitData.get()) {
        Deliver<Analysis>([&](auto&& r) {
            r.SaveTTCHitData(fSaveTTCHitData->GetNewBoolValue(value));
        });
    } else if (command == fSaveTTCSiPMHitData.get()) {
        Deliver<Analysis>([&](auto&& r) {
            r.SaveTTCSiPMHitData(fSaveTTCSiPMHitData->GetNewBoolValue(value));
        });
    } else if (command == fSaveCDCHitData.get()) {
        Deliver<Analysis>([&](auto&& r) {
            r.SaveCDCHitData(fSaveCDCHitData->GetNewBoolValue(value));
        });
    }
}

} // namespace MACE::SimMMS::inline Messenger
