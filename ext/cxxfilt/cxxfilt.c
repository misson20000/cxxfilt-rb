#include<ruby.h>

#include "demangle.h"

static VALUE c_Demangler = Qnil;
static VALUE v_auto_demangler = Qnil;

static VALUE cxxfilt_demangle(int argc, VALUE *argv, VALUE self) {
  VALUE v_mangled_name;
  VALUE v_mangling_style;
  rb_scan_args(argc, argv, "11", &v_mangled_name, &v_mangling_style);

  enum demangling_styles style = auto_demangling;
  if(!NIL_P(v_mangling_style)) {
    style = cplus_demangle_name_to_style(StringValueCStr(v_mangling_style));
  }

  if(style == unknown_demangling) {
    rb_raise(rb_eRuntimeError, "no such demangling style '%s' was found", StringValueCStr(v_mangling_style)); // TODO: make an actual exception class to raise here
  }

  cplus_demangle_set_style(style);
  char *result;
  result = cplus_demangle(StringValueCStr(v_mangled_name), DMGL_PARAMS | DMGL_ANSI | DMGL_VERBOSE);
  if(result == NULL) {
    return Qnil;
  }
  VALUE v_result = rb_str_new_cstr(result);
  free(result);
  return v_result;
}

static VALUE cxxfilt_demangle_m_demangle(VALUE self, VALUE name) {
  const struct demangler_engine *demangler;
  Data_Get_Struct(self, const struct demangler_engine, demangler);

  cplus_demangle_set_style(demangler->demangling_style);
  char *result;
  result = cplus_demangle(StringValueCStr(name), DMGL_PARAMS | DMGL_ANSI | DMGL_VERBOSE);
  if(result == NULL) {
    return Qnil;
  }
  VALUE v_result = rb_str_new_cstr(result);
  free(result);
  return v_result;
}

static VALUE cxxfilt_get_auto(VALUE self) {
  return v_auto_demangler;
}

void Init_cxxfilt() {
  VALUE mCXXFilt = rb_define_module("CXXFilt");
  c_Demangler = rb_define_class_under(mCXXFilt, "Demangler", rb_cObject);
  rb_define_module_function(mCXXFilt, "demangle", cxxfilt_demangle, -1);
  //rb_define_module_function(mCXXFilt, "demanglers", cxxfilt_demanglers, 0);
  rb_define_module_function(mCXXFilt, "auto", cxxfilt_get_auto, 0);
  rb_define_method(c_Demangler, "demangle", cxxfilt_demangle_m_demangle, 1);

  static VALUE v_demanglers = Qnil;
  v_demanglers = rb_ary_new();
  for(const struct demangler_engine *demangler = libiberty_demanglers; demangler->demangling_style != unknown_demangling; demangler++) {
    VALUE v_demangler = Data_Wrap_Struct(c_Demangler, 0, 0, demangler);
    if(demangler->demangling_style == auto_demangling) {
      v_auto_demangler = v_demangler;
    }
    rb_ary_push(v_demanglers, v_demangler);
    rb_iv_set(v_demangler, "@name", rb_str_new_cstr(demangler->demangling_style_name));
    rb_iv_set(v_demangler, "@doc", rb_str_new_cstr(demangler->demangling_style_doc));
  }
  rb_iv_set(mCXXFilt, "@demanglers", v_demanglers);
  
  rb_require("cxxfilt/cxxfilt");
}
