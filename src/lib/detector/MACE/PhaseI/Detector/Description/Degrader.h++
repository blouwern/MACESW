#pragma once

#include "Mustard/Detector/Description/DescriptionBase.h++"

#include <string>
#include <utility>

namespace MACE::PhaseI::Detector::Description {

class Degrader final : public Mustard::Detector::Description::DescriptionBase<Degrader> {
    friend Mustard::Env::Memory::SingletonInstantiator;

private:
    Degrader();
    ~Degrader() = default;

public:
    auto Radius() const -> auto { return fRadius; }
    auto Thickness() const -> auto { return fThickness; }

    auto Radius(double val) -> void { fRadius = val; }
    auto Thickness(double val) -> void { fThickness = val; }

private:
    auto ImportAllValue(const YAML::Node& node) -> void override;
    auto ExportAllValue(YAML::Node& node) const -> void override;

private:
    double fRadius;
    double fThickness;
};

} // namespace MACE::PhaseI::Detector::Description
