#!/usr/bin/env bash

end_time=$(date +%s)
total_time=$((end_time - start_time))

hours=$((total_time / 3600))
minutes=$(( (total_time % 3600) / 60 ))
seconds=$((total_time % 60))

echo "################################################################################"
echo "# Start at: $(date --iso-8601=seconds -d @$start_time)"
echo "# End at: $(date --iso-8601=seconds -d @$end_time)"
echo "# Total running time: ${hours}h ${minutes}m ${seconds}s"
echo "# ✅ All commands completed successfully!"
echo "# Details in $test_dir"
echo "################################################################################"

exit 0
