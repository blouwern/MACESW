#!/usr/bin/env bash
# --SimTTC regression test script--

module_name='SimTTC'
simttc_dir="$(dirname "$(readlink -f "${BASH_SOURCE[0]}")")"

source $simttc_dir/../../../rc/init-rc.bash
source $simttc_dir/../../../rc/run_command-rc.bash
source $simttc_dir/../../../rc/parexec-rc.bash

init $module_name

echo "Start SimTTC"
run_command parexec $build_dir/MACE SimTTC --seed 0 $build_dir/SimTTC/run_em_flat.mac

echo "Merging results..."
run_command hadd -ff SimTTC_em_flat_test.root SimTTC_em_flat_test/*

echo "Generating regression report..."
run_command root -l -q "$simttc_dir/TestTTCSimHit.cxx(\"SimTTC_em_flat\",\"SimTTC_em_flat_test.root\",\"$test_src_dir/macesw_regression_data.root\")"

source $simttc_dir/../../../rc/summarize-rc.bash 
