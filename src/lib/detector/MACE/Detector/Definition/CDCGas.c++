#include "MACE/Detector/Definition/CDCGas.h++"
#include "MACE/Detector/Description/CDC.h++"
#include "MACE/Utility/LiteralUnit.h++"

#include "G4PVPlacement.hh"
#include "G4Polycone.hh"
#include "G4Transform3D.hh"

#include "gsl/gsl"

#include <array>

namespace MACE::Detector::Definition {

using namespace MACE::LiteralUnit::MathConstantSuffix;

auto CDCGas::Construct(G4bool checkOverlaps) -> void {
    const auto& cdc{Description::CDC::Instance()};
    const auto name{cdc.Name() + "Gas"};
    const auto zI{cdc.GasInnerLength() / 2};
    const auto zO{cdc.GasOuterLength() / 2};
    const auto rI{cdc.GasInnerRadius()};
    const auto rO{cdc.GasOuterRadius()};

    const std::array zPlaneList{-zO, -zI, zI, zO};
    const std::array rInnerList{rO, rI, rI, rO};
    const std::array rOuterList{rO, rO, rO, rO};

    const auto solid{Make<G4Polycone>(
        name,
        0,
        2_pi,
        zPlaneList.size(),
        zPlaneList.data(),
        rInnerList.data(),
        rOuterList.data())};
    const auto logic{Make<G4LogicalVolume>(
        solid,
        cdc.GasMaterial(),
        name)};
    Make<G4PVPlacement>(
        G4Transform3D{},
        logic,
        name,
        Mother().LogicalVolume().get(),
        false,
        0,
        checkOverlaps);
}

} // namespace MACE::Detector::Definition
