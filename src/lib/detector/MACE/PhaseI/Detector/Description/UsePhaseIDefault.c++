#include "MACE/Detector/Description/Accelerator.h++"
#include "MACE/Detector/Description/ECAL.h++"
#include "MACE/Detector/Description/Target.h++"
#include "MACE/PhaseI/Detector/Description/UsePhaseIDefault.h++"

#include "Mustard/Utility/LiteralUnit.h++"

namespace MACE::PhaseI::Detector::Description {

auto UsePhaseIDefault() -> void {
    using namespace Mustard::LiteralUnit::Length;
    using namespace Mustard::LiteralUnit::Time;
    using namespace Mustard::LiteralUnit::Energy;
    namespace MACE = MACE::Detector::Description;
    { // set accelerator up/downstream length to a random equal value
        auto& accelerator{MACE::Accelerator::Instance()};
        accelerator.MaxPotentialPosition(0);
        accelerator.AccelerateFieldLength(2);
        accelerator.DecelerateFieldLength(2);
    }
    { // Use cylinder target
        auto& target{MACE::Target::Instance()};
        target.ShapeType(MACE::Target::TargetShapeType::Cylinder);
        target.FormationProbability(0);
    }
    { // bigger windows for ECAL
        auto& ecal{MACE::ECAL::Instance()};
        ecal.InnerRadius(25_cm);
        ecal.CrystalHypotenuse(24_cm);
        ecal.UpstreamWindowRadius(100_mm);
        ecal.DownstreamWindowRadius(100_mm);
        ecal.ScintillationEnergyBin({3.300891_eV, 3.394291_eV, 3.459551_eV, 3.515883_eV, 3.557591_eV, 3.591915_eV,
                                     3.622042_eV, 3.644458_eV, 3.678815_eV, 3.690132_eV, 3.715531_eV, 3.728362_eV,
                                     3.747776_eV, 3.768708_eV, 3.787216_eV, 3.80725_eV, 3.820723_eV, 3.847958_eV,
                                     3.871416_eV, 3.9022_eV, 3.932045_eV, 4.042466_eV, 4.157667_eV, 4.193192_eV,
                                     4.224366_eV, 4.24096_eV, 4.257685_eV, 4.274542_eV, 4.291534_eV, 4.306942_eV,
                                     4.343328_eV, 4.359111_eV, 4.396388_eV, 4.437953_eV, 4.471035_eV, 4.511202_eV,
                                     4.546346_eV, 4.602552_eV, 4.662178_eV, 4.733725_eV, 4.883613_eV, 5.114986_eV});
        ecal.ScintillationComponent1({0.152652, 0.190301, 0.233538, 0.282997, 0.328661, 0.379536,
                                      0.430119, 0.47672, 0.531663, 0.57447, 0.617499, 0.656175,
                                      0.695466, 0.729048, 0.768509, 0.803861, 0.841795, 0.88913,
                                      0.937399, 0.977291, 1.0, 0.972946, 0.880537, 0.821459,
                                      0.754517, 0.691979, 0.640116, 0.591668, 0.540922, 0.501151,
                                      0.452269, 0.413595, 0.35813, 0.307095, 0.264469, 0.218419,
                                      0.182053, 0.129528, 0.081253, 0.047185, 0.017148, 0.0});
        ecal.ScintillationYield(3500);
        ecal.ScintillationTimeConstant1(30_ns);
        ecal.MPPCNPixelRows({8, 8, 8, 8, 8, 8, 8, 8, 8, 8});
    }
}

} // namespace MACE::PhaseI::Detector::Description
