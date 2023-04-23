(1..10).each { |n|
  puts "Das ist Satz Nr. #{n}."
}

puts (0..12).step(3).to_a.join(", ")
puts (0..12).select { |n| n.modulo(3) == 2 }
            .join(", ")

a = ('a'..'p')
a.each_slice(4) {|n| puts n.join(", ")}
