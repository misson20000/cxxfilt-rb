require "cxxfilt/version.rb"

module CXXFilt
  class Demangler
    attr_reader :name
    attr_reader :doc
  end

  @demangler_map = Hash[@demanglers.map do |d|
                         [d.name.to_sym, d]
                       end]

  def self.demanglers
    @demanglers
  end
  
  def self.method_missing(sym, *args)
    if @demangler_map.include?(sym) then
      return @demangler_map[sym]
    end
    super
  end

  def self.respond_to_missing?(sym, include_private=false)
    @demangler_map.include?(sym) || super
  end
end
