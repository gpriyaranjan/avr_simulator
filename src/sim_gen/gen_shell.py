import argparse
import os
from enum import Enum
from pathlib import Path

from gen_wrpr_hdr import WrapperHdrFile
from gen_wrpr_body import WrapperBodyFile
from src.sim_gen.gen_impl_hdr import ImplHdrFile

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

    def __init__(self, args):
        self.mod_name = args.mod_name
        self.spec_dir = args.spec_dir
        self.out_dir  = args.out_dir

    def validate(self):
        if self.spec_dir is None:
            self.spec_dir = os.path.join(SRC_DIR, "specs")
        if self.out_dir is None:
            self.out_dir = os.path.join(SRC_DIR, "out")

    def spec_file(self)->str:
        return os.path.join(self.spec_dir, "%s.json" % self.mod_name)

    def out_file(self, gen_type: str)->str:
        PATTERN = {'w': "%s.h", 'W': "%s.cpp", 'i': "%s_impl.h"}
        return os.path.join(self.out_dir, PATTERN[gen_type] % self.mod_name)


def parseargs()->Args:
    parser = argparse.ArgumentParser()
    parser.add_argument('-m', '--mod_name', help='Module name', required=True)
    parser.add_argument('-o', '--out_dir', help='Output directory')
    parser.add_argument('-s', '--spec_dir', help='Specification directory')
    args = parser.parse_args()
    return Args(args)

def exec(args: Args):

    spec_file: str = args.spec_file()
    WrapperHdrFile().gen_file(args.mod_name, spec_file, args.out_file('w'))
    WrapperBodyFile().gen_file(args.mod_name, spec_file, args.out_file('W'))
    ImplHdrFile().gen_file(args.mod_name, spec_file, args.out_file('i'))


if __name__ == "__main__":
    args: Args = parseargs()
    args.validate()
    exec(args)