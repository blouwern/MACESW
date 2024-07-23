#pragma once

#include "Mustard/Env/Memory/PassiveSingleton.h++"

#include "G4VUserActionInitialization.hh"

namespace MACE::SimDose::inline Action {

class ActionInitialization final : public Mustard::Env::Memory::PassiveSingleton<ActionInitialization>,
                                   public G4VUserActionInitialization {
public:
    auto Build() const -> void override;
};

} // namespace MACE::SimDose::inline Action
