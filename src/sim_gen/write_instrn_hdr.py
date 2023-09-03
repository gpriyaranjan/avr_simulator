import os.path
from typing import List, Dict

from gen_common import HeaderFile, SpecCommon, camel_case, FuncSpec, SpecCommon


class InstrnEnumsFile(HeaderFile):

    func_specs: Dict[str, FuncSpec]
    funcs_by_mod: Dict[str, List[str]]

    def __init__(self):
        self.func_specs = {}
        self.funcs_by_mod = {}

    def write_enums_struct(self, enum_name: str):
        mod_name: str
        self.fprintln("enum %s {" % camel_case(enum_name))
        for mod_name in self.funcs_by_mod.keys():
            self.fprintln(f"\t// {camel_case(mod_name)}")
            for func_name in self.funcs_by_mod[mod_name]:
                self.fprintln(f"\t{func_name},")
            self.fprintln()
        self.fprintln("};")

    def write_func_masks(self, msk_cls_name: str):
        mod_name: str
        self.fprintln("namespace %s {" % camel_case(msk_cls_name))
        for mod_name in self.funcs_by_mod.keys():
            self.fprintln("\t// {camel_case(mod_name)}")
            func_spec: FuncSpec
            for func_name in self.funcs_by_mod[mod_name]:
                func_spec: FuncSpec = self.func_specs[func_name]
                if func_spec.man_dcd: continue
                func_hex: str = func_spec.pattern.instrn_mask_hex
                self.fprintln(f"\tconstexpr {func_name} = {func_hex};")
            self.fprintln()
        self.fprintln("};")
        self.fprintln()

    def read_all_json_files(self, spec_files: List[str]):
        for spec_file in spec_files:
            mod_name: str = SpecCommon.mod_name(spec_file)
            json_spec: Dict[str, Dict[str,str]] = SpecCommon.read_json_file(spec_file)
            for func_name, json_func in json_spec.items():
                self.func_specs[func_name] = FuncSpec(json_func, mod_name)
                self.funcs_by_mod[mod_name] = self.funcs_by_mod.get(mod_name, [])
                self.funcs_by_mod[mod_name].append(func_name)

    def write_decode_hdr_line(self):
        self.write_func_header("InstrnEnum", "decode", [("ShortInstrn", "instrn"),])
        self.blankline()

    def write_instrn_size_hdr_line(self):
        self.write_func_header("uchar_t", "instrn_size", [("InstrnEnum", "instrn_enum"),])
        self.blankline()

    def write_files(self, out_file: str):
        self.open_writer(out_file)

        mod_name: str = "instrns"
        self.write_file_header(mod_name)
        self.write_include_files(["../infra/types.h"])

        enum_name: str = camel_case("instrn_enum")
        self.write_enums_struct(enum_name)

        msk_cls_name: str = camel_case("instrn_mask")
        self.write_func_masks(msk_cls_name)

        self.write_decode_hdr_line()
        self.write_instrn_size_hdr_line()

        self.write_file_trailer(mod_name)

    def gen_file(self, spec_files: List[str], out_file: str):
        self.read_all_json_files(spec_files)
        self.write_files(out_file)
