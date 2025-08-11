#!/usr/bin/env python

import os, sys, argparse
import tempfile
import shutil
import c2kratos.main
import kratos
import subprocess
import time

_common_mc_opts = "-stage=mc -inline_max_depth_add_check=true -propagate_constants=maps -remove_const_maps=true -apply_slicing=true"

configs = {
    "bmc": _common_mc_opts + " -model_checking_engine=bmc",
    "msatic3": _common_mc_opts
    + " -model_checking_engine=msatic3 -model_checking_invert_ts=true",
    "symexec": "-stage=symexec -error_id=reach_error -symexec_iterative=true -symexec_max_depth=0",
    "bitprophic3": _common_mc_opts + " -model_checking_engine=btoric3abs",
}

# format is: (name, time limit in seconds)
configorder = [
    ("symexec", 240),
    ("msatic3", 450),
    ("bitprophic3", 600),
    ("bmc", -1),
    # run symex again if other engines fail due to unsupported recursion
    ("symexec", -1),
    # Skipped configurations...
    ("msatic3", -1),
    ("bitprophic3", -1),
]


spec = "CHECK( init(main()), LTL(G ! call(reach_error())) )"


def c_to_k2(opts, tempdir):
    specfile = os.path.join(tempdir, "spec.prp")
    with open(specfile, "w") as out:
        out.write(spec)
    filename = os.path.join(tempdir, "program.k2")
    inputfile = opts.inputfile

    if opts.prefer_unprocessed:
        benchname, ext = os.path.splitext(inputfile)
        unprocessed = benchname + ".c"
        path, benchmark = os.path.split(unprocessed)
        path, family = os.path.split(path)
        if ext == ".i" and os.path.exists(unprocessed):
            print("Preferring unprocessed", unprocessed, file=sys.stderr)
            inputfile = unprocessed

    frontend_opts = ["--svcomp-spec", specfile, "--output", filename, inputfile]
    c2kratos.main.main(c2kratos.main.getopts(frontend_opts))
    return filename


def getopts():
    p = argparse.ArgumentParser()
    p.add_argument("inputfile")
    p.add_argument("--dump-k2")
    p.add_argument("--cex", action="store_true")
    p.add_argument("--translate-only", action="store_true")
    p.add_argument("--prefer-unprocessed", action="store_true")
    p.add_argument("--single-config")
    return p.parse_args()


def main():
    global configorder
    sys.setrecursionlimit(20000)
    start = time.time()
    d = tempfile.mkdtemp()
    try:
        opts = getopts()
        print("-" * 77)
        print("translating input C program to k2")
        print("-" * 77)
        cstart = time.time()
        try:
            filename = c_to_k2(opts, d)
        except Exception as e:
            print("c2kratos exception: %s" % e)
            print("result = unknown")
            return
        cend = time.time()
        print("translation_time = %.3f" % (cend - cstart))
        if opts.dump_k2:
            shutil.copyfile(filename, opts.dump_k2)
        if opts.translate_only:
            return
        if opts.single_config is not None:
            configorder = [(opts.single_config, -1)]
        for name, timelimit in configorder:
            try:
                print("-" * 77)
                print(f"running kratos with configuration: {name}")
                config = configs[name]
                print(f"options: {config}")
                print("-" * 77)
                cex = "" if not opts.cex else "-cex_type=patheval"
                cmd = f"{kratos.get_kratos_executable()} {config} {cex} {filename}"
                if timelimit > 0:
                    cmd = f"ulimit -t {timelimit}; {cmd}"
                res = subprocess.run(cmd, shell=True, encoding="utf-8")
                if res.returncode in (10, 20):
                    end = time.time()
                    print("-" * 77)
                    print(f"solution found by {name}")
                    print("-" * 77)
                    print("time = %.3f" % (end - start))
                    print("result = %s" % ("safe" if res.returncode == 10 else "unsafe"))
                    break
            except KeyboardInterrupt:
                print("\nSkipping to the next execution configuration...")
                continue
    finally:
        shutil.rmtree(d)


if __name__ == "__main__":
    main()
