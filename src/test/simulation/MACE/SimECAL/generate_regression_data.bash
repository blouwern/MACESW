#!/usr/bin/env bash
# --SimECAL regression data generation script--

current_dir="$(dirname "$(readlink -f "${BASH_SOURCE[0]}")")"

echo "Start simulation..."
# TODO: Add SimECAL test instance
# e.g.:
# run_command mpiexec -n $n_proc $build_dir/MACE SimTTC $build_dir/SimTTC/run_em_flat.mac

echo "Merging results..."
# TODO: Merge SimECAL test results
# e.g.:
# run_command hadd -ff SimTTC_em_flat_sample.root SimTTC_em_flat_test/*

echo "Drawing & saving regression histograms..."
# TODO: Aggregate SimECAL test results
# e.g.:
# run_command root -l -q "$current_dir/ReadTTCSimHit.cxx(\"SimTTC_em_flat\",\"SimTTC_em_flat_sample.root\",\"$test_root_dir/macesw_regression_data.root\")"
