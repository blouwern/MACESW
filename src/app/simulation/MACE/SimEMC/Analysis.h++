#pragma once

#include "MACE/Data/SensorHit.h++"
#include "MACE/Data/SimHit.h++"
#include "MACE/Data/SimVertex.h++"
#include "MACE/SimEMC/Messenger/AnalysisMessenger.h++"

#include "Mustard/Data/Output.h++"
#include "Mustard/Env/Memory/PassiveSingleton.h++"

#include "G4Types.hh"

#include "gsl/gsl"

#include <filesystem>
#include <memory>
#include <optional>
#include <utility>

class TFile;

namespace MACE::inline Simulation::inline Hit {
class EMCHit;
class EMCPMTHit;
class MCPHit;
} // namespace MACE::inline Simulation::inline Hit

namespace MACE::SimEMC {

class Analysis final : public Mustard::Env::Memory::PassiveSingleton<Analysis> {
public:
    Analysis();

    auto FilePath(std::filesystem::path path) -> void { fFilePath = std::move(path); }
    auto FileMode(std::string mode) -> void { fFileMode = std::move(mode); }
    auto CoincidenceWithEMC(G4bool val) -> void { fCoincidenceWithEMC = val; }
    auto CoincidenceWithMCP(G4bool val) -> void { fCoincidenceWithMCP = val; }

    auto RunBegin(G4int runID) -> void;

    auto SubmitPrimaryVertexData(const std::vector<std::unique_ptr<Mustard::Data::Tuple<Data::SimPrimaryVertex>>>& data) -> void { fPrimaryVertex = &data; }
    auto SubmitDecayVertexData(const std::vector<std::unique_ptr<Mustard::Data::Tuple<Data::SimDecayVertex>>>& data) -> void { fDecayVertex = &data; }
    auto SubmitEMCHC(const std::vector<gsl::owner<EMCHit*>>& hc) -> void { fEMCHit = &hc; }
    auto SubmitEMCPMTHC(const std::vector<gsl::owner<EMCPMTHit*>>& hc) -> void { fEMCPMTHit = &hc; }
    auto SubmitMCPHC(const std::vector<gsl::owner<MCPHit*>>& hc) -> void { fMCPHit = &hc; }
    auto EventEnd() -> void;

    auto RunEnd(Option_t* option = {}) -> void;

private:
    std::filesystem::path fFilePath;
    std::string fFileMode;
    G4bool fCoincidenceWithEMC;
    G4bool fCoincidenceWithMCP;

    std::filesystem::path fLastUsedFullFilePath;

    gsl::owner<TFile*> fFile;
    std::optional<Mustard::Data::Output<Data::SimPrimaryVertex>> fPrimaryVertexOutput;
    std::optional<Mustard::Data::Output<Data::SimDecayVertex>> fDecayVertexOutput;
    std::optional<Mustard::Data::Output<Data::EMCSimHit>> fEMCSimHitOutput;
    std::optional<Mustard::Data::Output<Data::EMCPMTHit>> fEMCPMTHitOutput;
    std::optional<Mustard::Data::Output<Data::MCPSimHit>> fMCPSimHitOutput;

    const std::vector<std::unique_ptr<Mustard::Data::Tuple<Data::SimPrimaryVertex>>>* fPrimaryVertex;
    const std::vector<std::unique_ptr<Mustard::Data::Tuple<Data::SimDecayVertex>>>* fDecayVertex;
    const std::vector<gsl::owner<EMCHit*>>* fEMCHit;
    const std::vector<gsl::owner<EMCPMTHit*>>* fEMCPMTHit;
    const std::vector<gsl::owner<MCPHit*>>* fMCPHit;

    AnalysisMessenger::Register<Analysis> fMessengerRegister;
};

} // namespace MACE::SimEMC
