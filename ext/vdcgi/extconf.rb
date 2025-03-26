# frozen_string_literal: true

require "mkmf"

# Makes all symbols private by default to avoid unintended conflict
# with other gems. To explicitly export symbols you can use RUBY_FUNC_EXPORTED
# selectively, or entirely remove this flag.
# append_cflags("-fvisibility=hidden")
require "fileutils"
extension_name = 'vdcgi'
v = " -std=c11 "
$defs.push(v)
$warnflags = "-Wall"
$libs += " -lmysqlclient -lcrypto -ljansson -lssl -lpthread  -lpthread -ldl -lcrypt -lm  -lc "

create_makefile("vdcgi/vdcgi")
