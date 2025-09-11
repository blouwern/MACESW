#include "MACE/Data/SimVertex.h++"
#include "MACE/PhaseI/SimMACEPhaseI/Action/PrimaryGeneratorAction.h++"
#include "MACE/PhaseI/SimMACEPhaseI/Action/TrackingAction.h++"
#include "MACE/PhaseI/SimMACEPhaseI/Analysis.h++"

#include "G4Event.hh"
#include "G4EventManager.hh"
#include "G4MuonMinus.hh"
#include "G4MuonPlus.hh"
#include "G4ProcessType.hh"
#include "G4SteppingManager.hh"
#include "G4Track.hh"
#include "G4TrackingManager.hh"
#include "G4VProcess.hh"

#include <cassert>
#include <vector>

namespace MACE::PhaseI::SimMACEPhaseI::inline Action {

TrackingAction::TrackingAction() :
    PassiveSingleton{this},
    G4UserTrackingAction{},
    fSaveDecayVertexData{true},
    fDecayVertexData{},
    fMessengerRegister{this} {}

auto TrackingAction::PostUserTrackingAction(const G4Track* track) -> void {
    if (fSaveDecayVertexData) {
        UpdateDecayVertexData(*track);
    }
}

auto TrackingAction::UpdateDecayVertexData(const G4Track& track) -> void {
    if (auto& eventManager{*G4EventManager::GetEventManager()};
        eventManager.GetTrackingManager()
            ->GetSteppingManager()
            ->GetfCurrentProcess()
            ->GetProcessType() == fDecay) {
        std::vector<int> secondaryPDGID;
        std::vector<float> secondaryEtotal;
        secondaryPDGID.reserve(track.GetStep()->GetSecondary()->size());
        secondaryEtotal.reserve(track.GetStep()->GetSecondary()->size());
        // if (track.GetDynamicParticle()->GetDefinition()->GetPDGEncoding() == -13) {
        for (auto&& sec : *track.GetStep()->GetSecondary()) {
            secondaryPDGID.emplace_back(sec->GetParticleDefinition()->GetPDGEncoding());
            secondaryEtotal.emplace_back(sec->GetTotalEnergy());
        }
        auto& vertex{fDecayVertexData.emplace_back(std::make_unique_for_overwrite<Mustard::Data::Tuple<MACE::Data::SimDecayVertex>>())};
        Get<"EvtID">(*vertex) = eventManager.GetConstCurrentEvent()->GetEventID();
        Get<"TrkID">(*vertex) = track.GetTrackID();
        Get<"PDGID">(*vertex) = track.GetParticleDefinition()->GetPDGEncoding();
        Get<"SecPDGID">(*vertex) = std::move(secondaryPDGID);
        Get<"SecEtotal">(*vertex) = std::move(secondaryEtotal);
        Get<"t">(*vertex) = track.GetGlobalTime();
        Get<"x">(*vertex) = track.GetPosition();
        Get<"Ek">(*vertex) = track.GetKineticEnergy();
        Get<"p">(*vertex) = track.GetMomentum();
        // }
    }
}

} // namespace MACE::PhaseI::SimMACEPhaseI::inline Action
