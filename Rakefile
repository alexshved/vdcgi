# frozen_string_literal: true

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

namespace :vendor do
  task :build do
    system "cd ext/jansson && rake build"
  end
  
  task :clean do
    system "cd ext/jansson && rake clean"
  end
end
task vendor: "vendor:build"
task default: %i["vendor:build" clobber compile test rubocop]
