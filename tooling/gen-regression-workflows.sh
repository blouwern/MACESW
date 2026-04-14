#!/usr/bin/env bash
set -euo pipefail

if [[ $# -ne 2 ]]; then
  echo "Usage: $0 <ModuleName> <TestPath>" >&2
  echo "Hint: <TestPath> should look like /test/<Domain>/<Suite>/<ModuleName>" >&2
  echo "Example: $0 SimMACE /test/simulation/MACE/SimMACE" >&2
  exit 1
fi

module_name="$1"
test_path="$2"

script_dir="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
repo_root="$(cd "${script_dir}/.." && pwd)"
workflow_dir="${repo_root}/.github/workflows"

mkdir -p -v "$workflow_dir"

module_lower="$(echo "$module_name" | tr '[:upper:]' '[:lower:]')"

out_gcc_rel=".github/workflows/regression-test-with-gcc-${module_lower}.yml"
out_clang_rel=".github/workflows/regression-test-with-clang-${module_lower}.yml"
out_gcc="${repo_root}/${out_gcc_rel}"
out_clang="${repo_root}/${out_clang_rel}"

cat > "$out_gcc" <<EOF
name: ${module_name} regression test (AMD64 GNU/Linux GCC)
NOTE: This file is auto-generated

on:
  push:
    branches:
      - main
      - rc
    paths:
      - "${out_gcc_rel}"
      - "src/**"
      - "test/**"
      - "MACE.c\\\\+\\\\+"
      - "**/CMakeLists.txt"
      - "**.cmake"

  pull_request:
    branches:
      - main
      - rc
    paths:
      - "${out_gcc_rel}"
      - "src/**"
      - "test/**"
      - "MACE.c\\\\+\\\\+"
      - "**/CMakeLists.txt"
      - "**.cmake"

permissions:
  contents: read

jobs:
  regression-test-with-gcc-${module_lower}:
    name: ${module_name} regression test (AMD64 GNU/Linux GCC)
    timeout-minutes: 180
    runs-on: ubuntu-latest
    strategy:
      matrix:
        image:
          - url: ghcr.io/zhao-shihan/rgb-docker:mpich
            artifact-name: Regression test report (${module_name}, AMD64 GNU-Linux GCC, MPICH)
          - url: ghcr.io/zhao-shihan/rgb-docker:openmpi
            artifact-name: Regression test report (${module_name}, AMD64 GNU-Linux GCC,OpenMPI)
    container: \${{ matrix.image.url }}
    defaults:
      run:
        shell: bash
    steps:
      - name: Checkout code
        uses: actions/checkout@v4

      - name: Build
        run: |
          . /environment
          mkdir build && cd build
          cmake -G Ninja .. \\
            -DCMAKE_C_COMPILER=gcc \\
            -DCMAKE_C_FLAGS='-march=native' \\
            -DCMAKE_CXX_COMPILER=g++ \\
            -DCMAKE_CXX_FLAGS='-march=native'\\
            -DMACESW_UNITY_BUILD=ON \\
            -DMACESW_FULL_UNITY_BUILD=ON
          ninja

      - name: Run regression test
        run: |
          . /environment
          bash build${test_path}/regression_test.bash --use-hwthreads

      - name: Restore regression report
        uses: actions/upload-artifact@v4
        with:
          name: \${{ matrix.image.artifact-name }}
          path: |
            build/test/test_*/regression_report.root
          retention-days: 90
EOF

cat > "$out_clang" <<EOF
name: ${module_name} regression test (AMD64 GNU/Linux Clang)

on:
  push:
    branches:
      - main
      - rc
    paths:
      - "${out_clang_rel}"
      - "src/**"
      - "test/**"
      - "MACE.c\\\\+\\\\+"
      - "**/CMakeLists.txt"
      - "**.cmake"

  pull_request:
    branches:
      - main
      - rc
    paths:
      - "${out_clang_rel}"
      - "src/**"
      - "test/**"
      - "MACE.c\\\\+\\\\+"
      - "**/CMakeLists.txt"
      - "**.cmake"

permissions:
  contents: read

jobs:
  regression-test-with-clang-${module_lower}:
    name: ${module_name} regression test (AMD64 GNU/Linux Clang)
    timeout-minutes: 180
    runs-on: ubuntu-latest
    strategy:
      matrix:
        image:
          - url: ghcr.io/zhao-shihan/rgb-docker:mpich
            artifact-name: Regression test report (${module_name}, AMD64 GNU-Linux Clang, MPICH)
          - url: ghcr.io/zhao-shihan/rgb-docker:openmpi
            artifact-name: Regression test report (${module_name}, AMD64 GNU-Linux Clang, OpenMPI)
    container: \${{ matrix.image.url }}
    defaults:
      run:
        shell: bash
    steps:
      - name: Checkout code
        uses: actions/checkout@v4

      - name: Build
        run: |
          . /environment
          mkdir build && cd build
          cmake -G Ninja .. \\
            -DCMAKE_C_COMPILER=clang \\
            -DCMAKE_C_FLAGS='-march=native' \\
            -DCMAKE_CXX_COMPILER=clang++ \\
            -DCMAKE_CXX_FLAGS='-march=native' \\
            -DMACESW_UNITY_BUILD=ON \\
            -DMACESW_FULL_UNITY_BUILD=ON
          ninja

      - name: Run regression test
        run: |
          . /environment
          bash build${test_path}/regression_test.bash --use-hwthreads

      - name: Restore regression report
        uses: actions/upload-artifact@v4
        with:
          name: \${{ matrix.image.artifact-name }}
          path: |
            build/test/test_*/regression_report.root
          retention-days: 90
EOF

echo "Wrote: $out_gcc"
echo "Wrote: $out_clang"
