foo = nil
p1 = proc{|n| foo=n}
p2 = proc{|n| foo+=n}

foo = 5
puts foo

p1.call 7
puts foo

p1.call 9
puts foo

p2.call 1
puts foo

