if ARGV.count < 2
  puts "Usage: grep \"wuppie\" meinFile.txt"
  exit
end

query = ARGV[0]
filename = ARGV[1]
f = File.open(filename)

for l in f do
  puts "#{$.}. #{l}" if l.match(/#{query}/)
end


