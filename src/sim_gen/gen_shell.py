import argparse
import logging
import os
from enum import Enum
from glob import glob
from pathlib import Path
from typing import List

from src.sim_gen.write_cmpl_cpp import CompilerCppFile
from write_wrpr_hdr import WrapperHdrFile
from write_wrpr_cpp import WrapperBodyFile
from write_impl_hdr import ImplHdrFile
from write_instrn_hdr import InstrnEnumsFile
from write_instrn_cpp import InstrnDecodeFile, InstrnExecFile
from src.sim_gen.write_compl_hdr import CompilerHdrFile

SRC_DIR = Path(__file__).resolve().parent

# File to be generated
class GenType(Enum):
    WHdr = 'w'
    WCpp = 'W'
    IHdr = 'i'

class Args(object):

    mod_name: str

    spec_dir: str
    out_dir: str

    all_specs: bool

    wrap_hdr: bool
    wrap_cpp: bool

    cmpl_hdr: bool
    cmpl_cpp: bool

    impl_hdr: bool

    instrn_map: bool

    def __init__(self, args):

        self.mod_name = args.mod_name

        self.spec_dir = args.spec_dir
        self.out_dir  = args.out_dir

        self.all_specs = args.all_specs

        self.wrap_hdr = args.wrap_hdr
        self.wrap_cpp = args.wrap_cpp

        self.cmpl_hdr = args.cmpl_hdr
        self.cmpl_cpp = args.cmpl_cpp

        self.impl_hdr = args.impl_hdr

        self.instrn_map = args.instrn_map

    def is_mod_spec(self)->bool:
        return (self.spec_dir or self.wrap_cpp or self.impl_hdr or self.all_specs)

    def adjust(self):
        if self.spec_dir is None:
            self.spec_dir = os.path.join(SRC_DIR, "specs")
        if self.out_dir is None:
            self.out_dir = os.path.join(SRC_DIR, "out")
        if self.all_specs or self.instrn_map:
            self.mod_name = '*'
        if not (self.wrap_cpp
                or self.wrap_hdr or self.impl_hdr
                or self.cmpl_cpp or self.cmpl_hdr
                or self.instrn_map
        ):
            self.wrap_hdr = self.wrap_cpp = self.impl_hdr = True
            self.cmpl_hdr = self.cmpl_cpp = True

    def spec_files(self)->List[str]:
        spec_file: str = os.path.join(self.spec_dir, "%s.json" % self.mod_name)
        return glob(spec_file)

    def out_module_file(self, mod_name: str, gen_type: str)->str:
        PATTERN = {
            'w': "%s.h", 'W': "%s.cpp", 'i': "%s_impl.h",
            'c' : '%s_cmpl.h', 'C': '%s_cmpl.cpp'
        }

        return os.path.join(SRC_DIR, self.out_dir, PATTERN[gen_type] % mod_name)

    def out_map_file(self, gen_type: str)->str:
        PATTERN = {'I': "instrns.h", 'D': "instrns.cpp", 'E': "all_ops.cpp"}
        return os.path.join(SRC_DIR, self.out_dir, PATTERN[gen_type])

def parseargs()->Args:
    parser = argparse.ArgumentParser()

    parser.add_argument('-m', '--mod_name', type=str,
        help='Module name')

    parser.add_argument('-a', '--all_specs',
        help='All specifications', action='store_true')

    parser.add_argument('-o', '--out_dir',
        help='Output directory')

    parser.add_argument('-s', '--spec_dir',
        help='Specification directory')

    parser.add_argument('-w', '--wrap_hdr', action='store_true',
        help='Generate wrapper header only')

    parser.add_argument('-W', '--wrap_cpp', action='store_true',
        help='Generate wrapper c++ code only')

    parser.add_argument('-i', '--impl_hdr', action='store_true',
        help='Generate implementation c++ code only')

    parser.add_argument('-I', '--instrn_map', action='store_true',
        help='Generate instruction map')

    parser.add_argument('-c', '--cmpl_hdr', action='store_true',
                        help='Generate compiler header only')

    parser.add_argument('-C', '--cmpl_cpp', action='store_true',
                        help='Generate compiler c++ code only')

    args = parser.parse_args()
    return Args(args)

def do_mod_specs(spec_files: List[str], args: Args):
    spec_file: str
    for spec_file in spec_files:
        mod_name = (args.mod_name if args.mod_name != '*'
                    else os.path.splitext(os.path.basename(spec_file))[0] )

        if args.wrap_hdr:
            WrapperHdrFile().gen_file(mod_name, spec_file, args.out_module_file(mod_name, 'w'))
        if args.wrap_cpp:
            WrapperBodyFile().gen_file(mod_name, spec_file, args.out_module_file(mod_name, 'W'))
        if args.impl_hdr:
            ImplHdrFile().gen_file(mod_name, spec_file, args.out_module_file(mod_name, 'i'))
        if args.cmpl_hdr:
            CompilerHdrFile().gen_file(mod_name, spec_file, args.out_module_file(mod_name, 'c'))
        if args.cmpl_cpp:
            CompilerCppFile().gen_file(mod_name, spec_file, args.out_module_file(mod_name, 'C'))

def exec(args: Args):

    spec_files: List[str] = args.spec_files()
    if not(args.instrn_map) and not len(spec_files):
        return

    out_dir: str = os.path.join(SRC_DIR, args.out_dir)
    if not os.path.exists(out_dir):
        os.mkdir(out_dir)

    if args.is_mod_spec():
        do_mod_specs(spec_files, args)

    if args.instrn_map:
        InstrnEnumsFile().gen_file(spec_files, args.out_map_file('I'))
        InstrnDecodeFile().gen_file(spec_files, args.out_map_file('D'))
        InstrnExecFile().gen_file(spec_files, args.out_map_file('E'))

if __name__ == "__main__":
    logging.basicConfig(level=logging.INFO)
    args: Args = parseargs()
    args.adjust()
    exec(args)