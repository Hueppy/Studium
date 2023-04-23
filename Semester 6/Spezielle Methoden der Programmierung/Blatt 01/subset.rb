module Subset
  def subset_of?(other)
    all? { |n| other.include?(n) }
  end

  def superset_of?(other)
    other.subset_of?(self)
  end
end

class Array
  include Subset
end

puts [1, 2, 3].subset_of?([1, 2, 3, 4, 5])
puts [1, 2, 3, 6].subset_of?([1, 2, 3, 4, 5])
puts [1, 2, 3, 4, 5].superset_of?([1, 2, 3])
puts [1, 2, 3, 4, 5].superset_of?([1, 2, 3, 6])

