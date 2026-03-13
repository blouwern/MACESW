#!/usr/bin/env bash
# --SimMMS regression data generation script--

simmms_dir="$(dirname "$(readlink -f "${BASH_SOURCE[0]}")")"

echo "Start SimMMS"
run_command mpiexec -n $n_proc $build_dir/MACE SimMMS $build_dir/SimMMS/run_em_flat.mac

echo "Merging results..."
run_command hadd -ff SimMMS_em_flat_sample.root SimMMS_em_flat_test/*

echo "Drawing & saving regression histograms..."
run_command root -l -q "$simmms_dir/ReadCDCSimHit.cxx(\"SimMMS_em_flat\",\"SimMMS_em_flat_sample.root\",\"$test_src_dir/macesw_regression_data.root\")"
run_command root -l -q "$simmms_dir/ReadMMSSimTrack.cxx(\"SimMMS_em_flat\",\"SimMMS_em_flat_sample.root\",\"$test_src_dir/macesw_regression_data.root\")"
