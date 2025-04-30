require "mkmf"

extension_name = "cxxfilt"
dir_config(extension_name)
append_cflags("-DHAVE_STDLIB_H -DHAVE_STRING_H -DHAVE_ALLOCA_H -DHAVE_LIMITS_H")
create_makefile extension_name
