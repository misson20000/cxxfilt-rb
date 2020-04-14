# coding: utf-8
lib = File.expand_path("../lib", __FILE__)
$LOAD_PATH.unshift(lib) unless $LOAD_PATH.include?(lib)
require "cxxfilt/version"

Gem::Specification.new do |spec|
  spec.name          = "cxxfilt"
  spec.version       = CXXFilt::VERSION
  spec.authors       = ["misson20000"]
  spec.email         = ["xenotoad@xenotoad.net"]
  spec.licenses      = ["LGPL-2.1-or-later"]

  spec.summary       = "Demangle C++ symbols"
  spec.homepage      = "https://github.com/misson20000/cxxfilt-rb"

  spec.files         = `git ls-files -z`.split("\x0").reject do |f|
    f.match(%r{^(test|spec|features)/})
  end
  spec.bindir        = "exe"
  spec.executables   = spec.files.grep(%r{^exe/}) { |f| File.basename(f) }
  spec.require_paths = ["lib", "ext"]
  spec.extensions    = ["ext/cxxfilt/extconf.rb"]
  
  spec.add_development_dependency "bundler", "~> 2.1"
  spec.add_development_dependency "rake", "~> 13.0"
  spec.add_development_dependency "rake-compiler"
  spec.add_development_dependency "pry"
  spec.add_development_dependency "rspec", "~> 3.0"
end
