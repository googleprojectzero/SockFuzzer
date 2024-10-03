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

"""
Helpers for header inclusion in XNU
"""

def get_headers(includes):
    result = []
    unique_includes = {folder: True for folder in includes}

    for folder in unique_includes:
        if folder == ".":
            continue

        # Split the folder by "/" and check if any prefix is in the unique_includes set
        folder_parts = folder.split("/")
        should_skip = False

        for i in range(1, len(folder_parts)):
            prefix = "/".join(folder_parts[:i])
            if prefix in unique_includes:
                should_skip = True
                break

        if not should_skip:
            headers = native.glob([folder + "/**/*.h"])
            result.extend(headers)

    return result
