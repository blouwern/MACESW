#!/usr/bin/env bash
# --SimMACE regression test script--

simmace_dir="$(dirname "$(readlink -f "${BASH_SOURCE[0]}")")"

echo "Start SimMACE"
run_command parexec $build_dir/MACE SimMACE --seed 0 $build_dir/SimMACE/run_signal.mac

echo "Merging results..."
run_command hadd -ff SimMACE_signal_test.root SimMACE_signal_test/*

echo "Generating regression report..."
run_command root -l -q "$simmace_dir/TestMCPSimHit.cxx(\"SimMACE_signal\",\"SimMACE_signal_test.root\",\"$test_root_dir/macesw_regression_data.root\")"
run_command root -l -q "$simmace_dir/TestTTCSimHit.cxx(\"SimMACE_signal\",\"SimMACE_signal_test.root\",\"$test_root_dir/macesw_regression_data.root\")"
run_command root -l -q "$simmace_dir/TestCDCSimHit.cxx(\"SimMACE_signal\",\"SimMACE_signal_test.root\",\"$test_root_dir/macesw_regression_data.root\")"
run_command root -l -q "$simmace_dir/TestMMSSimTrack.cxx(\"SimMACE_signal\",\"SimMACE_signal_test.root\",\"$test_root_dir/macesw_regression_data.root\")"

