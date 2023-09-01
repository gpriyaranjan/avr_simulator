import os.path
from pprint import pformat
from typing import List, Dict, Tuple

from gen_common import CppFile, read_json_file, camel_case

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
    modules_by_instrn: Dict[str, str]
    prefix_table: PrefixTable

    def read_all_specs(self, spec_files: List[str]):
        # spec_files: List[str] = glob("specs/*.json")

        self.patterns_by_instrn = {}
        self.modules_by_instrn = {}

        spec_file: str
        for spec_file in spec_files:
            spec_json = read_json_file(spec_file)
            mod_name:str = os.path.splitext(os.path.basename(spec_file))[0]
            for func_name, func_spec in spec_json.items():
                self.patterns_by_instrn[func_name] = Pattern(func_spec["P"])
                self.modules_by_instrn[func_name] = mod_name


    def calc_prefix_table(self):

        self.prefix_table = PrefixTable()
        pattern: Pattern
        for instrn, pattern in self.patterns_by_instrn.items():
            self.prefix_table.add_prefix(instrn, pattern)

    def write_switches(self):

        pat_by_len_tuples = sorted(
            self.prefix_table.by_len.items(), key=lambda x:x[0])

        for len, prefixes in pat_by_len_tuples:
            switch_expr: str = "instrn & %s" % prefixes.mask

            self.write_switch_func(
                switch_expr, list(prefixes.instrns.items()),
                True, True, def_val = None)
            self.blankline()

        def_val: str = "NOP"
        self.fprint("\treturn %s;" % def_val)


    def gen_func(self, spec_files: List[str]):
        self.read_all_specs(spec_files)
        self.calc_prefix_table()


    def write_decode_func(self):
        self.write_func_header("InstrnEnum", "", "decode", [("ShortInstrn", "instrn"), ])
        self.write_switches()
        self.fprint("}")
        self.blankline()


    def write_sizes_func(self):
        def size(pattern: Pattern):
            return str(2) if len(pattern.pattern) <= 16 else str(3)

        cases: List[Tuple[str, str]] = [
            (instrn, size(pattern)) for (instrn, pattern) in self.patterns_by_instrn.items()]

        self.write_func_header("uchar_t", "", "instrn_size", [("InstrnEnum", "instrn_enum"), ])
        self.write_switch_func("instrn_enum", cases, True, False, 0)
        self.fprint("}")
        self.blankline()


    def write_exec_func(self):
        # To do - Need to split between short instrns and long instrns
        self.write_func_header("void", "", "exec_instrn", [("LongInstrn", "instrn")])
        cases: List[Tuple[str,str]] = [
                (instr_name, "%s::%s(instrn)" %(camel_case(mod_name), instr_name))
                for (instr_name, mod_name) in self.modules_by_instrn.items()]

        self.write_switch_func("instrn", cases, False, True, "")
        self.fprint("};")


    def gen_file(self, spec_files: List[str], out_file: str):
        self.gen_func(spec_files)

        self.open_writer(out_file)
        self.write_include_files(["instrns.h", "../infra/types.h"])
        self.write_decode_func()
        self.write_sizes_func()
        # self.write_exec_func()
        self.close_writer()
