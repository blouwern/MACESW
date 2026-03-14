#!/usr/bin/env bash
# --SimMACE regression test script--

module_name='SimMACE'
simmace_dir="$(dirname "$(readlink -f "${BASH_SOURCE[0]}")")"

source $simmace_dir/../../../rc/init-rc.bash
source $simmace_dir/../../../rc/run_command-rc.bash
source $simmace_dir/../../../rc/parexec-rc.bash

init $module_name

golden_file="$test_src_dir/macesw_regression_data.root"
if [[ ! -f "$golden_file" ]]; then
    echo "ERROR: $golden_file not found."
    exit 1
fi

echo "Start SimMACE"
run_command parexec $build_dir/MACE SimMACE --seed 0 $build_dir/SimMACE/run_signal.mac

echo "Merging results..."
if [ -d "SimMACE_signal_test" ]; then
    run_command hadd -ff SimMACE_signal_test.root SimMACE_signal_test/*.root
else
    echo "Single file already present."
    run_command mv SimMACE_signal_test*.root SimMACE_signal_test.root
fi

echo "Generating regression report..."
run_command root -l -q "$simmace_dir/TestMCPSimHit.cxx(\"SimMACE_signal\",\"SimMACE_signal_test.root\",\"$golden_file\")"
run_command root -l -q "$simmace_dir/TestTTCSimHit.cxx(\"SimMACE_signal\",\"SimMACE_signal_test.root\",\"$golden_file\")"
run_command root -l -q "$simmace_dir/TestCDCSimHit.cxx(\"SimMACE_signal\",\"SimMACE_signal_test.root\",\"$golden_file\")"
run_command root -l -q "$simmace_dir/TestMMSSimTrack.cxx(\"SimMACE_signal\",\"SimMACE_signal_test.root\",\"$golden_file\")"

source $simmace_dir/../../../rc/summarize-rc.bash
