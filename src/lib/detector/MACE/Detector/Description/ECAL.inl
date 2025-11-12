namespace MACE::Detector::Description {

inline auto ECAL::ArrayManager::Get(const ECAL* ecal) -> const ArrayInformation& {
    if (fOutdated) {
        fArray = ecal->CalculateArrayInformation();
        fOutdated = false;
    }
    return fArray;
}

inline void ECAL::SetGeometryOutdated() const {
    fArrayManager.SetOutdated();
}

} // namespace MACE::Detector::Description
