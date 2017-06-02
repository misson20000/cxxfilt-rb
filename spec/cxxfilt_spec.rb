require "spec_helper"
require "pry"

RSpec.describe CXXFilt do
  it "has demanglers" do
    expect(CXXFilt::demanglers.length).to be >= 2
  end

  it "reports names for demanglers" do
    CXXFilt::demanglers.each do |d|
      expect(d).to respond_to(:name)
      expect(d.name).to be_a(String)
    end
  end
  
  it "reports docs for demanglers" do
    CXXFilt::demanglers.each do |d|
      expect(d).to respond_to(:doc)
      expect(d.doc).to be_a(String)
    end
  end
  
  describe "auto demangler" do
    it "demangles symbols" do
      expect(CXXFilt::auto.demangle("_ZN9wikipedia7article6formatEv")).to eq "wikipedia::article::format()"
      expect(CXXFilt::auto.demangle("_ZN9wikipedia7article8print_toERSo")).to eq "wikipedia::article::print_to(std::basic_ostream<char, std::char_traits<char> >&)"
    end
  end  
end
