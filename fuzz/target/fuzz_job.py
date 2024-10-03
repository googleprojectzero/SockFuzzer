# Copyright 2024 Google LLC
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

# /usr/bin/env python3
import os
import subprocess


def fetch_environment_variables():
    pod_name = os.environ.get("POD_NAME", "fuzz-0")
    num_replicas = int(os.environ.get("NUM_REPLICAS", "1"))
    threads_per_replica = int(os.environ.get("THREADS_PER_REPLICA", "1"))
    return pod_name, num_replicas, threads_per_replica


def generate_command(pod_name, num_replicas, threads_per_replica):
    try:
        pod_index = int(pod_name.split("-")[-1]) * threads_per_replica
    except ValueError:
        raise ValueError(f"Pod name {pod_name} is in an unexpected format")
    total_shards = num_replicas * threads_per_replica

    cmd = [
        "/fuzz/target/centipede",
        "--binary=/fuzz/target/xnu_fuzzer_centipede",
        "--extra_binaries=/fuzz/target/xnu_fuzzer_asan_opt",
        "--workdir=/workdir",
        f"--total_shards={total_shards}",
        f"--first_shard_index={pod_index}",
        f"--num_threads={threads_per_replica}",
    ]
    return cmd


def main():
    pod_name, num_replicas, threads_per_replica = fetch_environment_variables()
    cmd = generate_command(pod_name, num_replicas, threads_per_replica)
    subprocess.run(cmd)


if __name__ == "__main__":
    main()
