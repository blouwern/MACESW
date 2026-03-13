#!/usr/bin/env bash
# --SimTTC regression data generation script--

simttc_dir="$(dirname "$(readlink -f "${BASH_SOURCE[0]}")")"

echo "Start SimTTC"
run_command mpiexec -n $n_proc $build_dir/MACE SimTTC $build_dir/SimTTC/run_em_flat.mac

echo "Merging results..."
run_command hadd -ff SimTTC_em_flat_sample.root SimTTC_em_flat_test/*

echo "Drawing & saving regression histograms..."
run_command root -l -q "$simttc_dir/ReadTTCSimHit.cxx(\"SimTTC_em_flat\",\"SimTTC_em_flat_sample.root\",\"$test_src_dir/macesw_regression_data.root\")"

