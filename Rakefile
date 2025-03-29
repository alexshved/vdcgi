# frozen_string_literal: true
require 'rake/clean'
require 'ffi'
require "bundler/gem_tasks"
require "minitest/test_task"

Minitest::TestTask.create

require "rubocop/rake_task"

RuboCop::RakeTask.new

require "rake/extensiontask"

task build: :compile


GEMSPEC = Gem::Specification.load("vdcgi.gemspec")

Rake::ExtensionTask.new("vdcgi", GEMSPEC) do |ext|
  ext.lib_dir = "lib/vdcgi"
end
FILES = {}

task :defaultj => :clobber

def self.file_task(filename, opts, &block)
  name, dep = opts.is_a?(Hash) ? opts.to_a.first : [opts, nil]
  
  FILES[name] = filename
  CLEAN.include filename
  task name => filename
  
  if dep
    file filename => FILES[dep], &block
  else
    file filename, &block
  end
end

def cmd(string)
  fail "Command failed: #{string}" unless system(string)
end

file_task 'jansson.tar.gz', :download_tarball do
  version = "2.14"
  release = "https://github.com/akheron/jansson/archive/v#{version}.tar.gz"
  cmd "wget #{release}"
  cmd "mv #{File.basename(release)} #{FILES[:download_tarball]}"
end

file_task 'jansson', :download => :download_tarball do
  cmd "tar -xf #{FILES[:download_tarball]}"
  cmd "mv jansson-* #{FILES[:download]}"
end
file_task 'config.status', :configure => :download do
  cmd "bash -c 'cd #{FILES[:download]} && autoreconf -fi && ./configure'"
  cmd "cp #{FILES[:download]}/#{FILES[:configure]} ./"
end
file_task "libjansson.#{::FFI::Platform::LIBSUFFIX}", :defaultj => :configure do
  cmd "bash -c 'cd #{FILES[:download]} && make'"
  puts "______cp file___________#{FILES[:download]}/src/.libs/#{FILES[:defaultj]}________________________"
  cmd "cp #{FILES[:download]}/src/.libs/#{FILES[:defaultj]} ."
end

task default: %i[defaultj compile test rubocop]
