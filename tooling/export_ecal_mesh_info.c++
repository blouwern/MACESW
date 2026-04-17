#include "../src/lib/detector/MACE/Detector/Description/ECAL.h++"

auto export_ecal_mesh_info() -> int {
  const auto& ecal{MACE::Detector::Description::ECAL::Instance()};
  const auto& moduleList{ecal.Array().moduleList};

  std::vector<std::vector<int>> moduleNeighborInfo;
  for (auto aModule : moduleList) {
      moduleNeighborInfo.emplace_back(aModule.neighborModuleID);
  }

  return 0;
}
