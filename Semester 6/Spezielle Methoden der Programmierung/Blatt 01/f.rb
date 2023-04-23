module Mod
  def hello
    puts "Hello"
  end
end

class A
  include Mod
end

a = A.new
a.hello

puts "require:"
require './f_1.rb'
require './f_1.rb'
b = B.new
b.world

puts "load:"
load './f_2.rb'
load './f_2.rb'
c = C.new
c.foo



