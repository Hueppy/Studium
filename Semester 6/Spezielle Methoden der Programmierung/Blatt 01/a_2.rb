def foobar
  x = nil
  get = proc{x}
  set = proc{|n| x = n}
  return get, set
end

r1, w1 = foobar
r2, w2 = foobar
puts r1.call

w1.call(2)
puts r1.call
puts r2.call