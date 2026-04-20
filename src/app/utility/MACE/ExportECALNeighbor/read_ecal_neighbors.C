#include <iostream>
#include <vector>
#include "TTree.h"
#include "TFile.h"

void read_ecal_neighbors() {
    // 打开 ROOT 文件
    TFile *file = TFile::Open("ecal_neighbor_info");
    if (!file || file->IsZombie()) {
        std::cerr << "Error: cannot open file ecal_neighbor_info" << std::endl;
        return;
    }

    // 获取 TTree
    TTree *tree = (TTree*)file->Get("ECALCrystalNeighbors");
    if (!tree) {
        std::cerr << "Error: cannot find TTree ECALCrystalNeighbors" << std::endl;
        return;
    }

    // 设置分支地址
    std::vector<int> *nbor = nullptr;
    tree->SetBranchAddress("neighbors", &nbor);

    // 打开输出文件
    std::ofstream out("read_ecal_neighbors_output.txt");
    if (!out.is_open()) {
        std::cerr << "Error: cannot create read_ecal_neighbors_output.txt" << std::endl;
        return;
    }

    // 循环所有条目
    Long64_t nEntries = tree->GetEntries();
    for (Long64_t i = 0; i < nEntries; ++i) {
        tree->GetEntry(i);
        // 输出当前 vector 的所有元素，空格分隔，一行一个 vector
        for (size_t j = 0; j < nbor->size(); ++j) {
            out << (*nbor)[j];
            if (j != nbor->size() - 1) out << " ";
        }
        out << "\n";
    }

    out.close();
    file->Close();
    std::cout << "Done. Output written to read_ecal_neighbors_output.txt" << std::endl;
}
