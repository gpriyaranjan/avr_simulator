import os.path
from typing import List, Dict

from gen_common import HeaderFile, read_json_file, camel_case, FuncSpec


class InstrnEnumsFile(HeaderFile):

    def write_enums_for_spec(self, mod_spec: Dict[str, Dict[str, str]]):
        func_name: str
        func_json: Dict[str, str]

        for func_name, func_json in mod_spec.items():
            func_spec: FuncSpec = FuncSpec(func_json)
            value: str = hex(int(func_spec.pattern.instrn_mask, 2))
            self.fprintln("\t%s = %s," % (func_name, value))

    def write_enums_for_spec_file(self, spec_file: str):
        json_spec: Dict[str, Dict[str, str]] = read_json_file(spec_file)
        mod_name: str = os.path.splitext(os.path.basename(spec_file))[0]
        self.fprintln("\t// %s" % camel_case(mod_name))
        self.write_enums_for_spec(json_spec)

    def write_enums_for_spec_files(self, spec_files: List[str]):
        spec_file: str
        for spec_file in spec_files:
            self.write_enums_for_spec_file(spec_file)
            self.blankline()

    def gen_enum(self, enum_name: str, spec_files: List[str]):
        self.write_enum_prefix(enum_name)
        self.write_enums_for_spec_files(spec_files)
        self.write_enum_suffix()
        self.blankline()

    def write_decode_header(self):
        self.write_func_header("InstrnEnum", "decode", [("ShortInstrn", "instrn"),])
        self.blankline()

    def write_instrn_size_header(self):
        self.write_func_header("uchar_t", "instrn_size", [("InstrnEnum", "instrn_enum"),])
        self.blankline()

    def gen_file(self, spec_files: List[str], out_file: str):
        self.open_writer(out_file)

        mod_name: str = "instrns"
        self.write_file_header(mod_name)

        self.write_include_files(["../infra/types.h"])

        enum_name: str = camel_case("instrn_enum")
        self.gen_enum(enum_name, spec_files)
        self.write_decode_header()
        self.write_instrn_size_header()

        self.write_file_trailer(mod_name)
