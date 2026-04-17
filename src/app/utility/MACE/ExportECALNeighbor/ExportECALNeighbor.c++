// -*- C++ -*-
//
// Copyright (C) 2020-2025  MACESW developers
//
// This file is part of MACESW, Muonium-to-Antimuonium Conversion Experiment
// offline software.
//
// MACESW is free software: you can redistribute it and/or modify it under the
// terms of the GNU General Public License as published by the Free Software
// Foundation, either version 3 of the License, or (at your option) any later
// version.
//
// MACESW is distributed in the hope that it will be useful, but WITHOUT ANY
// WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
// A PARTICULAR PURPOSE. See the GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License along with
// MACESW. If not, see <https://www.gnu.org/licenses/>.

#include "MACE/Detector/Description/ECAL.h++"
#include "MACE/ExportECALNeighbor/ExportECALNeighbor.h++"

#include "Mustard/CLI/BasicCLI.h++"
#include "Mustard/Detector/Description/DescriptionIO.h++"
#include "Mustard/Env/BasicEnv.h++"
#include "Mustard/IO/PrettyLog.h++"
#include "Mustard/Utility/LiteralUnit.h++"

#include "ROOT/RDataFrame.hxx"

#include "fmt/std.h"

#include <filesystem>
#include <functional>
#include <stdexcept>
#include <string>

namespace MACE::ExportECALNeighbor {

using namespace std::string_literals;

ExportECALNeighbor::ExportECALNeighbor() :
    Subprogram{"ExportECALNeighbor", "Export neighbor crystal indeces of each ECAL crystal index"} {}

auto ExportECALNeighbor::Main(int argc, char* argv[]) const -> int {
    Mustard::CLI::BasicCLI<> cli;
    cli->add_argument("-o", "--output").help("Set output directory path.").default_value("ecal_neighbor"s).required().nargs(1);
    Mustard::Env::BasicEnv env(argc, argv, cli);

    const std::filesystem::path outputPath{cli->get("--output")};
    if (std::filesystem::exists(outputPath)) {
        Mustard::Throw<std::runtime_error>(fmt::format("{} already exists", outputPath));
    }
    std::filesystem::create_directories(outputPath);

    ////////////////////////////////////////////////////////////////
    // Construct volumes
    ////////////////////////////////////////////////////////////////

    using namespace Detector::Description;

    const auto& ecal{Detector::Description::ECAL::Instance()};
    const auto& moduleList{ecal.Array().moduleList};


    return EXIT_SUCCESS;
}

} // namespace MACE::ExportECALNeighbor
