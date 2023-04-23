class RubyCsv
  class Row
    def initialize(table, data)
      super()
      @table = table
      @data = data
    end

    def index(value)
      @data.find_index value
    end

    def method_missing(name, *args)
      index = @table.header.index name.to_s
      @data[index] if index != nil
    end
  end

  attr_accessor :header

  def initialize(file)
    super()

    @header, *@rows = file.map { |line| Row.new self, line.chomp.split(",") }
  end

  def each
    @rows.each { |row| yield(row) }
  end
end

csv = File.open("b.csv") { |file| RubyCsv.new file }
puts "Eins:"
csv.each { |row| puts row.eins }
puts "Zwei:"
csv.each { |row| puts row.zwei }
puts "Drei:"
csv.each { |row| puts row.drei }
puts "Vier:"
csv.each { |row| puts row.vier }