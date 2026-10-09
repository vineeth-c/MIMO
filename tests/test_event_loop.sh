#!/usr/bin/env bash
set -euo pipefail

OUTPUT=$("$1" < "$2")

echo "$OUTPUT"

# check valid transitions
grep -q "Idle -> Listening" <<< "$OUTPUT"
grep -q "Listening -> Thinking" <<< "$OUTPUT"
grep -q "Thinking -> Idle" <<< "$OUTPUT"
grep -q "Idle -> Sleeping" <<< "$OUTPUT"
grep -q "Sleeping -> Listening" <<< "$OUTPUT"

# Check invalid transition
grep -q "Sleeping -> Sleeping" <<< "$OUTPUT"
grep -q "\[RESULT\] Ignored" <<< "$OUTPUT"

# Check shutdown
grep -q "MIMO shutting down" <<< "$OUTPUT"

echo "Event loop integration test passed."