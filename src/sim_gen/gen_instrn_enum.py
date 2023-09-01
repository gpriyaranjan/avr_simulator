from typing import List, Dict

from gen_common import HeaderFile, read_json_file


class InstrEnumFile(HeaderFile):

    def gen_enums_for_spec(self, mod_spec: Dict[str, Dict[str, str]]):
        func_name: str
        for func_name in mod_spec.keys():
            self.fprint("%s," % func_name)

    def gen_enums_for_spec_file(self, spec_file: str):
        json_spec: Dict[str, Dict[str, str]] = read_json_file(spec_file)
        self.gen_enums_for_spec(json_spec)

    def gen_enums_for_spec_files(self, spec_files: List[str]):
        spec_file: str
        for spec_file in spec_files:
            self.gen_enums_for_spec_file(spec_file)
            self.gen_newline()

    def gen_file(self, spec_files: List[str], out_file: str):
        self.open_writer(out_file)
        enum_name: str = "InstrnEnum"

        self.gen_enum_prefix(enum_name)
        self.gen_enums_for_spec_files(spec_files)
        self.gen_enum_suffix()

