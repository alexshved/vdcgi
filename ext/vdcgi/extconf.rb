# frozen_string_literal: true

require "mkmf"

# Makes all symbols private by default to avoid unintended conflict
# with other gems. To explicitly export symbols you can use RUBY_FUNC_EXPORTED
# selectively, or entirely remove this flag.

  if !have_library("libruby")
     abort "-----\nA package libruby is required for installation libruby. Install libruby and try again\n-----"
  end    
  if !find_executable("mysql")
   abort "-----\nA package mysql is required for installation libruby. Install mysql and try again\n-----"
  end
  if  !find_executable("ruby-dev")
    abort "-----\nA package ruby-dev is required for installation libruby. Install ruby-dev and try again\n-----"
  end
#    if !have_library("pthread")
#     `yes | apt -y install libpthread-stubs0-dev`
#   end
  if !have_library("libjansson-dev")
     abort "-----\nA package libjansson-dev is required for installation libruby. Install libjansson-dev and try again\n-----"
  end
  if ! have_library("crypto")
    abort "-----\nA package crypto is required for installation libruby. Install crypto and try again\n-----"
  end
  if ! have_library("libmysqlclient-dev")
   abort "-----\nA package ibmysqlclient-dev is required for installation libruby. Install ibmysqlclient-dev and try again\n-----"
  end


append_cflags("-fvisibility=hidden")
extension_name = 'vdcgi'
v = " -std=c17 "
$defs.push(v)
$warnflags = "-Wall"
$libs += " -lmysqlclient -lcrypto -ljansson -lssl -lpthread  -lpthread -ldl -lcrypt -lm  -lc "

create_makefile("vdcgi/vdcgi")
