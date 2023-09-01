from pprint import pformat
from typing import List, Dict

from gen_common import CppFile, read_json_file


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

class InstrnDecodeFile(CppFile):

    patterns_by_instrn : Dict[str, Pattern]
    prefix_table: PrefixTable

    def read_all_specs(self, spec_files: List[str]):
        # spec_files: List[str] = glob("specs/*.json")

        self.patterns_by_instrn = {}
        spec_file: str
        for spec_file in spec_files:
            spec_json = read_json_file(spec_file)
            for func_name, func_spec in spec_json.items():
                self.patterns_by_instrn[func_name] = Pattern(func_spec["P"])


    def calc_prefix_table(self):

        self.prefix_table = PrefixTable()
        pattern: Pattern
        for instrn, pattern in self.patterns_by_instrn.items():
            self.prefix_table.add_prefix(instrn, pattern)

    def gen_switches(self):

        pat_by_len_tuples = sorted(
            self.prefix_table.by_len.items(), key=lambda x:x[0])

        for len, prefixes in pat_by_len_tuples:
            switch_expr: str = "instrn & %s" % prefixes.mask

            self.gen_switch_function(
                switch_expr=switch_expr, cases=list(prefixes.instrns.items()),
                brk_flag = True, def_val = None)
            self.gen_newline()

        def_val: str = "NOP"
        self.fprint("\treturn %s;" % def_val)

    def gen_func(self, spec_files: List[str]):
        self.gen_include_files(["instrn_enum.h", "../ops/decoder.h"])
        self.gen_func_header("InstrnEnum", "Decoder", "decode", [("ShortInstrn", "instrn"),])
        self.read_all_specs(spec_files)
        self.calc_prefix_table()
        self.gen_switches()
        self.fprint("}")

    def gen_file(self, spec_files: List[str], out_file: str):
        self.open_writer(out_file)
        self.gen_func(spec_files)
        self.close_writer()
