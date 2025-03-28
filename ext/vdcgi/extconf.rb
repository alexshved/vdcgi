# frozen_string_literal: true

require "mkmf"

# Makes all symbols private by default to avoid unintended conflict
# with other gems. To explicitly export symbols you can use RUBY_FUNC_EXPORTED
# selectively, or entirely remove this flag.

  if !have_library("libruby")
    `yes | apt -y install libruby`
  end    
  if !find_executable("mysql")
    abort("Please install mysql")
  end
  if  !find_executable("libmysqlclient21","/usr/lib/x86_64-linux-gnu/")
    `yes | apt -y install libmysqlclient21`
  end
  if  !find_executable("ruby-dev")
    `yes | apt -y install ruby-dev`
  end
  if  !find_executable("pkg-config")
    `yes | apt -y install pkg-config`
  end
  if !have_library("pthread")
    `yes | apt -y install libpthread-stubs0-dev`
  end
  if !have_library("libjansson-dev")
    `yes | apt -y install libjansson-dev`
  end
  if ! have_library("crypto")
    `yes | apt -y install libhcrypto4-heimdal`
  end
  if ! have_library("libmysqlclient-dev")
    `yes | apt -y install libmysqlclient-dev`
  end


append_cflags("-fvisibility=hidden")
extension_name = 'vdcgi'
v = " -std=c17 "
$defs.push(v)
$warnflags = "-Wall"
$libs += " -lmysqlclient -lcrypto -ljansson -lssl -lpthread  -lpthread -ldl -lcrypt -lm  -lc "

create_makefile("vdcgi/vdcgi")
