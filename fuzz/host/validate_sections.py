#!/usr/bin/env python3
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

import sys
from elftools.elf.elffile import ELFFile

def get_section_names(binary_path):
    with open(binary_path, 'rb') as f:
        elf = ELFFile(f)
        return [section.name for section in elf.iter_sections()]

def validate_section_name(name):
    return ',' not in name and ' ' not in name and '"' not in name

def main(binary_path):
    section_names = get_section_names(binary_path)
    invalid_sections = [name for name in section_names if not validate_section_name(name)]
    
    if invalid_sections:
        print("Error: Invalid section names found:")
        for name in invalid_sections:
            print(f"  - {name}")
        return 1
    else:
        print("All section names are valid.")
        return 0

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage: python validate_sections.py <path_to_binary>")
        sys.exit(1)
    sys.exit(main(sys.argv[1]))