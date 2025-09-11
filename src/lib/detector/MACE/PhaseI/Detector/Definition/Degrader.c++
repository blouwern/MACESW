#include "MACE/PhaseI/Detector/Definition/Degrader.h++"
#include "MACE/PhaseI/Detector/Description/Degrader.h++"

#include "Mustard/Utility/LiteralUnit.h++"
#include "Mustard/Utility/PhysicalConstant.h++"

#include "G4NistManager.hh"
#include "G4PVPlacement.hh"
#include "G4Tubs.hh"

namespace MACE::PhaseI::Detector::Definition {

using namespace Mustard::LiteralUnit;
using namespace Mustard::PhysicalConstant;

auto Degrader::Construct(G4bool checkOverlaps) -> void {
    const auto& degrader{Description::Degrader::Instance()};

    const auto solid{Make<G4Tubs>(
        degrader.Name(),
        0,
        degrader.Radius(),
        degrader.Thickness() / 2,
        0,
        2_pi)};
    const auto logic{Make<G4LogicalVolume>(
        solid,
        G4NistManager::Instance()->FindOrBuildMaterial("G4_MYLAR"),
        degrader.Name())};
    Make<G4PVPlacement>(
        G4Transform3D{
            {},
            {0, 0, -40_cm}
    },
        logic,
        degrader.Name(),
        Mother().LogicalVolume(),
        false,
        0,
        checkOverlaps);
}

} // namespace MACE::PhaseI::Detector::Definition
