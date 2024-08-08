#pragma once

#include "MACE/Detector/Description/Accelerator.h++"
#include "MACE/Detector/Description/BeamDegrader.h++"
#include "MACE/Detector/Description/BeamMonitor.h++"
#include "MACE/Detector/Description/CDC.h++"
#include "MACE/Detector/Description/ECal.h++"
#include "MACE/Detector/Description/ECalField.h++"
#include "MACE/Detector/Description/ECalMagnet.h++"
#include "MACE/Detector/Description/ECalShield.h++"
#include "MACE/Detector/Description/FieldOption.h++"
#include "MACE/Detector/Description/Filter.h++"
#include "MACE/Detector/Description/MCP.h++"
#include "MACE/Detector/Description/MCPChamber.h++"
#include "MACE/Detector/Description/MMSBeamPipe.h++"
#include "MACE/Detector/Description/MMSField.h++"
#include "MACE/Detector/Description/MMSMagnet.h++"
#include "MACE/Detector/Description/MMSShield.h++"
#include "MACE/Detector/Description/ShieldingWall.h++"
#include "MACE/Detector/Description/Solenoid.h++"
#include "MACE/Detector/Description/TTC.h++"
#include "MACE/Detector/Description/Target.h++"
#include "MACE/Detector/Description/Vacuum.h++"
#include "MACE/Detector/Description/World.h++"
#include "MACE/Simulation/Messenger/NumericMessenger.h++"

#include "Mustard/Env/Memory/PassiveSingleton.h++"

#include "G4VUserDetectorConstruction.hh"

#include <memory>

class G4UserLimits;

namespace Mustard::Detector::Definition {
class DefinitionBase;
} // namespace Mustard::Detector::Definition

namespace MACE::SimDose::inline Action {

class DetectorConstruction final : public Mustard::Env::Memory::PassiveSingleton<DetectorConstruction>,
                                   public G4VUserDetectorConstruction {
public:
    DetectorConstruction();
    ~DetectorConstruction();

    auto SetCheckOverlaps(G4bool checkOverlaps) -> void { fCheckOverlap = checkOverlaps; }

    auto MinDriverStep(double val) -> void { fMinDriverStep = val; }
    auto DeltaChord(double val) -> void { fDeltaChord = val; }

    auto VacuumStepLimit() const -> double;
    auto VacuumStepLimit(double val) -> void;

    auto Construct() -> G4VPhysicalVolume* override;

public:
    using DescriptionInUse = std::tuple<Detector::Description::Accelerator,
                                        Detector::Description::BeamDegrader,
                                        Detector::Description::BeamMonitor,
                                        Detector::Description::CDC,
                                        Detector::Description::ECal,
                                        Detector::Description::ECalField,
                                        Detector::Description::ECalMagnet,
                                        Detector::Description::ECalShield,
                                        Detector::Description::FieldOption,
                                        Detector::Description::Filter,
                                        Detector::Description::MCP,
                                        Detector::Description::MCPChamber,
                                        Detector::Description::MMSBeamPipe,
                                        Detector::Description::MMSField,
                                        Detector::Description::MMSMagnet,
                                        Detector::Description::MMSShield,
                                        Detector::Description::ShieldingWall,
                                        Detector::Description::Solenoid,
                                        Detector::Description::Target,
                                        Detector::Description::TTC,
                                        Detector::Description::Vacuum,
                                        Detector::Description::World>;

private:
    G4bool fCheckOverlap;

    double fMinDriverStep;
    double fDeltaChord;

    std::unique_ptr<G4UserLimits> fVacuumStepLimit;

    std::unique_ptr<Mustard::Detector::Definition::DefinitionBase> fWorld;

    NumericMessenger<DetectorConstruction>::Register<DetectorConstruction> fNumericMessengerRegister;
};

} // namespace MACE::SimDose::inline Action
