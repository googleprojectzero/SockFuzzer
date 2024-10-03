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

import os
import unittest
from unittest.mock import patch
from sockfuzzer.fuzz.target import fuzz_job

class FuzzJobTest(unittest.TestCase):

    @patch.dict(os.environ, {"POD_NAME": "fuzzer-3", "NUM_REPLICAS": "4", "THREADS_PER_REPLICA": "3"})
    def test_fetch_environment_variables(self):
        pod_name, num_replicas, threads_per_replica = fuzz_job.fetch_environment_variables()
        self.assertEqual(pod_name, "fuzzer-3")
        self.assertEqual(num_replicas, 4)
        self.assertEqual(threads_per_replica, 3)

    def test_generate_command(self):
        cmd = fuzz_job.generate_command("fuzzer-3", 4, 3)
        expected_cmd = [
            "/fuzz/target/centipede",
            "--binary=/fuzz/target/xnu_fuzzer_centipede",
            "--extra_binaries=/fuzz/target/xnu_fuzzer_asan_opt",
            "--workdir=/workdir",
            "--total_shards=12",
            "--first_shard_index=9",
            "--num_threads=3",
        ]
        self.assertEqual(cmd, expected_cmd)

    @patch('sockfuzzer.fuzz.target.fuzz_job.subprocess.run')
    @patch('sockfuzzer.fuzz.target.fuzz_job.generate_command')
    @patch('sockfuzzer.fuzz.target.fuzz_job.fetch_environment_variables')
    def test_main(self, mock_fetch_env, mock_generate_cmd, mock_run_cmd):
        mock_fetch_env.return_value = ("fuzzer-3", 2, 2)
        mock_generate_cmd.return_value = ["mock_cmd"]
        fuzz_job.main()
        mock_fetch_env.assert_called_once()
        mock_generate_cmd.assert_called_once_with("fuzzer-3", 2, 2)
        mock_run_cmd.assert_called_once_with(["mock_cmd"])


if __name__ == "__main__":
    unittest.main()
