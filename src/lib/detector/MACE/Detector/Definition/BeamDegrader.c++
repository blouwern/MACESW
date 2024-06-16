#include "MACE/Detector/Definition/BeamDegrader.h++"
#include "MACE/Detector/Description/Accelerator.h++"
#include "MACE/Detector/Description/BeamDegrader.h++"
#include "MACE/Detector/Description/Target.h++"

#include "Mustard/Utility/LiteralUnit.h++"

#include "G4Box.hh"
#include "G4NistManager.hh"
#include "G4PVPlacement.hh"

namespace MACE::Detector::Definition {

using namespace Mustard::LiteralUnit::Density;

auto BeamDegrader::Enabled() const -> bool {
    return Description::BeamDegrader::Instance().Enabled();
}

auto BeamDegrader::Construct(G4bool checkOverlaps) -> void {
    const auto& degrader{Description::BeamDegrader::Instance()};
    const auto& accelerator{Description::Accelerator::Instance()};
    const auto& target{Description::Target::Instance()};

    G4Transform3D transform;
    switch (const auto z0{(accelerator.UpstreamLength() - accelerator.AccelerateLength()) / 2};
            target.ShapeType()) {
    case Description::Target::TargetShapeType::Cuboid: // clang-format off
        transform = {{}, {0, 0, z0 - target.Cuboid().Thickness() - degrader.DistanceToTarget() - degrader.Thickness() / 2}}; // clang-format on
        break;
    case Description::Target::TargetShapeType::MultiLayer: // clang-format off
        transform = {{}, {0, 0, z0 - target.MultiLayer().Width() / 2 - degrader.DistanceToTarget() - degrader.Thickness() / 2}}; // clang-format on
        break;
    case Description::Target::TargetShapeType::Cylinder: // clang-format off
        transform = {{}, {0, 0, z0 - target.Cylinder().Thickness() / 2 - degrader.DistanceToTarget() - degrader.Thickness() / 2}}; // clang-format on
        break;
    }

    const auto solid{Make<G4Box>(
        degrader.Name(),
        degrader.Width() / 2,
        degrader.Width() / 2,
        degrader.Thickness() / 2)};
    const auto logic{Make<G4LogicalVolume>(
        solid,
        G4NistManager::Instance()->FindOrBuildMaterial(degrader.MaterialName()),
        degrader.Name())};
    Make<G4PVPlacement>(
        transform,
        logic,
        degrader.Name(),
        Mother().LogicalVolume(),
        false,
        0,
        checkOverlaps);
}

} // namespace MACE::Detector::Definition
