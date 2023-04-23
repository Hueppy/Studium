a = [4, 8, 15, 16, 23, 42]
puts a

puts "find_all:", a.find_all { |n| n.even? }
puts "reject:", a.reject { |n| n.even? }

puts "map:", a.map { |n| n**2 }

puts "inject:", a.inject(0) { |x,y| x+y }
puts "inject:", a.inject(1) { |x,y| x*y }

puts "any:", a.any? {|n| n === 42}
puts "all:", a.all? {|n| n != 41}

