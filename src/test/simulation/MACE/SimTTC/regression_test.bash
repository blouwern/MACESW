#!/usr/bin/env bash
# --SimTTC regression test script--

simttc_dir="$(dirname "$(readlink -f "${BASH_SOURCE[0]}")")"

echo "Start SimTTC"
run_command parexec $build_dir/MACE SimTTC --seed 0 $build_dir/SimTTC/run_em_flat.mac

echo "Merging results..."
run_command hadd -ff SimTTC_em_flat_test.root SimTTC_em_flat_test/*

echo "Generating regression report..."
run_command root -l -q "$simttc_dir/TestTTCSimHit.cxx(\"SimTTC_em_flat\",\"SimTTC_em_flat_test.root\",\"$test_root_dir/macesw_regression_data.root\")"
