require "mkmf"

extension_name = "cxxfilt"
dir_config(extension_name)
have_library("iberty")
create_makefile extension_name
