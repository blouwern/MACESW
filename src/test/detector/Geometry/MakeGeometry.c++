#include "MACE/Detector/Assembly/MMS.h++"
#include "MACE/Detector/Definition/Accelerator.h++"
#include "MACE/Detector/Definition/AcceleratorField.h++"
#include "MACE/Detector/Definition/BeamDegrader.h++"
#include "MACE/Detector/Definition/BeamMonitor.h++"
#include "MACE/Detector/Definition/CDCBody.h++"
#include "MACE/Detector/Definition/CDCCell.h++"
#include "MACE/Detector/Definition/CDCGas.h++"
#include "MACE/Detector/Definition/CDCSenseLayer.h++"
#include "MACE/Detector/Definition/CDCSuperLayer.h++"
#include "MACE/Detector/Definition/Collimator.h++"
#include "MACE/Detector/Definition/ECALCrystal.h++"
#include "MACE/Detector/Definition/ECALField.h++"
#include "MACE/Detector/Definition/ECALMagnet.h++"
#include "MACE/Detector/Definition/ECALPMTAssemblies.h++"
#include "MACE/Detector/Definition/ECALShield.h++"
#include "MACE/Detector/Definition/MCP.h++"
#include "MACE/Detector/Definition/MCPChamber.h++"
#include "MACE/Detector/Definition/MMSBeamPipe.h++"
#include "MACE/Detector/Definition/MMSField.h++"
#include "MACE/Detector/Definition/MMSMagnet.h++"
#include "MACE/Detector/Definition/MMSShield.h++"
#include "MACE/Detector/Definition/ShieldingWall.h++"
#include "MACE/Detector/Definition/SolenoidBeamPipeS1.h++"
#include "MACE/Detector/Definition/SolenoidBeamPipeS2.h++"
#include "MACE/Detector/Definition/SolenoidBeamPipeS3.h++"
#include "MACE/Detector/Definition/SolenoidBeamPipeT1.h++"
#include "MACE/Detector/Definition/SolenoidBeamPipeT2.h++"
#include "MACE/Detector/Definition/SolenoidFieldS1.h++"
#include "MACE/Detector/Definition/SolenoidFieldS2.h++"
#include "MACE/Detector/Definition/SolenoidFieldS3.h++"
#include "MACE/Detector/Definition/SolenoidFieldT1.h++"
#include "MACE/Detector/Definition/SolenoidFieldT2.h++"
#include "MACE/Detector/Definition/SolenoidS1.h++"
#include "MACE/Detector/Definition/SolenoidS2.h++"
#include "MACE/Detector/Definition/SolenoidS3.h++"
#include "MACE/Detector/Definition/SolenoidShieldS1.h++"
#include "MACE/Detector/Definition/SolenoidShieldS2.h++"
#include "MACE/Detector/Definition/SolenoidShieldS3.h++"
#include "MACE/Detector/Definition/SolenoidShieldT1.h++"
#include "MACE/Detector/Definition/SolenoidShieldT2.h++"
#include "MACE/Detector/Definition/SolenoidT1.h++"
#include "MACE/Detector/Definition/SolenoidT2.h++"
#include "MACE/Detector/Definition/TTC.h++"
#include "MACE/Detector/Definition/Target.h++"
#include "MACE/Detector/Definition/World.h++"

#include "Mustard/Detector/Description/DescriptionIO.h++"
#include "Mustard/Env/BasicEnv.h++"
#include "Mustard/Env/CLI/BasicCLI.h++"
#include "Mustard/Utility/LiteralUnit.h++"

#include "TGeoManager.h"

#include <functional>

int main(int argc, char* argv[]) {
    Mustard::Env::CLI::BasicCLI<> cli;
    Mustard::Env::BasicEnv env(argc, argv, cli);

    ////////////////////////////////////////////////////////////////
    // Construct volumes
    ////////////////////////////////////////////////////////////////

    using namespace MACE::Detector::Definition;

    constexpr auto fCheckOverlap = true;

    // 0

    const auto fWorld{std::make_unique_for_overwrite<World>()};

    // 1

    MACE::Detector::Assembly::MMS mms{*fWorld, fCheckOverlap};

    [[maybe_unused]] auto& ecalField{fWorld->NewDaughter<ECALField>(fCheckOverlap)};
    [[maybe_unused]] auto& ecalShield{fWorld->NewDaughter<ECALShield>(fCheckOverlap)};
    [[maybe_unused]] auto& shieldingWall{fWorld->NewDaughter<ShieldingWall>(fCheckOverlap)};
    [[maybe_unused]] auto& solenoidFieldS1{fWorld->NewDaughter<SolenoidFieldS1>(fCheckOverlap)};
    [[maybe_unused]] auto& solenoidFieldS2{fWorld->NewDaughter<SolenoidFieldS2>(fCheckOverlap)};
    [[maybe_unused]] auto& solenoidFieldS3{fWorld->NewDaughter<SolenoidFieldS3>(fCheckOverlap)};
    [[maybe_unused]] auto& solenoidFieldT1{fWorld->NewDaughter<SolenoidFieldT1>(fCheckOverlap)};
    [[maybe_unused]] auto& solenoidFieldT2{fWorld->NewDaughter<SolenoidFieldT2>(fCheckOverlap)};

    // 2

    [[maybe_unused]] auto& ecalCrystal{ecalField.NewDaughter<ECALCrystal>(fCheckOverlap)};
    [[maybe_unused]] auto& ecalMagnet{ecalField.NewDaughter<ECALMagnet>(fCheckOverlap)};
    [[maybe_unused]] auto& ecalPMTAssemblies{ecalField.NewDaughter<ECALPMTAssemblies>(fCheckOverlap)};
    [[maybe_unused]] auto& mcpChamber{ecalField.NewDaughter<MCPChamber>(fCheckOverlap)};

    [[maybe_unused]] auto& solenoidBeamPipeS1{solenoidFieldS1.NewDaughter<SolenoidBeamPipeS1>(fCheckOverlap)};
    [[maybe_unused]] auto& solenoidS1{solenoidFieldS1.NewDaughter<SolenoidS1>(fCheckOverlap)};
    [[maybe_unused]] auto& solenoidShieldS1{solenoidFieldS1.NewDaughter<SolenoidShieldS1>(fCheckOverlap)};

    [[maybe_unused]] auto& solenoidBeamPipeS2{solenoidFieldS2.NewDaughter<SolenoidBeamPipeS2>(fCheckOverlap)};
    [[maybe_unused]] auto& solenoidS2{solenoidFieldS2.NewDaughter<SolenoidS2>(fCheckOverlap)};
    [[maybe_unused]] auto& solenoidShieldS2{solenoidFieldS2.NewDaughter<SolenoidShieldS2>(fCheckOverlap)};

    [[maybe_unused]] auto& solenoidBeamPipeS3{solenoidFieldS3.NewDaughter<SolenoidBeamPipeS3>(fCheckOverlap)};
    [[maybe_unused]] auto& solenoidS3{solenoidFieldS3.NewDaughter<SolenoidS3>(fCheckOverlap)};
    [[maybe_unused]] auto& solenoidShieldS3{solenoidFieldS3.NewDaughter<SolenoidShieldS3>(fCheckOverlap)};

    [[maybe_unused]] auto& solenoidBeamPipeT1{solenoidFieldT1.NewDaughter<SolenoidBeamPipeT1>(fCheckOverlap)};
    [[maybe_unused]] auto& solenoidShieldT1{solenoidFieldT1.NewDaughter<SolenoidShieldT1>(fCheckOverlap)};
    [[maybe_unused]] auto& solenoidT1{solenoidFieldT1.NewDaughter<SolenoidT1>(fCheckOverlap)};

    [[maybe_unused]] auto& solenoidBeamPipeT2{solenoidFieldT2.NewDaughter<SolenoidBeamPipeT2>(fCheckOverlap)};
    [[maybe_unused]] auto& solenoidShieldT2{solenoidFieldT2.NewDaughter<SolenoidShieldT2>(fCheckOverlap)};
    [[maybe_unused]] auto& solenoidT2{solenoidFieldT2.NewDaughter<SolenoidT2>(fCheckOverlap)};

    // 3

    [[maybe_unused]] auto& mcp{mcpChamber.NewDaughter<MCP>(fCheckOverlap)};

    [[maybe_unused]] auto& acceleratorField{mms.Get<MMSBeamPipe>().NewDaughter<AcceleratorField>(fCheckOverlap)};

    [[maybe_unused]] auto& collimator{solenoidBeamPipeS2.NewDaughter<Collimator>(fCheckOverlap)};

    // 4

    [[maybe_unused]] auto& accelerator{acceleratorField.NewDaughter<Accelerator>(fCheckOverlap)};
    [[maybe_unused]] auto& beamDegrader{acceleratorField.NewDaughter<BeamDegrader>(fCheckOverlap)};
    [[maybe_unused]] auto& beamMonitor{acceleratorField.NewDaughter<BeamMonitor>(fCheckOverlap)};
    [[maybe_unused]] auto& target{acceleratorField.NewDaughter<Target>(fCheckOverlap)};

    ///////////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////////

    Mustard::Detector::Description::DescriptionIO::ExportInstantiated("test.yaml");

    ///////////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////////

    fWorld->Export("test.gdml");
    mms.Get<CDCSenseLayer>().RemoveDaughter<CDCCell>(); // ROOT does not support twisted tube.
    fWorld->Export("test_no_cell.gdml");

    const auto geoManager{std::make_unique<TGeoManager>("MACEGeom", "MACE Geometry")};
    geoManager->Import("test_no_cell.gdml");

    /* // set transparency for jsroot display
    // see form https://github.com/root-project/jsroot/blob/master/docs/JSROOT.md#geometry-viewer

    geoManager->GetVolume(fWorld->LogicalVolume()->GetName())->SetInvisible();
    using Mustard::Detector::Definition::DefinitionBase;
    for (auto&& entity : std::initializer_list<std::reference_wrapper<const DefinitionBase>>{
             ecalCrystal,
             ecalMagnet,
             ecalPMTAssemblies,
             ecalShield,
             mmsMagnet,
             mmsShield,
             shieldingWall,
             solenoidT1,
             solenoidT2,
             solenoidS1,
             solenoidS2,
             solenoidS3}) {
        geoManager->GetVolume(entity.get().LogicalVolume()->GetName())->SetTransparency(60);
    } */

    geoManager->Export("test.root");

    ///////////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////////

    return EXIT_SUCCESS;
}
