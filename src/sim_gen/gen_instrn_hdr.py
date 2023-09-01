import os.path
from typing import List, Dict

from gen_common import HeaderFile, read_json_file, camel_case


class InstrnEnumsFile(HeaderFile):

    def write_enums_for_spec(self, mod_spec: Dict[str, Dict[str, str]]):
        func_name: str
        for func_name in mod_spec.keys():
            self.fprint("\t%s," % func_name)

    def write_enums_for_spec_file(self, spec_file: str):
        json_spec: Dict[str, Dict[str, str]] = read_json_file(spec_file)
        mod_name: str = os.path.splitext(os.path.basename(spec_file))[0]
        self.fprint("\t// %s" % camel_case(mod_name))
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
        self.write_func_header("uchar_t", "instrn_size2", [("InstrnEnum", "instrn_enum"),])
        self.blankline()

    def gen_file(self, spec_files: List[str], out_file: str):
        self.open_writer(out_file)

        mod_name: str = "instrn_enum"
        enum_name: str = camel_case(mod_name)

        self.write_file_header(mod_name)

        self.gen_enum(enum_name, spec_files)
        self.write_decode_header()
        self.write_instrn_size_header()

        self.write_file_trailer(mod_name)
