from collections import OrderedDict
from glob import glob
from pprint import pprint, pformat
from typing import List, Dict

from gen_common import read_json_file

INSTRN_SIZE = 16

def extract_prefix(pattern:str)->str:
    prefix: str = ""
    for ch in pattern:
        if ch not in ['0','1']: break
        prefix = prefix + ch
    return prefix

class Pattern(object):

    readable: str
    pattern: str

    prefix: str
    pfx_hex: str
    pfx_msk: str
    pfx_len: int

    def __init__(self, pattern:str):
        self.readable = pattern
        self.pattern = self.readable.replace("-", "")

        self.prefix = extract_prefix(self.pattern)
        self.set_prefix_flags()

    def set_prefix_flags(self):

        self.pfx_len = len(self.prefix)

        pfx_len: int = len(self.prefix)
        pfx_bin: str = self.prefix + "0"*(INSTRN_SIZE-pfx_len)
        self.pfx_hex = hex(int(pfx_bin,2))
        msk_bin: str = "1"*pfx_len + "0"*(INSTRN_SIZE-pfx_len)
        self.pfx_msk = hex(int(msk_bin,2))

    def __repr__(self):
        return ("PL(%s),P(%s),PH(%s),PM(%s)" %
                (self.pfx_len, self.prefix, self.pfx_hex, self.pfx_msk))

def read_all_specs()->Dict[str,Pattern]:
    name_patterns = OrderedDict()
    spec_files: List[str] = glob("specs/*.json")
    spec_file: str
    for spec_file in spec_files:
        spec_json = read_json_file(spec_file)
        for func_name, func_spec in spec_json.items():
            name_patterns[func_name] = Pattern(func_spec["P"])
    return name_patterns

Hex = str
class Prefixes(object):
    len: int
    mask: str
    instrns: Dict[Hex,str]

    def __init__(self, len:int, mask:str):
        self.len = len
        self.mask = mask
        self.instrns = {}

    def set(self, hex:Hex, instrn:str):
        self.instrns[hex] = instrn

    def __repr__(self):
        instrns = ["<%s,%s>" % (mask, instrn)
            for (mask, instrn) in self.instrns.items()]
        instrns = sorted(instrns)
        return "(%s)" % (",".join(instrns))

class PrefixTable(object):
    by_len: Dict[int,Prefixes]

    def __init__(self):
        self.by_len = {}

    def add_prefix(self, instrn:str, pattern: Pattern):
        len: int = pattern.pfx_len
        prefixes: Prefixes = self.by_len.get(len, Prefixes(len, pattern.pfx_msk))
        prefixes.set(pattern.pfx_hex, instrn)
        self.by_len[len] = prefixes

    def __repr__(self):
        return pformat(self.by_len)

def to_prefix_table(
        ptrns_by_name: Dict[str,Pattern])->PrefixTable:

    prefix_table: PrefixTable = PrefixTable()
    pattern: Pattern
    for instrn, pattern in ptrns_by_name.items():
        prefix_table.add_prefix(instrn, pattern)
    return prefix_table

def gen_code(prefix_table: PrefixTable):

    len_tuples = sorted(
        prefix_table.by_len.items(), key=lambda x:x[0])
    for len, prefixes in len_tuples:
        print("\tswitch(instrn & %s) {" % prefixes.mask)
        for pfx_hex, instrn in prefixes.instrns.items():
            print("\t\tcase %s: return %s;" % (pfx_hex, instrn) )
        print("\t\tdefault: break;")
        print("\t};")
        print()

if __name__ == "__main__":
    ptrns_by_name: Dict[str,Pattern] = read_all_specs()
    # pprint(dict(ptrns_by_name))
    # print()

    prefix_table: PrefixTable = to_prefix_table(ptrns_by_name)
    pprint(prefix_table.by_len)
    print()

    gen_code(prefix_table)
