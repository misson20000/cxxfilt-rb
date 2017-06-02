# CXXFilt

This is a Ruby gem for demangling C++ symbols. It works the same way as the `c++filt` program from GNU binutils does. It even links with `libiberty` and uses the same demangling routines as `c++filt`.

## Installation

Add this line to your application's Gemfile:

```ruby
gem 'cxxfilt'
```

And then execute:

    $ bundle

Or install it yourself as:

    $ gem install cxxfilt

## Usage

Get a list of the available demanglers:

```
2.4.1 :001 > require "cxxfilt"
 => true 
2.4.1 :002 > CXXFilt::demanglers
 => [
      #<CXXFilt::Demangler:0x00000000e3e720 @name="none", @doc="Demangling disabled">,
      #<CXXFilt::Demangler:0x00000000e3e658 @name="auto", @doc="Automatic selection based on executable">,
      #<CXXFilt::Demangler:0x00000000e3e5e0 @name="gnu", @doc="GNU (g++) style demangling">,
      #<CXXFilt::Demangler:0x00000000e3e568 @name="lucid", @doc="Lucid (lcc) style demangling">,
      #<CXXFilt::Demangler:0x00000000e3e4c8 @name="arm", @doc="ARM style demangling">,
      #<CXXFilt::Demangler:0x00000000e3e450 @name="hp", @doc="HP (aCC) style demangling">,
      #<CXXFilt::Demangler:0x00000000e3e3d8 @name="edg", @doc="EDG style demangling">,
      #<CXXFilt::Demangler:0x00000000e3e360 @name="gnu-v3", @doc="GNU (g++) V3 ABI-style demangling">,
      #<CXXFilt::Demangler:0x00000000e3e270 @name="java", @doc="Java style demangling">,
      #<CXXFilt::Demangler:0x00000000e3e180 @name="gnat", @doc="GNAT style demangling">,
      #<CXXFilt::Demangler:0x00000000e3e0e0 @name="dlang", @doc="DLANG style demangling">]
 ```

Demangle a symbol with the `auto` demangler:

```
2.4.1 :003 > CXXFilt::demangle("_Z1hic")
 => "h(int, char)" 
2.4.1 :004 > CXXFilt::auto.demangle("_Z1hic")
 => "h(int, char)" 
2.4.1 :005 > CXXFilt::demanglers[1].demangle("_Z1hic")
 => "h(int, char)" 
```

## Development

After checking out the repo, run `bin/setup` to install dependencies. Then, run `rake spec` to run the tests. You can also run `bin/console` for an interactive prompt that will allow you to experiment.

To install this gem onto your local machine, run `bundle exec rake install`. To release a new version, update the version number in `version.rb`, and then run `bundle exec rake release`, which will create a git tag for the version, push git commits and tags, and push the `.gem` file to [rubygems.org](https://rubygems.org).

## Contributing

Bug reports and pull requests are welcome on GitHub at [https://github.com/misson20000/cxxfilt-rb].
