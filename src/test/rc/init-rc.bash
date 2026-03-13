#!/usr/bin/env bash

rc_dir="$(dirname "$(readlink -f "${BASH_SOURCE[0]}")")"
echo "rc dir: $rc_dir"
test_src_dir=$rc_dir/..
build_dir=$test_src_dir/..

init() {
    local module_name=$1

    test_dir=$test_src_dir/test_${module_name}_$(date --utc +%Y%m%d-%H%M%S)

    mkdir "$test_dir" && cd "$test_dir"
    echo "Working directory: $(pwd)"
}

start_time=$(date +%s)

source $build_dir/data/macesw_offline_data.sh
