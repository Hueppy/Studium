class Tree
  attr_accessor :name
  def initialize(children = {}, name = "")
    super()
    @name = name
    @children = children.map { |name, children| Tree.new children, name }
  end

  def visit
    yield(self)
  end

  def visit_all
    visit { |n| yield(n) }
    visit_children { |n| n.visit_all { |n| yield(n) } }
  end

  def visit_children
    @children.each { |c| c.visit { |n| yield(n)} }
  end
end

def format_tree(node, depth = 0)
  puts "#{"  " * depth} - #{node.name}"
  node.visit_children { |n| format_tree n, depth + 1 }
end

init = {"grandpa" => { "dad"   => {"child 1" => {}, "child 2" => {} },
                       "uncle" => {"child 3" => {}, "child 4" => {} } } }

tree = Tree.new init
tree.visit_all { |n| puts n.name }

tree.visit_children { |n| format_tree n }
