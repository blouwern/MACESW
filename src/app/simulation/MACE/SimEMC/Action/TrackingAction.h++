#pragma once

#include "MACE/Data/SimVertex.h++"
#include "MACE/SimEMC/Messenger/AnalysisMessenger.h++"

#include "Mustard/Data/Tuple.h++"
#include "Mustard/Env/Memory/PassiveSingleton.h++"

#include "G4UserTrackingAction.hh"

#include <memory>
#include <vector>

namespace MACE::SimEMC::inline Action {

class TrackingAction final : public Mustard::Env::Memory::PassiveSingleton<TrackingAction>,
                             public G4UserTrackingAction {
public:
    TrackingAction();

    auto PostUserTrackingAction(const G4Track* track) -> void override;

    auto SaveDecayVertexData() const -> auto { return fSaveDecayVertexData; }
    auto SaveDecayVertexData(bool val) -> void { fSaveDecayVertexData = val; }

    auto ClearDecayVertexData() -> void { return fDecayVertexData.clear(); }
    auto DecayVertexData() const -> const auto& { return fDecayVertexData; }

private:
    auto UpdateDecayVertexData(const G4Track& track) -> void;

private:
    bool fSaveDecayVertexData;

    std::vector<std::unique_ptr<Mustard::Data::Tuple<Data::SimDecayVertex>>> fDecayVertexData;

    AnalysisMessenger::Register<TrackingAction> fMessengerRegister;
};

} // namespace MACE::SimEMC::inline Action
