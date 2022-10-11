import os

source_dir = "src"

ignore_files = []
ignore_dirs = []


def reformat_license_header(raw):
    new = ["/*"]
    new.extend(" * " + line.rstrip() if line.strip() else " *" for line in raw)
    new.extend([" */", ""])
    return new


header_f = open("license_header.txt", "r")
license_header = reformat_license_header(header_f.readlines())
header_f.close()

for path, dirs, files in os.walk(source_dir):
    if path.replace(os.sep, "/") in ignore_dirs:
        continue
    for fpath in files:
        fpath = os.path.join(path, fpath)
        if fpath.replace(os.sep, "/") in ignore_files:
            continue
        with open(fpath, "r") as fp:
            header = []
            for line in fp:
                header.append(line.rstrip())
                if len(header) == len(license_header):
                    break
            if not header == license_header:
                raise Exception("License check failed: " + fpath)
