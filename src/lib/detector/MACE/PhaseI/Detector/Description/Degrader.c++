#include "MACE/PhaseI/Detector/Description/Degrader.h++"

#include "Mustard/Utility/LiteralUnit.h++"

namespace MACE::PhaseI::Detector::Description {

using namespace Mustard::LiteralUnit::Length;
using namespace Mustard::LiteralUnit::Angle;

Degrader::Degrader() :
    DescriptionBase("Degrader"),
    fRadius{30_mm},
    fThickness{350_um} {}

auto Degrader::ImportAllValue(const YAML::Node& node) -> void {
    ImportValue(node, fRadius, "Radius");
    ImportValue(node, fThickness, "Thickness");
}

auto Degrader::ExportAllValue(YAML::Node& node) const -> void {
    ExportValue(node, fRadius, "Radius");
    ExportValue(node, fThickness, "Thickness");
}

} // namespace MACE::PhaseI::Detector::Description
