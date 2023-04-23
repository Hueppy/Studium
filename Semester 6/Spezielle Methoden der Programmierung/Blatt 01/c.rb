words = %w[toad entertain abortive elegant complete dare peaceful enormous tiny turn]

word = words.sample.upcase

n = 0
guess = ""
while guess != word do
  puts "\nFalsche Antwort" if n > 0

  n += 1
  puts "#{n}. Versuch: "
  guess = gets.chop.strip.upcase
end

puts word.capitalize