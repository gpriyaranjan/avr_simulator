import os.path
from typing import List, Dict, Tuple, Set

from gen_common import CppFile, read_json_file, camel_case
from pattern import Pattern, PrefixTable

class InstrnDecodeFile(CppFile):

    patterns_by_instrn : Dict[str, Pattern]
    prefix_table: PrefixTable


    def read_all_specs(self, spec_files: List[str]):

        self.patterns_by_instrn = {}

        spec_file: str
        for spec_file in spec_files:
            spec_json = read_json_file(spec_file)
            mod_name:str = os.path.splitext(os.path.basename(spec_file))[0]
            for func_name, func_spec in spec_json.items():
                self.patterns_by_instrn[func_name] = Pattern(func_spec["P"])


    def calc_prefix_table(self):

        self.prefix_table = PrefixTable()
        pattern: Pattern
        for instrn, pattern in self.patterns_by_instrn.items():
            self.prefix_table.add_prefix(instrn, pattern)



    def write_all_includes(self):
        self.write_include_files(["instrns.h", "../infra/types.h"])


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
        self.write_func_body_hdr("InstrnEnum", "", "decode", [("ShortInstrn", "instrn"), ])
        self.write_switches()
        self.fprint("}")
        self.blankline()


    def write_sizes_func(self):
        def size(pattern: Pattern):
            return str(2) if len(pattern.compact) <= 16 else str(3)

        cases: List[Tuple[str, str]] = [
            (instrn, size(pattern)) for (instrn, pattern) in self.patterns_by_instrn.items()]

        self.write_func_body_hdr("uchar_t", "", "instrn_size", [("InstrnEnum", "instrn_enum"), ])
        self.write_switch_func("instrn_enum", cases, True, False, "0")
        self.fprint("}")
        self.blankline()


    def gen_file(self, spec_files: List[str], out_file: str):
        self.gen_func(spec_files)

        self.open_writer(out_file)
        self.write_all_includes()
        self.write_decode_func()
        self.write_sizes_func()
        self.close_writer()


class InstrnExecFile(CppFile):

    modules_by_instrn: Dict[str, str]

    def __init__(self):
        self.modules_by_instrn = {}

    def read_all_specs(self, spec_files: List[str]):
        spec_file: str
        for spec_file in spec_files:
            spec_json = read_json_file(spec_file)
            mod_name:str = os.path.splitext(os.path.basename(spec_file))[0]
            for func_name, func_spec in spec_json.items():
                self.modules_by_instrn[func_name] = mod_name

    def write_exec_includes(self):
        self.write_include_files(["instrns.h"])
        modules: Set[str] = set(self.modules_by_instrn.values())
        mod_files: List[str] = ["%s.h" % module for module in modules]
        self.write_include_files(list(mod_files))


    def write_exec_func(self):
        # To do - Need to split between short instrns and long instrns
        self.write_func_body_hdr(
            "void", "", "exec_instrn",
            [("Environ&", "env"), ("LongInstrn", "instrn")])

        self.fprint("\tInstrnEnum instrn_enum = decode(instrn);")
        cases: List[Tuple[str,str]] = [
            (instr_name, "%s::%s(env, instrn)" %(camel_case(mod_name), instr_name))
            for (instr_name, mod_name) in self.modules_by_instrn.items()]

        self.write_switch_func("instrn_enum", cases, False, True, "")
        self.fprint("};")


    def gen_file(self, spec_files: List[str], out_file: str):
        self.read_all_specs(spec_files)

        self.open_writer(out_file)
        self.write_exec_includes()
        self.write_exec_func()
        self.close_writer()