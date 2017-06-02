require "bundler/gem_tasks"
require "rspec/core/rake_task"
require "rake/extensiontask"

RSpec::Core::RakeTask.new(:spec)

task :default => :spec

spec = Gem::Specification.load("cxxfilt.gemspec")
Rake::ExtensionTask.new("cxxfilt", spec)
