import os

# Your mapping configuration
mappings = {
    "main": "ksvc_b28b.dat"
}

def generate_sys_file(output_path):
    with open(output_path, "wb") as f:
        for alias, filename in mappings.items():
            # Pad to 32 bytes each
            alias_bytes = alias.encode('utf-8').ljust(32, b'\0')
            file_bytes = filename.encode('utf-8').ljust(32, b'\0')
            f.write(alias_bytes + file_bytes)

generate_sys_file("examples/calculator/output/bin/kito.sys")