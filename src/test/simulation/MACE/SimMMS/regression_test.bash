#!/usr/bin/env bash
# --SimMMS regression test script--

simmms_dir="$(dirname "$(readlink -f "${BASH_SOURCE[0]}")")"

echo "Start SimMMS"
run_command parexec $build_dir/MACE SimMMS --seed 0 $build_dir/SimMMS/run_em_flat.mac

echo "Merging results..."
run_command hadd -ff SimMMS_em_flat_test.root SimMMS_em_flat_test/*

echo "Generating regression report..."
run_command root -l -q "$simmms_dir/TestCDCSimHit.cxx(\"SimMMS_em_flat\",\"SimMMS_em_flat_test.root\",\"$test_root_dir/macesw_regression_data.root\")"
run_command root -l -q "$simmms_dir/TestMMSSimTrack.cxx(\"SimMMS_em_flat\",\"SimMMS_em_flat_test.root\",\"$test_root_dir/macesw_regression_data.root\")"

